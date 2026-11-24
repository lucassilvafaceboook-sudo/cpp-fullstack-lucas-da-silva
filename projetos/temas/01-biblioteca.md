# 📚 Tema 1 — Biblioteca

Um sistema para a biblioteca de uma escola ou bairro cadastrar **livros** e seus **autores**, controlar quantos exemplares existem e encontrar um livro rapidamente pela busca.

- **Entidade principal:** `livros` (CRUD completo)
- **Entidade de apoio:** `autores` (ao menos listar e criar; excluir é bem-vindo)
- **Relacionamento:** um autor tem vários livros; cada livro tem um autor (`livros.autor_id → autores.id`)

## Campos

### Autor (`autores`)

| Campo | Tipo | Regras |
|-------|------|--------|
| `id` | inteiro, automático | chave primária |
| `nome` | texto, até 100 | **obrigatório** e **único** |
| `nacionalidade` | texto, até 50 | opcional |

### Livro (`livros`)

| Campo | Tipo | Regras |
|-------|------|--------|
| `id` | inteiro, automático | chave primária |
| `titulo` | texto, até 150 | **obrigatório** |
| `autor_id` | inteiro | **obrigatório**, precisa existir em `autores` |
| `genero` | texto, até 50 | opcional |
| `ano_publicacao` | inteiro | opcional; se informado, entre 1000 e 2100 |
| `isbn` | texto, até 20 | opcional; se informado, **único** |
| `exemplares` | inteiro | padrão 1; nunca negativo |

## Modelo de banco sugerido

Copiem este SQL para o `schema.sql` do projeto (no lugar da tabela de exemplo, mas **mantendo** o `CREATE DATABASE`/`USE` do começo do arquivo) e apliquem com `docker compose down -v` e `docker compose up -d --wait`.

Podem adaptar (e ampliar), mas mantenham a ideia: chaves, `NOT NULL`, `UNIQUE` e `CHECK` no banco **além** da validação na API.

```sql
CREATE TABLE IF NOT EXISTS autores (
    id            INT UNSIGNED NOT NULL AUTO_INCREMENT,
    nome          VARCHAR(100) NOT NULL,
    nacionalidade VARCHAR(50)  NULL,
    PRIMARY KEY (id),
    UNIQUE KEY uq_autores_nome (nome)
) ENGINE = InnoDB;

CREATE TABLE IF NOT EXISTS livros (
    id             INT UNSIGNED NOT NULL AUTO_INCREMENT,
    titulo         VARCHAR(150) NOT NULL,
    autor_id       INT UNSIGNED NOT NULL,
    genero         VARCHAR(50)  NULL,
    ano_publicacao SMALLINT     NULL,
    isbn           VARCHAR(20)  NULL,
    exemplares     INT          NOT NULL DEFAULT 1,
    PRIMARY KEY (id),
    UNIQUE KEY uq_livros_isbn (isbn),
    CONSTRAINT fk_livros_autor FOREIGN KEY (autor_id) REFERENCES autores (id),
    CONSTRAINT ck_livros_ano CHECK (ano_publicacao IS NULL OR ano_publicacao BETWEEN 1000 AND 2100),
    CONSTRAINT ck_livros_exemplares CHECK (exemplares >= 0)
) ENGINE = InnoDB;
```

> **Atenção com campos opcionais:** o `Conexao` envia todos os parâmetros como texto, e um campo vazio chega como `''`. Para gravar `NULL` de verdade (principalmente em colunas `UNIQUE`, como o `isbn`), use `NULLIF(?, '')` no SQL: `INSERT INTO livros (..., isbn) VALUES (..., NULLIF(?, ''))`. Sem isso, dois livros sem ISBN dariam erro de valor duplicado.

## Rotas mínimas

| Método | Caminho | Descrição | Respostas |
|--------|---------|-----------|-----------|
| GET | `/api/livros` | lista (aceita `?busca=` no título ou gênero) | 200 |
| GET | `/api/livros/:id` | um livro | 200 · 404 |
| POST | `/api/livros` | cria | 201 · 409 (ISBN repetido) · 422 |
| PUT | `/api/livros/:id` | atualiza | 200 · 404 · 409 · 422 |
| DELETE | `/api/livros/:id` | remove | 204 · 404 |
| GET | `/api/autores` | lista os autores | 200 |
| POST | `/api/autores` | cria um autor | 201 · 409 (nome repetido) · 422 |

Quando o `autor_id` não existe, o banco recusa o `INSERT` (violação de chave estrangeira); a API deve responder com um erro claro (**422** com a mensagem "autor_id nao existe"; vocês podem checar antes de gravar).

### Exemplo de livro em JSON

```json
{
  "titulo": "Dom Casmurro",
  "autor_id": 1,
  "genero": "Romance",
  "ano_publicacao": 1899,
  "isbn": "9788535910663",
  "exemplares": 3
}
```

## Tela mínima

- Tabela de livros (com o **nome do autor**, não só o número) e caixa de busca.
- Formulário de criar/editar com **lista de seleção de autor**. No `app.js` isso é um campo `select` com `opcoesDe: { recurso: "autores", valor: "id", rotulo: "nome" }`.
- Uma forma de cadastrar um autor novo (uma segunda tela simples, ou um formulário extra na mesma página).

## Extras (escolham alguns, só depois do obrigatório)

- `GET /api/livros/resumo`: total de livros, total de exemplares e quantidade de livros por gênero.
- Filtro por gênero e por autor (`?genero=Romance&autor_id=2`).
- Listar os livros de um autor: `GET /api/autores/:id/livros`.
- Impedir excluir autor com livros (a chave estrangeira já bloqueia: respondam **409** com uma mensagem útil).
- Ordenação por título/ano e paginação (`?pagina=2&tamanho=10`).
- Destacar na tabela os livros com `exemplares = 0`.

## Casos de teste que a equipe deve fazer com `curl`

1. Criar livro sem título → **422**, com a lista de detalhes.
2. Criar livro com `ano_publicacao: 3000` → **422**.
3. Criar dois livros com o mesmo ISBN → o segundo dá **409**.
4. Criar dois livros **sem** ISBN → os dois funcionam (por isso o `NULLIF`).
5. Buscar `/api/livros/9999` → **404**. Buscar `/api/livros/abc` → **400**.
6. Apagar um autor que tem livros → **409**.
