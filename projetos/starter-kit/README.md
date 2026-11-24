# Starter kit — API em C++ + MariaDB + front-end

Um CRUD **completo e funcionando** (o recurso de exemplo se chama *recados*) para a sua equipe usar como ponto de partida. O trabalho de vocês é **trocar o exemplo pelo tema do projeto** e deixar tudo bem feito, não construir a infraestrutura do zero.

```
Navegador (public/index.html + app.js)
        │  fetch() com JSON
        ▼
Servidor C++ (cpp-httplib)  ──►  rotas_*.cpp  ──►  *_repositorio.cpp  ──►  MariaDB (container Docker)
```

## Estrutura

```
starter-kit/
├── docker-compose.yml       sobe o banco MariaDB em um container Docker
├── build.sh / build.bat     compilam o servidor (build.sh só recompila o que mudou)
├── schema.sql               cria as tabelas (o Docker executa este arquivo ao criar o banco)
├── libs/                    bibliotecas de terceiros (não precisa instalar nada além do MariaDB):
│   ├── httplib.h            cpp-httplib (servidor HTTP)
│   └── nlohmann/json.hpp    nlohmann/json (JSON)
├── src/
│   ├── main.cpp             liga tudo: rotas, arquivos estáticos, tratamento de erros, porta
│   ├── config.hpp           host/usuário/senha do banco e porta do servidor
│   ├── banco.hpp/.cpp       conexão com o MariaDB (consultar / executar, com parâmetros "?")
│   ├── http_util.hpp        enviarJson, enviarErro, lerCorpoObjeto, lerId, comBanco
│   ├── recado_repositorio.* TODO o SQL do recurso "recados"
│   └── rotas_recados.*      rotas HTTP + validação do recurso "recados"
└── public/                  front-end (o servidor entrega estes arquivos ao navegador)
    ├── index.html
    ├── estilo.css
    ├── config.js            ← a configuração da tela (título, recurso da API, campos): é o que se edita
    └── app.js               CRUD genérico: monta tabela, formulário e busca a partir do config.js
```

## Rodando pela primeira vez

Pré-requisitos (compilador, biblioteca do MariaDB e Docker): [`../guia/01-preparar-ambiente.md`](../guia/01-preparar-ambiente.md).

1. **Suba o banco** (o Docker Desktop precisa estar aberto). Na pasta do starter kit:

   ```bash
   docker compose up -d --wait
   ```

   A primeira vez baixa a imagem do MariaDB (pode levar alguns minutos) e executa o `schema.sql` sozinho. Confira com `docker compose ps`: o serviço `db` deve aparecer como **healthy**.
2. **Compile** (a primeira vez demora, pois a `httplib.h` é grande):
   - terminal do MSYS2 UCRT64: `./build.sh`
   - `cmd` ou PowerShell: `build.bat`
3. **Execute, dentro da pasta do starter kit** (o servidor procura `./public` a partir dela):
   - `./build/servidor.exe` (ou `./build.sh rodar`)
4. Abra **http://localhost:8080** no navegador. Você deve ver a tela de *Recados* com um registro de boas-vindas.

Se algo falhar, veja a seção *Problemas comuns*, no fim deste arquivo.

## Testando a API sem o front-end

Com o servidor rodando, em outro terminal:

```bash
curl http://localhost:8080/api/saude                    # {"status":"ok"}
curl http://localhost:8080/api/saude/banco              # {"banco":"ok"}  (testa a conexão com o MariaDB)
curl http://localhost:8080/api/recados                  # lista
curl "http://localhost:8080/api/recados?busca=bem"      # busca
curl -X POST http://localhost:8080/api/recados -d '{"titulo":"Teste","prioridade":2}'
curl -X PUT  http://localhost:8080/api/recados/2 -d '{"titulo":"Novo titulo"}'
curl -X DELETE http://localhost:8080/api/recados/2
```

> Estes exemplos usam as aspas do bash: rode-os no **terminal do MSYS2**. No `cmd` e no PowerShell as aspas funcionam de outro jeito (e, no PowerShell, `curl` é um apelido de outro comando; use `curl.exe`). Outra opção é testar com a extensão *Thunder Client* do VS Code.

