# Equipe

> **Exemplo preenchido pelo professor**, para mostrar o nível de detalhe esperado. Os nomes das pessoas são fictícios. O arquivo em branco, para a sua equipe copiar, está em [`../EQUIPE.md`](../EQUIPE.md).

## Identificação

| Campo | Preencher |
|-------|-----------|
| Nome da equipe | Equipe Demo (exemplo do professor) |
| Tema (📚 Biblioteca · 🐾 Clínica Pet · 🛒 Estoque de Loja) | Demo "Tarefas por Projeto" (mesmo formato dos três temas: uma entidade principal e uma de apoio) |
| Nome do projeto | Tarefas por Projeto |
| Link da cópia da equipe no GitHub | <https://github.com/Hygo/c--fullstack-iteam-2sem> (pasta `projetos/demo`) |
| Tag de entrega | `projeto-final` (no demo, os passos estão nas tags `demo-passo-0` a `demo-passo-6`) |

## Integrantes

| Nome | Usuário no GitHub | Papel principal (pode revezar) |
|------|-------------------|--------------------------------|
| Hygo Sousa (professor) | `Hygo` | Coordenação e revisão |
| Ana Exemplo (fictícia) | `ana-exemplo` | Banco de dados e documentação |
| Bruno Exemplo (fictício) | `bruno-exemplo` | API em C++ (rotas e validação) |
| Carla Exemplo (fictícia) | `carla-exemplo` | Front-end e testes |

## Como executar (do zero, em outro computador)

1. **Requisitos:** g++ (MSYS2 UCRT64) com C++17, `libmariadb` (`pacman -S mingw-w64-ucrt-x86_64-libmariadbclient`) e Docker Desktop aberto. Guia completo: [`../guia/01-preparar-ambiente.md`](../guia/01-preparar-ambiente.md).
2. **Banco:** na pasta `projetos/demo`, `docker compose up -d --wait` (cria o banco, executa o `schema.sql` e insere os dados de exemplo). Para zerar o banco quando o `schema.sql` mudar: `docker compose down -v` e depois `docker compose up -d --wait`. Se a porta 3306 estiver ocupada por outra pasta: `docker compose down` lá.
3. **Compilar:** `./build.sh` no terminal do MSYS2 UCRT64 (ou `build.bat` no `cmd`).
4. **Executar:** na pasta `projetos/demo`, `./build/servidor.exe`.
5. **Acessar:** <http://localhost:8080>

## Rotas da API

| Método | Caminho | O que faz | Status possíveis |
|--------|---------|-----------|------------------|
| GET | `/api/saude` · `/api/saude/banco` | servidor e banco no ar | 200 · 500 |
| GET | `/api/projetos` | lista os projetos (com `total_tarefas`) | 200 |
| POST | `/api/projetos` | cria | 201 · 409 · 422 |
| DELETE | `/api/projetos/:id` | remove | 204 · 404 · 409 |
| GET | `/api/tarefas` | lista (`?busca=`, `?status=`, `?projeto_id=`) | 200 · 422 |
| GET | `/api/tarefas/resumo` | números do painel | 200 |
| GET | `/api/tarefas/:id` | uma tarefa | 200 · 400 · 404 |
| POST | `/api/tarefas` | cria | 201 · 400 · 422 |
| PUT | `/api/tarefas/:id` | atualiza | 200 · 400 · 404 · 422 |
| POST | `/api/tarefas/:id/concluir` | marca como feito | 200 · 404 · 409 |
| DELETE | `/api/tarefas/:id` | remove | 204 · 404 |

Exemplos de corpo JSON e respostas: [`README.md`](README.md).

## Banco de dados

| Tabela | Colunas principais | Relacionamentos / regras |
|--------|--------------------|--------------------------|
| `projetos` | `id`, `nome`, `descricao`, `criado_em` | `nome` obrigatório e único |
| `tarefas` | `id`, `projeto_id`, `titulo`, `status`, `prioridade`, `prazo`, `horas_estimadas`, `concluida_em` | `projeto_id` → `projetos.id` (FK, RESTRICT); `CHECK` em status, prioridade (1–5) e horas (≥ 0); `prazo` e `horas_estimadas` opcionais |

```
projetos (1) ───────< (N) tarefas
```

## Divisão de tarefas

| Dia | Quem | O que foi feito |
|-----|------|-----------------|
| 6 | Todos (em conjunto, com o professor) | Ambiente funcionando nos 4 computadores; `/api/saude/banco` respondendo `ok`; leitura do starter kit |
| 7 | Ana (banco), Bruno (API) | `schema.sql` com projetos e tarefas e dados de exemplo; rotas de projetos; `GET` e `POST` de tarefas testados com `curl` |
| 8 | Bruno (API), Carla (front) | `PUT`/`DELETE`/`GET :id` de tarefas com validação; telas de Tarefas e Projetos no `config.js`; revezamento: Ana escreveu o `validacao.hpp` |
| 9 | Carla (front), Ana (docs), Bruno (extras) | Filtros, resumo e botão *Concluir*; página de resumo; README e este arquivo; teste do README em outro computador |

## Decisões e dificuldades

- **Conferir o `projeto_id` antes de gravar** e responder 422 com a mensagem "projeto_id nao existe", em vez de deixar o banco recusar (erro 1452 viraria um 409 genérico, pouco útil para quem usa a tela).
- **"Concluir" virou uma rota de ação** (`POST /api/tarefas/:id/concluir`) em vez de um `PUT` completo: assim o servidor decide a data de conclusão e responde 409 se a tarefa já estava concluída.
- **Dificuldade:** a página de resumo respondia 400 "Id invalido". A causa era a ordem das rotas: `/api/tarefas/:id` estava registrada antes de `/api/tarefas/resumo`. Resolvido registrando a rota fixa **antes** da rota com parâmetro.
- **Dificuldade:** os acentos dos dados de exemplo apareciam trocados ("CiÃªncias"). Resolvido com `SET NAMES utf8mb4;` no topo do `schema.sql`.

## Extras implementados

- [x] Busca / filtro
- [x] Rota de resumo ou relatório
- [ ] Paginação ou ordenação
- [x] Validações extras no front-end
- [x] Outro: destaque de tarefas atrasadas e botão *Concluir* na linha

## Checklist de entrega (dia 9)

- [x] O projeto compila sem avisos (`-Wall -Wextra`)
- [ ] `docker compose up -d --wait` cria o banco do zero (o `schema.sql` é executado sozinho) e há dados de exemplo
- [x] Todo SQL usa parâmetros `?`
- [x] CRUD completo funciona pela tela
- [ ] O README da equipe foi testado em outro computador
- [ ] Todos os integrantes têm *commits* no próprio usuário
- [ ] A tag `projeto-final` foi criada e enviada (`git push origin projeto-final`) e o link foi entregue ao professor
