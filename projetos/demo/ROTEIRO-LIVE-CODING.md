# Roteiro do demo — Tarefas por Projeto

Este roteiro conta **como o demo foi construído, passo a passo**. Serve para o professor conduzir o *live coding* e para os alunos **revisarem cada passo sozinhos**: cada passo é um *commit* com uma *tag* (`demo-passo-0` … `demo-passo-6`), e a diferença entre duas tags mostra exatamente o que mudou.

O demo **não é o gabarito de nenhum tema**: o domínio é outro (tarefas e projetos), mas a *forma* é a mesma dos três temas (uma entidade principal, uma de apoio ligada por chave estrangeira, validação, filtros, resumo, duas telas). O que se aprende aqui se aplica diretamente ao projeto da equipe.

## O demo no mapa dos temas

| No demo | 📚 Biblioteca | 🐾 Clínica Pet | 🛒 Estoque de Loja |
|---------|---------------|----------------|--------------------|
| `projetos` (entidade de apoio) | `autores` | `tutores` | `categorias` |
| `tarefas` (entidade principal) | `livros` | `pets` | `produtos` |
| `projetos.nome` **único** → 409 | `autores.nome`, `livros.isbn` | `tutores.email` | `categorias.nome`, `produtos.sku` |
| `tarefas.projeto_id` (FK, `select` vindo da API) | `livros.autor_id` | `pets.tutor_id` | `produtos.categoria_id` |
| `status` (lista fixa) | `genero` | `especie` | — |
| `prazo` (data opcional) | `ano_publicacao` | `data_nascimento` | — |
| `horas_estimadas` (decimal opcional) | — | `peso_kg` | `preco` (moeda) |
| `prioridade` (inteiro com `CHECK`) | `exemplares` | — | `quantidade` |
| filtros `?status=&projeto_id=` | `?genero=&autor_id=` | `?especie=&tutor_id=` | categoria e faixa de preço |
| `GET /api/tarefas/resumo` | `/api/livros/resumo` | `/api/pets/resumo` | `/api/produtos/resumo` |
| `POST /api/tarefas/:id/concluir` (rota de ação) | emprestar/devolver | — | movimentar estoque |

## Antes da aula (checklist do professor)

- [ ] Testar o demo **no computador do laboratório** (MSYS2 UCRT64 + `libmariadbclient` + Docker Desktop): `docker compose up -d --wait`, `./build.sh`, `./build/servidor.exe`, abrir <http://localhost:8080>.
- [ ] Baixar a imagem antes, com boa internet: `docker pull mariadb:11.8` (a primeira vez demora; no laboratório isso evita esperar na frente da turma).
- [ ] Porta 3306 livre (`docker compose down` em qualquer outra pasta) e porta 8080 livre.
- [ ] Clonar o repositório com as tags: `git clone https://github.com/Hygo/c--fullstack-iteam-2sem.git` e, se já havia clone, `git fetch --tags`.
- [ ] Ter o terminal do MSYS2 UCRT64, o navegador e o editor lado a lado.

## Os passos