## Padrão das respostas

| Situação | Status | Corpo |
|----------|:------:|-------|
| Lista / busca / atualização OK | 200 | JSON (array ou objeto) |
| Criado | 201 | o registro criado |
| Removido | 204 | vazio |
| JSON inválido ou id inválido | 400 | `{"erro": "..."}` |
| Registro não encontrado / rota inexistente | 404 | `{"erro": "..."}` |
| Valor único repetido ou registro relacionado | 409 | `{"erro": "..."}` |
| Dados que não passam na validação (ou numa regra `CHECK` do banco) | 422 | `{"erro": "Dados invalidos", "detalhes": ["...", "..."]}` |
| Falha no banco / erro interno | 500 | `{"erro": "..."}` (os detalhes ficam só no console do servidor) |

## Como trocar o exemplo pelo seu tema

Siga sempre esta ordem; cada passo pode ser testado antes do próximo.

1. **Tabela** — em `schema.sql`, crie a tabela do seu tema (veja o tema em [`../temas/`](../temas/)) e **aplique de novo**: `docker compose down -v` e depois `docker compose up -d --wait` (o schema só roda quando o banco é criado).
2. **Repositório** — copie `recado_repositorio.hpp/.cpp` para `livro_repositorio.*` (ou `pet_`, `produto_`) e ajuste o nome da classe, as colunas e os SQLs. **Todo SQL fica aqui.**
3. **Rotas** — copie `rotas_recados.hpp/.cpp` para `rotas_livros.*` e ajuste os caminhos (`/api/livros`), a validação e as mensagens.
4. **Registro** — em `main.cpp`, inclua o cabeçalho novo e chame `registrarRotasLivros(servidor, config);`.
5. **Compilação** — o `build.sh` já enxerga os novos `.cpp` de `src/`. No `build.bat`, acrescente-os na lista `FONTES`.
6. **Front-end** — em `public/config.js`, troque o título, o recurso e os campos. Para uma segunda tela (a entidade de apoio), copie `index.html` e o `config.js` (veja o guia 05).
7. **Teste com `curl` e depois no navegador**, e só então faça o *commit*.

Os guias [`03-json-e-validacao.md`](../guia/03-json-e-validacao.md), [`04-banco-mariadb.md`](../guia/04-banco-mariadb.md) e [`05-front-end.md`](../guia/05-front-end.md) explicam cada parte.

## Configuração (variáveis de ambiente)

Os padrões servem para o banco do `docker-compose.yml`. Para mudar sem editar o código, defina antes de executar (no `cmd`: `set NOME=valor`; no MSYS2/bash: `export NOME=valor`):

| Variável | Padrão | Para que serve |
|----------|--------|----------------|
| `DB_HOST` | `127.0.0.1` | endereço do MariaDB |
| `DB_PORTA` | `3306` | porta do MariaDB (o `docker-compose.yml` também lê esta variável) |
| `DB_USUARIO` | `iteam` | usuário |
| `DB_SENHA` | `iteam123` | senha |
| `DB_NOME` | `projeto_iteam` | nome do banco |
| `PORTA` | `8080` | porta do servidor (também aceita `servidor.exe 8081`) |

## O banco de dados no Docker: comandos do dia a dia

Rode sempre **na pasta onde está o `docker-compose.yml`** (o Docker Desktop precisa estar aberto).

| Quero… | Comando |
|--------|---------|
| Subir o banco (e esperar ficar pronto) | `docker compose up -d --wait` |
| Ver se está no ar | `docker compose ps` (deve mostrar **healthy**) |
| Ver os registros de funcionamento (erros do banco) | `docker compose logs db` |
| Parar no fim do dia (os dados ficam guardados) | `docker compose stop` |
| **Zerar o banco** e aplicar o `schema.sql` de novo (apaga os dados!) | `docker compose down -v` e depois `docker compose up -d --wait` |
| Abrir um terminal SQL dentro do banco | `docker compose exec db mariadb -uiteam -piteam123 projeto_iteam` |
| Administrar pelo navegador (Adminer, opcional) | `docker compose --profile admin up -d`, depois <http://localhost:8081> (Sistema: MySQL; Servidor: `db`; Usuário: `iteam`; Senha: `iteam123`; Banco: `projeto_iteam`) |

