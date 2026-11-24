# 🛒 Tema 3 — Estoque de Loja

Um sistema para uma lojinha controlar o **estoque dos produtos**, organizados por **categoria**, com preço e quantidade, e enxergar o que está acabando.

- **Entidade principal:** `produtos` (CRUD completo)
- **Entidade de apoio:** `categorias` (ao menos listar e criar; excluir é bem-vindo)
- **Relacionamento:** uma categoria tem vários produtos; cada produto tem uma categoria (`produtos.categoria_id → categorias.id`)

## Campos

### Categoria (`categorias`)

| Campo | Tipo | Regras |
|-------|------|--------|
| `id` | inteiro, automático | chave primária |
| `nome` | texto, até 60 | **obrigatório** e **único** |

### Produto (`produtos`)

| Campo | Tipo | Regras |
|-------|------|--------|
| `id` | inteiro, automático | chave primária |
| `nome` | texto, até 100 | **obrigatório** |
| `sku` | texto, até 30 | **obrigatório** e **único** (código do produto) |
| `categoria_id` | inteiro | **obrigatório**, precisa existir em `categorias` |
| `preco` | decimal (2 casas) | **obrigatório**; maior ou igual a 0 |
| `quantidade` | inteiro | padrão 0; nunca negativo |

## Modelo de banco sugerido

Copiem este SQL para o `schema.sql` do projeto (no lugar da tabela de exemplo, mas **mantendo** o `CREATE DATABASE`/`USE` do começo do arquivo) e apliquem com `docker compose down -v` e `docker compose up -d --wait`.

```sql
CREATE TABLE IF NOT EXISTS categorias (
    id   INT UNSIGNED NOT NULL AUTO_INCREMENT,
    nome VARCHAR(60)  NOT NULL,
    PRIMARY KEY (id),
    UNIQUE KEY uq_categorias_nome (nome)
) ENGINE = InnoDB;

CREATE TABLE IF NOT EXISTS produtos (
    id           INT UNSIGNED  NOT NULL AUTO_INCREMENT,
    nome         VARCHAR(100)  NOT NULL,
    sku          VARCHAR(30)   NOT NULL,
    categoria_id INT UNSIGNED  NOT NULL,
    preco        DECIMAL(10,2) NOT NULL,
    quantidade   INT           NOT NULL DEFAULT 0,
    PRIMARY KEY (id),
    UNIQUE KEY uq_produtos_sku (sku),
    CONSTRAINT fk_produtos_categoria FOREIGN KEY (categoria_id) REFERENCES categorias (id),
    CONSTRAINT ck_produtos_preco CHECK (preco >= 0),
    CONSTRAINT ck_produtos_quantidade CHECK (quantidade >= 0)
) ENGINE = InnoDB;
```

> **Dica sobre dinheiro:** use `DECIMAL`, nunca `FLOAT`/`DOUBLE`, para valores em reais. No front-end, o campo `decimal` com `formato: "moeda"` mostra `R$ 12,50`.

## Rotas mínimas

| Método | Caminho | Descrição | Respostas |
|--------|---------|-----------|-----------|
| GET | `/api/produtos` | lista (aceita `?busca=` no nome ou no SKU) | 200 |
| GET | `/api/produtos/:id` | um produto | 200 · 404 |
| POST | `/api/produtos` | cria | 201 · 409 (SKU repetido) · 422 |
| PUT | `/api/produtos/:id` | atualiza | 200 · 404 · 409 · 422 |
| DELETE | `/api/produtos/:id` | remove | 204 · 404 |
| GET | `/api/categorias` | lista as categorias | 200 |
| POST | `/api/categorias` | cria uma categoria | 201 · 409 (nome repetido) · 422 |

### Exemplo de produto em JSON

```json
{
  "nome": "Caderno 96 folhas",
  "sku": "CAD-096",
  "categoria_id": 2,
  "preco": 18.9,
  "quantidade": 40
}
```

## Tela mínima

- Tabela de produtos com o **nome da categoria**, o preço em reais e a quantidade.
- Formulário de criar/editar com **lista de seleção de categoria** (`opcoesDe: { recurso: "categorias", valor: "id", rotulo: "nome" }`).
- Uma forma de cadastrar uma categoria nova.

## Extras (escolham alguns, só depois do obrigatório)

- **Movimentar estoque:** `POST /api/produtos/:id/movimentar` com `{"delta": -3}` (saída) ou `{"delta": 10}` (entrada). Se o resultado ficaria negativo, recuse com **422**. Dica: faça a conta no próprio `UPDATE` (`SET quantidade = quantidade + ? WHERE id = ? AND quantidade + ? >= 0`) para evitar condição de corrida entre dois pedidos simultâneos.
- `GET /api/produtos/baixo-estoque?limite=5`: produtos com quantidade menor ou igual ao limite.
- `GET /api/produtos/resumo`: valor total do estoque (`SUM(preco * quantidade)`), total de itens e total por categoria.
- Destacar na tabela os produtos com estoque baixo (botões de entrada/saída direto na linha).
- Filtro por categoria e faixa de preço; ordenação e paginação.
- Impedir excluir categoria com produtos (**409** com mensagem útil).

## Casos de teste que a equipe deve fazer com `curl`

1. Criar produto com `preco: -1` → **422**.
2. Criar dois produtos com o mesmo `sku` → o segundo dá **409**.
3. Criar produto com `quantidade: 2.5` (não inteiro) → **422**.
4. Criar produto com `categoria_id` inexistente → erro claro (**422**), sem derrubar o servidor.
5. Apagar uma categoria que tem produtos → **409**.
6. (Extra) Movimentar `delta: -999` num produto com 5 unidades → **422**, e a quantidade continua 5.