| Tag | O que se constrói | Onde olhar (guia) | Tempo sugerido |
|-----|-------------------|-------------------|:--------------:|
| `demo-passo-0` | Ponto de partida: cópia do starter kit rodando (banco + servidor + tela de *Recados*) | [01](../guia/01-preparar-ambiente.md), [02](../guia/02-primeira-rota.md) | 30 min |
| `demo-passo-1` | Banco: tabelas `projetos` e `tarefas`, constraints e dados de exemplo | [04](../guia/04-banco-mariadb.md) §1 e §6 | 30 min |
| `demo-passo-2` | API de **Projeto**: repositório, rotas (listar, criar, excluir), registro no `main.cpp` | [02](../guia/02-primeira-rota.md), [03](../guia/03-json-e-validacao.md) §3, [04](../guia/04-banco-mariadb.md) §2–4 | 45 min |
| `demo-passo-3` | API de **Tarefa**: CRUD completo, `validacao.hpp`, chave estrangeira, `NULLIF` | [03](../guia/03-json-e-validacao.md) §2 e §4, [04](../guia/04-banco-mariadb.md) §5.1–5.4 | 60 min |
| `demo-passo-4` | Front-end: tela de Tarefas e de Projetos no `config.js`; some o exemplo de recados | [05](../guia/05-front-end.md) | 40 min |
| `demo-passo-5` | Filtros, resumo (`GROUP BY`), rota de ação *Concluir*, destaque de atrasadas, página de resumo | [04](../guia/04-banco-mariadb.md) §5.5–5.6, [05](../guia/05-front-end.md) | 60 min |
| `demo-passo-6` | Documentação: README, `EQUIPE.md`, prints, rubrica | [06](../guia/06-git-em-equipe.md), [`rubrica.md`](../rubrica.md) | 30 min |

Total: cerca de 5 horas, que cabem em **mini-aulas** de 30 a 60 minutos antes de cada etapa do cronograma do projeto (dia 6: passos 0 a 3; dia 7 ou 8: passos 4 e 5; dia 9: passo 6). O professor decide o ritmo: dá para fazer só os passos 1 a 3 ao vivo e deixar os demais para a leitura dos *diffs*.

> **Dica de condução:** não digite tudo do zero. Mostre o *diff* do passo (`git diff demo-passo-1 demo-passo-2`), explique **por que** cada bloco existe e digite ao vivo apenas os trechos que ensinam algo (a consulta SQL, a lambda da rota, a validação). Termine **sempre** testando com `curl` ou no navegador, antes de seguir.

### Passo 0 — ponto de partida (`demo-passo-0`)

- **Mostrar:** a arquitetura (navegador → rotas → repositório → MariaDB), `main.cpp`, `banco.hpp`, o par `recado_repositorio`/`rotas_recados` e o `public/config.js`.
- **Fazer:** `docker compose up -d --wait`, `./build.sh`, executar, abrir a tela de *Recados*; `curl http://localhost:8080/api/saude/banco`.
- **Perguntas à turma:** onde fica o SQL? Onde fica a validação? O que o `comBanco` faz quando o banco devolve erro de chave duplicada?
- **Checkpoint:** todos os computadores mostram a tela e `{"banco":"ok"}`.

### Passo 1 — o banco (`demo-passo-1`)

- **Mostrar:** `schema.sql`: `UNIQUE`, `FOREIGN KEY ... ON DELETE RESTRICT`, três `CHECK`, colunas que aceitam `NULL`, dados de exemplo com **datas relativas a hoje** (sempre há tarefas atrasadas para a demonstração). Explicar as duas linhas "estranhas": `SET NAMES utf8mb4;` (acentos) e `ALTER TABLE ... AUTO_INCREMENT = 1` (ids sem "buraco").
- **Fazer:** `docker compose down -v` e `docker compose up -d --wait` (o `schema.sql` só roda com o banco novo). No terminal SQL (`docker compose exec db mariadb -uiteam -piteam123 projeto_iteam`) **provocar os erros de propósito** e anotar o código de cada um:

  ```sql
  INSERT INTO projetos (nome) VALUES ('Site da Padaria');                       -- 1062 (único)
  INSERT INTO tarefas (projeto_id, titulo) VALUES (99, 'x');                    -- 1452 (FK)
  INSERT INTO tarefas (projeto_id, titulo, prioridade) VALUES (1, 'x', 9);      -- 4025 (CHECK)
  DELETE FROM projetos WHERE id = 1;                                            -- 1451 (tem tarefas)
  ```
- **Ponte para o próximo passo:** "cada um desses códigos vira um status HTTP; quem faz a tradução é o `comBanco`".
- **Pegadinha:** mudou o `schema.sql` e nada mudou no banco? O Docker só executa o arquivo com o volume vazio: `down -v`.

