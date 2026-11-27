# 🐾 Clínica Pet

Cadastro de **pets** e **tutores** de uma clínica veterinária, com login de tutores e de veterinários
e pedidos de atendimento (consulta com sintomas ou só vacinação).

```
Navegador (HTML + CSS + JavaScript)  ⇄  API em C++17 (JSON sobre HTTP)  ⇄  MariaDB (Docker)
```

- **API:** C++17 com [cpp-httplib](https://github.com/yhirose/cpp-httplib) (servidor HTTP) e
  [nlohmann/json](https://github.com/nlohmann/json), ambos em `libs/`
- **Banco:** MariaDB 11.4 em container Docker, criado do zero pelo `schema.sql`
- **Front-end:** HTML/CSS/JS puro em `public/`, servido pela própria API

## Como rodar do zero

### 1. Instalar o que é preciso (uma vez por computador)

**Windows** — instale o [Docker Desktop](https://www.docker.com/products/docker-desktop/) e o
[MSYS2](https://www.msys2.org/). Depois, no terminal **MSYS2 UCRT64**:

```bash
pacman -S --needed mingw-w64-ucrt-x86_64-gcc mingw-w64-ucrt-x86_64-libmariadbclient mingw-w64-ucrt-x86_64-openssl
```

**Linux (Debian/Ubuntu)**:

```bash
sudo apt install g++ libmariadb-dev libssl-dev docker.io docker-compose-plugin curl
```

### 2. Subir o banco

```bash
docker compose up -d --wait   # cria o MariaDB e roda o schema.sql (com dados de exemplo)
```

Para zerar o banco e começar de novo: `docker compose down -v` e depois `docker compose up -d --wait`.

### 3. Compilar e rodar a API

| | Compilar | Rodar |
|---|---|---|
| Windows (PowerShell / cmd) | `build.bat` | `run.bat` |
| Windows (Git Bash / MSYS2) ou Linux | `./build.sh` | `./clinica-pet` (no Windows: `./clinica-pet.exe`) |

Abra **http://localhost:3000**. A API compila com `g++ -std=c++17 -Wall -Wextra` **sem avisos**.

> No Windows, o `run.bat` coloca `C:\msys64\ucrt64\bin` no PATH (é onde ficam as DLLs do MariaDB e do OpenSSL).
> Se o MSYS2 estiver em outra pasta, defina a variável `MSYS2` antes (ex.: `set MSYS2=D:\msys64`).

### 4. Testar

Com a API rodando, em outro terminal (Git Bash ou Linux):

```bash
./testes.sh                                  # os 6 casos do enunciado + login, permissões e extras
curl http://localhost:3000/api/saude/banco   # {"status":"ok"} se a API fala com o banco
```

### Configuração (variáveis de ambiente, todas opcionais)

| Variável | Padrão | Para quê |
|---|---|---|
| `PORT` | `3000` | porta da API |
| `DB_HOST` / `DB_PORT` | `127.0.0.1` / `3306` | onde está o MariaDB |
| `DB_USER` / `DB_PASSWORD` / `DB_NAME` | `root` / `root` / `clinica_pet` | acesso ao banco |
| `CODIGO_CLINICA` | `vet-2026` | código pedido para criar conta de veterinário. **Troque fora do ambiente de aula.** |
| `PUBLIC_DIR` | `./public` | pasta do front-end |

## Login e tipos de usuário

| | Tutor (cliente) | Veterinário (clínica) |
|---|---|---|
| Cadastro | nome, telefone, e-mail, senha | nome, e-mail, senha **+ código da clínica** |
| Pets | só os **próprios** (pet de outra pessoa responde 404) | todos |
| Cadastrar pet | precisa dizer o motivo: **consulta com sintomas** ou **apenas vacinação** | motivo opcional |
| Atendimentos | pede e acompanha os dos seus pets | vê todos, registra observações e conclui |
| Tutores e resumo | sem acesso (403) | acesso total |

- Senhas guardadas com **scrypt** + sal aleatório (OpenSSL); no banco fica `sal:hash`, nunca a senha.
- A sessão é um token aleatório (`Authorization: Bearer ...`) válido por 7 dias; no banco fica só o SHA-256 dele.
- **Esqueceu a senha?** A administração define uma nova pelo terminal (o que é digitado não aparece):
  `run.bat --redefinir-senha email@exemplo.com` (Linux: `./clinica-pet --redefinir-senha email@exemplo.com`).
  Isso também desconecta as sessões abertas.
- Ao criar conta de tutor, o sistema cria o cadastro de tutor junto. Se o e-mail já estiver no cadastro
  da clínica, a conta é recusada (409) para ninguém "assumir" os pets de outra pessoa.

## Estrutura

| Arquivo | O que faz |
|---|---|
| `docker-compose.yml` | banco MariaDB em container; roda o `schema.sql` na primeira vez |
| `schema.sql` | tabelas `tutores`, `pets`, `usuarios`, `sessoes`, `atendimentos` (PK, FK, CHECK, UNIQUE) + dados de exemplo |
| `src/main.cpp` | sobe o servidor, front-end, tratamento de erros e o comando `--redefinir-senha` |
| `src/banco.hpp/.cpp` | classe `Conexao`: todo SQL com parâmetros `?` (prepared statements), enviados como texto |
| `src/validacao.hpp/.cpp` | regras de Tutor, Pet, cadastro de usuário e atendimento + cálculo de idade |
| `src/auth.hpp/.cpp` | senhas, sessões e permissões (cliente × veterinário) |
| `src/especies.hpp` | lista de espécies (código, nome, grupo): fonte única usada pela API e pela tela |
| `src/rotas.hpp` | funções comuns às rotas (responder JSON, 422, ler o corpo...) |
| `src/rotas_auth.cpp` | cadastro, login, logout |
| `src/rotas_pets.cpp` | CRUD de pets + resumo |
| `src/rotas_atendimentos.cpp` | pedidos de consulta/vacina |
| `src/rotas_tutores.cpp` | CRUD de tutores |
| `libs/` | `httplib.h` e `json.hpp` (bibliotecas de terceiros, não editar) |
| `public/` | tela: login, pets, atendimentos, tutores; `racas.js` tem as sugestões de raça |
| `build.sh` / `build.bat` / `run.bat` | compilar e rodar |
| `testes.sh` | testes com `curl` |

## Rotas

Todas as rotas exigem login (**401** sem login), menos: `/api/auth/registro`, `/api/auth/login`,
`/api/especies` e `/api/saude/banco`.

| Método | Caminho | Respostas |
|---|---|---|
| GET | `/api/saude/banco` | 200 `{"status":"ok"}` · 503 |
| GET | `/api/especies` | 200 — `[{ codigo, nome, grupo }]` |
| POST | `/api/auth/registro` | 201 · 409 · 422 |
| POST | `/api/auth/login` | 200 · 401 |
| GET | `/api/auth/eu` · POST `/api/auth/logout` | 200 · 204 |
| GET | `/api/pets?busca=&especie=&tutor_id=` | 200 |
| GET | `/api/pets/resumo` (só vet) | 200 — total e peso médio por espécie · 403 |
| GET | `/api/pets/:id` | 200 · 404 |
| POST | `/api/pets` | 201 · 422 |
| PUT | `/api/pets/:id` | 200 · 404 · 422 |
| DELETE | `/api/pets/:id` | 204 · 404 |
| GET | `/api/atendimentos?status=&pet_id=` | 200 |
| POST | `/api/atendimentos` | 201 · 422 |
| PATCH | `/api/atendimentos/:id` (só vet) | 200 · 403 · 404 · 422 |
| GET | `/api/tutores` (só vet) | 200 (inclui `qtd_pets`) |
| GET | `/api/tutores/:id` (só vet) | 200 · 404 |
| GET | `/api/tutores/:id/pets` (só vet) | 200 · 404 |
| POST | `/api/tutores` (só vet) | 201 · 409 (e-mail repetido) · 422 |
| PUT | `/api/tutores/:id` (só vet) | 200 · 404 · 409 · 422 |
| DELETE | `/api/tutores/:id` (só vet) | 204 · 404 · 409 (tutor tem pets ou tem conta) |

- **400**: JSON mal formatado no corpo.
- **422**: dados inválidos, no formato `{ "erro": "...", "campos": { "campo": "mensagem" } }`;
  a tela mostra cada mensagem embaixo do campo.
- Nenhum erro derruba o servidor: exceções viram uma resposta JSON (`tratarExcecao`, em `main.cpp`).

### Exemplo de pet em JSON

```json
{
  "nome": "Thor",
  "especie": "cachorro",
  "raca": "Labrador",
  "mes_nascimento": 3,
  "ano_nascimento": 2021,
  "peso_kg": 28.4,
  "tutor_id": 1
}
```

## Extras implementados

- Login de tutor e de veterinário, com permissões diferentes
- Pedido de atendimento obrigatório ao cadastrar pet (sintomas ou só vacina) e registro do veterinário
- Idade do pet em anos e meses, calculada na API a partir do mês e ano de nascimento
- 41 espécies em grupos (inclusive répteis, aracnídeos, animais de fazenda e silvestres)
- Autocompletar de raça por espécie e opção "Não sei a raça"
- Filtro por espécie e por tutor; `GET /api/tutores/:id/pets`; `GET /api/pets/resumo`
- Bloqueio de exclusão de tutor com pets (409 com mensagem útil); edição e exclusão de tutores pela tela

## Validação em duas camadas

1. **API** (`validacao.cpp`): devolve mensagens claras (422/409).
2. **Banco** (`CHECK`, `FOREIGN KEY`, `UNIQUE`): rede de segurança. Mesmo que a API deixe passar algo,
   o banco recusa, e o tratador de erros traduz para 409/422 sem derrubar o servidor.