- O `schema.sql` é executado **só quando o banco é criado** (volume vazio). Mudou o arquivo? Zere o banco com `down -v`.
- Os dados ficam em um *volume* do Docker e sobrevivem a `stop`/`down` e à reinicialização do computador.
- Só um banco por vez usa a porta 3306: ao trocar de pasta (por exemplo, do `starter-kit` para o `projeto-equipe`), rode `docker compose down` na pasta antiga.
- Se a porta 3306 já estiver ocupada, defina `DB_PORTA` (por exemplo, `set DB_PORTA=3307`) **antes** de subir o banco **e** ao executar o servidor.
- Usuário do banco: `iteam` / `iteam123` (aplicação) e `root` / `root` (administrador). Servem apenas para desenvolvimento local; a porta só é aberta para o seu computador.

## O que pode e o que não deve mudar

- **Podem e devem mudar:** `schema.sql`, `docker-compose.yml` (só se precisar, por exemplo, de outra porta), `src/recado_*`, `src/rotas_*`, `src/main.cpp` (para registrar rotas), `public/*`.
- **Mudem com cuidado:** `banco.*` e `http_util.hpp` — são usados por todas as rotas. Se alterar, avise a equipe.
- **Não editem:** `libs/` (código de terceiros).
- **Regra de ouro do SQL:** valores **sempre** em parâmetros `?`, nunca concatenados no texto do SQL (SQL injection).

## Problemas comuns

| Sintoma | Causa provável e o que fazer |
|---------|------------------------------|
| `AVISO: Nao foi possivel conectar ao banco` | O container do banco não está no ar (`docker compose ps`; suba com `docker compose up -d --wait`), o Docker Desktop está fechado, ou a porta/usuário/senha são outros (variáveis `DB_*`). |
| `Cannot connect to the Docker daemon` / `error during connect` | O **Docker Desktop não está aberto** (ou ainda está iniciando). Abra-o, espere o ícone ficar verde e tente de novo. |
| `Bind for 127.0.0.1:3306 failed: port is already allocated` | Outro banco (ou o container de outra pasta) usa a porta 3306. Rode `docker compose down` na outra pasta, ou use `DB_PORTA=3307`. |
| `Unknown database 'projeto_iteam'` ou `Table ... doesn't exist` | O banco foi criado antes de o `schema.sql` estar pronto/correto. Zere: `docker compose down -v` e `docker compose up -d --wait`. |
| O container fica `unhealthy` / reinicia sozinho | Provável erro de SQL no `schema.sql`: veja `docker compose logs db`, corrija o arquivo e zere o banco (`down -v`). |
| `mysql.h: No such file or directory` / `cannot find -lmariadb` | Falta a biblioteca cliente do MariaDB. Veja o guia 01 (instalação via `pacman` ou o MariaDB Connector/C) e, se necessário, defina `MARIADB_DIR`. |
| `ERRO: nao foi possivel usar a porta 8080` | Outro programa já usa a porta (talvez uma execução anterior do servidor). Feche-o ou rode `servidor.exe 8081`. |
| `AVISO: pasta ./public nao encontrada` | Você executou o servidor de outra pasta. Entre na pasta do starter kit antes de executar. |
| Janela fecha ao abrir o `.exe` e/ou erro sobre `libmariadb.dll` | A DLL do MariaDB não está no `PATH`. Rode pelo terminal do MSYS2 ou copie a `libmariadb.dll` para a pasta `build/`. |
| Alterei o código e nada mudou | Compile de novo (`./build.sh`) e **reinicie** o servidor. Para mudanças só no `public/`, basta recarregar a página (Ctrl+F5). |
| Acentos estranhos no navegador | Salve os arquivos do projeto em **UTF-8**. |

## Créditos das bibliotecas

[cpp-httplib](https://github.com/yhirose/cpp-httplib) (licença MIT) e [nlohmann/json](https://github.com/nlohmann/json) (licença MIT). Os textos das licenças estão em `libs/`.