### Passo 2 — API de Projeto (`demo-passo-2`)

- **Mostrar, na ordem:** `parametros.hpp` (conversões reaproveitáveis) → `projeto_repositorio` (`LEFT JOIN` + `COUNT`, `NULLIF(?, '')`) → `rotas_projetos` (validação, `comBanco`) → registro no `main.cpp` → `FONTES` do `build.bat`.
- **Digitar ao vivo:** o `SELECT` com `LEFT JOIN ... GROUP BY` e a rota `POST`.
- **Testar** (com o servidor reiniciado): `GET` (200), `POST` (201), mesmo nome de novo (**409**), nome vazio (**422**), corpo que não é JSON (**400**), `DELETE` de projeto com tarefas (**409**), de projeto novo (**204**), de id inexistente (**404**), de `abc` (**400**).
- **Perguntas:** por que `LEFT JOIN` e não `JOIN`? (projetos sem tarefa também precisam aparecer, com total 0.) Por que `PUT` não existe aqui? (entidade de apoio: o enunciado pede só listar e criar.)

### Passo 3 — API de Tarefa (`demo-passo-3`)

- **Mostrar:** `validacao.hpp` (cada função confere **um** campo e acumula mensagens) e, no fim do passo, o `validarProjeto` **encolhendo** para duas linhas: o `if` repetido virou função (critério "qualidade do código" da rubrica).
- **Pontos de ensino:**
  - `projeto_id` é conferido **antes** de gravar → 422 "projeto_id nao existe" (sem isso o banco recusa e a API devolveria um 409 genérico).
  - `PUT` confere se o id existe **antes** do `UPDATE` (um `UPDATE` que não muda nada devolve 0 linhas afetadas; sem a conferência, "nada mudou" pareceria "não existe").
  - `NULLIF(?, '')` em `descricao`, `prazo` e `horas_estimadas`: vazio vira `NULL` de verdade.
  - `concluida_em` automático: `CASE WHEN ? = 'feito' THEN COALESCE(concluida_em, NOW()) ELSE NULL END`.
- **Testar:** criar só com os campos obrigatórios (veja os padrões `pendente` e prioridade 3); criar com tudo; vários erros de uma vez (`{"projeto_id":1,"titulo":"x","status":"xx","prioridade":9,"prazo":"2026-02-30","horas_estimadas":-1}` → quatro mensagens); `PUT` mudando o status para `feito` e voltando; `GET /api/tarefas/abc` (400).
- **Desafio para a turma:** "e se `prazo` vier como `24/12/2026`?" (422, `dataValida` do `validacao.hpp`).

### Passo 4 — front-end (`demo-passo-4`)

- **Mostrar:** só `config.js` e `config-projetos.js` mudaram (mais o `projetos.html`, cópia do `index.html`). Percorrer os tipos de campo: `select` com `opcoesDe` (lista vinda da API), `select` com `opcoes` (lista fixa), `padrao`, `decimal` com `casas`, `data`, `textarea` (`largo`), `somenteLeitura` e `rotuloTabela`. Mostrar o `semEditar` na tela de Projetos e o `menu`.
- **Fazer:** criar uma tarefa pela tela, provocar um erro 422 (prioridade 9) e ver a mensagem da API aparecer, editar, excluir.
- **Ganho para o próximo passo:** a caixa **Buscar** ainda não filtra tarefas, porque a API ainda não aceita `?busca=`. Deixe a turma notar.

### Passo 5 — filtros, resumo e ação (`demo-passo-5`)

