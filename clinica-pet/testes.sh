#!/usr/bin/env bash
# Casos de teste do enunciado + login e permissões.
# Uso: ./testes.sh  (com o servidor rodando)
API="${API:-http://localhost:3000/api}"
CODIGO="${CODIGO_CLINICA:-vet-2026}"
J='Content-Type: application/json'
SUFIXO=$RANDOM   # deixa os e-mails únicos a cada execução

# Envia o corpo (-d) pela entrada padrão: assim os acentos chegam em UTF-8
# também no Git Bash do Windows (que estraga acentos passados como argumento).
c() {
  local args=() corpo="" tem=0
  while [ $# -gt 0 ]; do
    if [ "$1" = "-d" ]; then corpo=$2; tem=1; shift 2; else args+=("$1"); shift; fi
  done
  if [ "$tem" = 1 ]; then printf '%s' "$corpo" | curl "${args[@]}" --data-binary @-; else curl "${args[@]}"; fi
}
passo() { echo; echo "=== $1 (esperado: $2)"; }
req()   { c -s -w '\n→ HTTP %{http_code}\n' "$@"; }
token() { sed -n 's/.*"token":"\([^"]*\)".*/\1/p'; }
id()    { sed -n 's/^{"id":\([0-9]*\).*/\1/p'; }

echo "=== Preparando contas de teste"
VET=$(c -s -X POST "$API/auth/registro" -H "$J" \
  -d "{\"papel\":\"veterinario\",\"nome\":\"Dra. Teste\",\"email\":\"vet$SUFIXO@clinica.com\",\"senha\":\"segredo1\",\"codigo_clinica\":\"$CODIGO\"}" | token)
ANA=$(c -s -X POST "$API/auth/registro" -H "$J" \
  -d "{\"nome\":\"Cliente A\",\"telefone\":\"1111\",\"email\":\"a$SUFIXO@email.com\",\"senha\":\"segredo1\"}" | token)
BIA=$(c -s -X POST "$API/auth/registro" -H "$J" \
  -d "{\"nome\":\"Cliente B\",\"telefone\":\"2222\",\"email\":\"b$SUFIXO@email.com\",\"senha\":\"segredo1\"}" | token)
[ -n "$VET" ] && [ -n "$ANA" ] && [ -n "$BIA" ] || { echo "Falha ao criar contas de teste"; exit 1; }
AV="Authorization: Bearer $VET"; AA="Authorization: Bearer $ANA"; AB="Authorization: Bearer $BIA"

echo; echo "######## ENUNCIADO (como veterinário) ########"

passo "1. Espécie 'dragao'" 422
req -X POST "$API/pets" -H "$J" -H "$AV" -d '{"nome":"Smaug","especie":"dragao","tutor_id":1}'

passo "2. Nascimento no futuro (01/2999)" 422
req -X POST "$API/pets" -H "$J" -H "$AV" -d '{"nome":"Futuro","especie":"gato","mes_nascimento":1,"ano_nascimento":2999,"tutor_id":1}'

passo "3. Sem nascimento e sem peso" 201
req -X POST "$API/pets" -H "$J" -H "$AV" -d '{"nome":"Rex","especie":"cachorro","tutor_id":1}'

passo "Nascimento com mês e ano (03/2021)" 201
req -X POST "$API/pets" -H "$J" -H "$AV" -d '{"nome":"Mel","especie":"cachorro","mes_nascimento":3,"ano_nascimento":2021,"tutor_id":1}'
passo "Ano sem mês" 422
req -X POST "$API/pets" -H "$J" -H "$AV" -d '{"nome":"Mel","especie":"cachorro","ano_nascimento":2021,"tutor_id":1}'
passo "Mês 13" 422
req -X POST "$API/pets" -H "$J" -H "$AV" -d '{"nome":"Mel","especie":"cachorro","mes_nascimento":13,"ano_nascimento":2021,"tutor_id":1}'

passo "Espécie nova: cobra" 201
req -X POST "$API/pets" -H "$J" -H "$AV" -d '{"nome":"Nagini","especie":"cobra","raca":"Jiboia","tutor_id":1}'
passo "Espécie nova: aranha" 201
req -X POST "$API/pets" -H "$J" -H "$AV" -d '{"nome":"Aragog","especie":"aranha","tutor_id":1}'
passo "Lista de espécies" 200
req "$API/especies" -o /dev/null

passo "4. Peso -2" 422
req -X POST "$API/pets" -H "$J" -H "$AV" -d '{"nome":"Leve","especie":"ave","peso_kg":-2,"tutor_id":1}'

passo "5a. Tutor com e-mail novo" 201
req -X POST "$API/tutores" -H "$J" -H "$AV" -d "{\"nome\":\"Dani\",\"telefone\":\"1111\",\"email\":\"dani$SUFIXO@email.com\"}"
passo "5b. Outro tutor com o MESMO e-mail" 409
req -X POST "$API/tutores" -H "$J" -H "$AV" -d "{\"nome\":\"Dani 2\",\"telefone\":\"2222\",\"email\":\"dani$SUFIXO@email.com\"}"
passo "5c. Tutor sem e-mail" 201
req -X POST "$API/tutores" -H "$J" -H "$AV" -d '{"nome":"Sem Email 1","telefone":"3333"}'
passo "5d. Outro tutor sem e-mail" 201
req -X POST "$API/tutores" -H "$J" -H "$AV" -d '{"nome":"Sem Email 2","telefone":"4444","email":""}'

passo "6. tutor_id inexistente" 422
req -X POST "$API/pets" -H "$J" -H "$AV" -d '{"nome":"Órfão","especie":"gato","tutor_id":99999}'

echo; echo "######## LOGIN E CADASTRO ########"

passo "Sem login" 401
req "$API/pets"
passo "Login com senha errada" 401
req -X POST "$API/auth/login" -H "$J" -d "{\"email\":\"a$SUFIXO@email.com\",\"senha\":\"errada\"}"
passo "Login certo" 200
req -X POST "$API/auth/login" -H "$J" -d "{\"email\":\"a$SUFIXO@email.com\",\"senha\":\"segredo1\"}" -o /dev/null
passo "Conta com e-mail repetido" 409
req -X POST "$API/auth/registro" -H "$J" -d "{\"nome\":\"X\",\"telefone\":\"1\",\"email\":\"a$SUFIXO@email.com\",\"senha\":\"segredo1\"}"
passo "Veterinário com código errado" 422
req -X POST "$API/auth/registro" -H "$J" -d "{\"papel\":\"veterinario\",\"nome\":\"X\",\"email\":\"x$SUFIXO@c.com\",\"senha\":\"segredo1\",\"codigo_clinica\":\"chute\"}"

echo; echo "######## CLIENTE: MOTIVO OBRIGATÓRIO ########"

passo "Cliente cadastra pet sem dizer o motivo" 422
req -X POST "$API/pets" -H "$J" -H "$AA" -d '{"nome":"Bidu","especie":"cachorro"}'
passo "Consulta sem sintomas" 422
req -X POST "$API/pets" -H "$J" -H "$AA" -d '{"nome":"Bidu","especie":"cachorro","tipo":"consulta"}'
passo "Pet da cliente A, com sintomas" 201
PET_A=$(c -s -X POST "$API/pets" -H "$J" -H "$AA" \
  -d '{"nome":"Bidu","especie":"cachorro","tipo":"consulta","sintomas":"Está sem comer há 2 dias","tutor_id":1}')
echo "$PET_A"; PET_A=$(echo "$PET_A" | id)
passo "Pet da cliente B, só vacina (sem sintomas)" 201
PET_B=$(c -s -X POST "$API/pets" -H "$J" -H "$AB" -d '{"nome":"Nina","especie":"gato","tipo":"vacina"}')
echo "$PET_B"; PET_B=$(echo "$PET_B" | id)

echo; echo "######## CLIENTE NÃO VÊ PET DOS OUTROS ########"

passo "B lista pets (só a Nina)" 200
req "$API/pets" -H "$AB"
passo "B abre o pet da A" 404
req "$API/pets/$PET_A" -H "$AB"
passo "B tenta editar o pet da A" 404
req -X PUT "$API/pets/$PET_A" -H "$J" -H "$AB" -d '{"nome":"Roubado","especie":"cachorro"}'
passo "B tenta excluir o pet da A" 404
req -X DELETE "$API/pets/$PET_A" -H "$AB"
passo "B pede atendimento para o pet da A" 422
req -X POST "$API/atendimentos" -H "$J" -H "$AB" -d "{\"pet_id\":$PET_A,\"tipo\":\"vacina\"}"
passo "B lista atendimentos (só os da Nina)" 200
req "$API/atendimentos" -H "$AB"
passo "B tenta ver a lista de tutores" 403
req "$API/tutores" -H "$AB"
passo "B tenta ver o resumo da clínica" 403
req "$API/pets/resumo" -H "$AB"
passo "B tenta concluir um atendimento" 403
req -X PATCH "$API/atendimentos/1" -H "$J" -H "$AB" -d '{"status":"concluido"}'
passo "B pede nova consulta para a própria Nina" 201
req -X POST "$API/atendimentos" -H "$J" -H "$AB" -d "{\"pet_id\":$PET_B,\"tipo\":\"consulta\",\"sintomas\":\"Espirrando muito\"}"

echo; echo "######## VETERINÁRIO VÊ TUDO ########"

passo "Vet abre o pet da A" 200
req "$API/pets/$PET_A" -H "$AV" -o /dev/null
passo "Vet lista atendimentos aguardando" 200
req "$API/atendimentos?status=aguardando" -H "$AV" -o /dev/null
ATEND=$(c -s "$API/atendimentos?pet_id=$PET_A" -H "$AV" | sed -n 's/^\[{"id":\([0-9]*\).*/\1/p')
passo "Vet conclui o atendimento do Bidu" 200
req -X PATCH "$API/atendimentos/$ATEND" -H "$J" -H "$AV" -d '{"status":"concluido","observacoes":"Gastrite leve, dieta por 5 dias."}'

echo; echo "######## EXTRAS ########"
passo "GET pet inexistente" 404
req "$API/pets/99999" -H "$AV"
passo "Excluir tutor que tem pets" 409
req -X DELETE "$API/tutores/1" -H "$AV"
passo "Resumo por espécie" 200
req "$API/pets/resumo" -H "$AV"
passo "Busca por raça" 200
req "$API/pets?busca=labr" -H "$AV"
passo "Logout, depois o mesmo token" 401
c -s -o /dev/null -X POST "$API/auth/logout" -H "$AB"
req "$API/pets" -H "$AB"