- **Filtros:** montar `WHERE` com **condições que levam `?`** (o texto digitado nunca entra no SQL). Mostrar `?busca=%27%20OR%201%3D1%20--%20` devolvendo lista vazia: não há injeção de SQL.
- **Resumo:** `COUNT(*)`, `SUM(status = 'feito')`, `COALESCE`, `GROUP BY` com `LEFT JOIN`.
- **A pegadinha da ordem das rotas (faça ao vivo):** mova `/api/tarefas/resumo` para **depois** de `/api/tarefas/:id`, recompile e chame `curl .../api/tarefas/resumo` → **400 "Id invalido"**. Desfaça e explique: o httplib testa as rotas na ordem em que foram registradas.
- **Rota de ação:** `POST /api/tarefas/:id/concluir` (404 se não existe, **409** se já está concluída). Chame duas vezes seguidas.
- **Front:** `filtros`, `classeLinha` e `acoesExtras` no `config.js`; `resumo.html` + `resumo.js` como exemplo de **página própria** que consome uma rota (`fetch`, `textContent`, barras de progresso).
- **Pergunta final:** quais destes três extras (filtro, resumo, ação) a sua equipe vai fazer? Como ficaria no seu tema? (use a tabela "O demo no mapa dos temas".)

### Passo 6 — documentação e entrega (`demo-passo-6`)

- **Mostrar:** o `README.md` do demo como **modelo de README de equipe** (como executar, tabela de rotas com exemplos, banco, decisões), o `EQUIPE.md` preenchido e como os prints entram no README (pasta `docs/`).
- **Percorrer a [`rubrica.md`](../rubrica.md)** usando o demo: onde está cada critério (API e CRUD → `rotas_*`; banco → `schema.sql`; front → `config.js`; qualidade → `validacao.hpp`; documentação → `README.md` e `EQUIPE.md`).
- **Git em equipe** (guia 06): como esse histórico em passos nasce de *commits* pequenos e de *tags*.

## Navegando pelas tags (professor)

```bash
git checkout demo-passo-3                     # vai para o estado do passo 3
git diff demo-passo-2 demo-passo-3 --stat     # o que mudou do passo 2 para o 3
git diff demo-passo-2 demo-passo-3 -- projetos/demo/src/rotas_tarefas.cpp
git checkout main                             # volta ao estado final
```

- **Trocou de tag e o `schema.sql` mudou?** Isso acontece nos passos **1** e **4**. Zere o banco: `docker compose down -v` e `docker compose up -d --wait`.
- **Recompile e reinicie o servidor** a cada troca de tag (`./build.sh`; o `public/` só precisa de Ctrl+F5).
- Para ver o passo **na internet**, sem baixar nada: `https://github.com/Hygo/c--fullstack-iteam-2sem/compare/demo-passo-2...demo-passo-3`.
- Para **liberar aos poucos**, envie as tags só depois de cada aula: `git push origin demo-passo-1`, depois `demo-passo-2`…

## Para os alunos: revisando um passo sozinho

Na cópia da equipe (ou da sua atividade) você já tem o remoto `professor` (veja [`COMO-OBTER-AS-ATIVIDADES.md`](../../COMO-OBTER-AS-ATIVIDADES.md), seção 3). Uma cópia criada pelo botão *Use this template* **não traz o histórico nem as tags**, então busque-as:

```bash
git fetch professor --tags
git diff demo-passo-2 demo-passo-3 --stat                  # arquivos que mudaram
git diff demo-passo-2 demo-passo-3 -- projetos/demo/src    # o código que mudou
git show demo-passo-3:projetos/demo/src/validacao.hpp      # um arquivo como estava naquele passo
```

Dica de estudo: antes de olhar o *diff* de um passo, leia o que ele constrói na tabela acima e **tente você mesmo** no tema da sua equipe; depois compare.

## O que o demo (de propósito) não cobre

- **Paginação e ordenação** na API e na tela.
- **`PUT` da entidade de apoio** (o enunciado pede só listar e criar; a tela de Projetos esconde o botão *Editar*).
- **Testes automatizados**: o demo foi verificado com `curl` e no navegador, como a equipe deve fazer.

Esses itens são bons extras para a sua equipe.
