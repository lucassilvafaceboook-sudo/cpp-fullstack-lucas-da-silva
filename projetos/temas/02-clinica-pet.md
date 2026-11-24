# 🐾 Tema 2 — Clínica Pet

Um sistema para uma clínica veterinária cadastrar os **pets** atendidos e os **tutores** (donos) responsáveis por eles, para a recepção consultar rapidamente quem é o animal, qual a espécie e como falar com o tutor.

- **Entidade principal:** `pets` (CRUD completo)
- **Entidade de apoio:** `tutores` (ao menos listar e criar; editar/excluir é bem-vindo)
- **Relacionamento:** um tutor tem vários pets; cada pet tem um tutor (`pets.tutor_id → tutores.id`)

## Campos

### Tutor (`tutores`)

| Campo | Tipo | Regras |
|-------|------|--------|
| `id` | inteiro, automático | chave primária |
| `nome` | texto, até 100 | **obrigatório** |
| `telefone` | texto, até 20 | **obrigatório** |
| `email` | texto, até 120 | opcional; se informado, **único** e com um `@` |

### Pet (`pets`)

| Campo | Tipo | Regras |
|-------|------|--------|
| `id` | inteiro, automático | chave primária |
| `nome` | texto, até 60 | **obrigatório** |
| `especie` | texto | **obrigatório**; um de: `cachorro`, `gato`, `ave`, `outro` |
| `raca` | texto, até 60 | opcional |
| `data_nascimento` | data (`AAAA-MM-DD`) | opcional; não pode ser no futuro |
| `peso_kg` | decimal (até 999,99) | opcional; se informado, maior que 0 |
| `tutor_id` | inteiro | **obrigatório**, precisa existir em `tutores` |

## Modelo de banco sugerido

Copiem este SQL para o `schema.sql` do projeto (no lugar da tabela de exemplo, mas **mantendo** o `CREATE DATABASE`/`USE` do começo do arquivo) e apliquem com `docker compose down -v` e `docker compose up -d --wait`.

```sql
CREATE TABLE IF NOT EXISTS tutores (
    id       INT UNSIGNED NOT NULL AUTO_INCREMENT,
    nome     VARCHAR(100) NOT NULL,
    telefone VARCHAR(20)  NOT NULL,
    email    VARCHAR(120) NULL,
    PRIMARY KEY (id),
    UNIQUE KEY uq_tutores_email (email)
) ENGINE = InnoDB;

CREATE TABLE IF NOT EXISTS pets (
    id              INT UNSIGNED  NOT NULL AUTO_INCREMENT,
    nome            VARCHAR(60)   NOT NULL,
    especie         VARCHAR(20)   NOT NULL,
    raca            VARCHAR(60)   NULL,
    data_nascimento DATE          NULL,
    peso_kg         DECIMAL(5,2)  NULL,
    tutor_id        INT UNSIGNED  NOT NULL,
    PRIMARY KEY (id),
    CONSTRAINT fk_pets_tutor FOREIGN KEY (tutor_id) REFERENCES tutores (id),
    CONSTRAINT ck_pets_especie CHECK (especie IN ('cachorro', 'gato', 'ave', 'outro')),
    CONSTRAINT ck_pets_peso CHECK (peso_kg IS NULL OR peso_kg > 0)
) ENGINE = InnoDB;
```

> **Atenção com campos opcionais:** o `Conexao` envia todos os parâmetros como texto, e um campo vazio chega como `''`. Uma data vazia (`''`) é **recusada** pelo banco, e um `email` vazio repetido quebraria o `UNIQUE`. Use `NULLIF(?, '')` no SQL para gravar `NULL`: `VALUES (..., NULLIF(?, ''), NULLIF(?, ''))`.

## Rotas mínimas

| Método | Caminho | Descrição | Respostas |
|--------|---------|-----------|-----------|
| GET | `/api/pets` | lista (aceita `?busca=` no nome do pet ou da raça) | 200 |
| GET | `/api/pets/:id` | um pet | 200 · 404 |
| POST | `/api/pets` | cria | 201 · 422 |
| PUT | `/api/pets/:id` | atualiza | 200 · 404 · 422 |
| DELETE | `/api/pets/:id` | remove | 204 · 404 |
| GET | `/api/tutores` | lista os tutores | 200 |
| POST | `/api/tutores` | cria um tutor | 201 · 409 (e-mail repetido) · 422 |

### Exemplo de pet em JSON

```json
{
  "nome": "Thor",
  "especie": "cachorro",
  "raca": "Labrador",
  "data_nascimento": "2021-03-15",
  "peso_kg": 28.4,
  "tutor_id": 1
}
```

## Tela mínima

- Tabela de pets com o **nome do tutor**, a espécie e a data formatada (`15/03/2021`).
- Formulário de criar/editar com **lista de seleção** para a espécie (`opcoes` fixas) e para o tutor (`opcoesDe: { recurso: "tutores", valor: "id", rotulo: "nome" }`).
- Uma forma de cadastrar um tutor novo.

## Extras (escolham alguns, só depois do obrigatório)

- Mostrar a **idade** do pet (em anos e meses) calculada a partir da data de nascimento, na API ou no front.
- Filtro por espécie e por tutor (`?especie=gato&tutor_id=3`).
- `GET /api/tutores/:id/pets`: os pets de um tutor.
- `GET /api/pets/resumo`: quantidade de pets por espécie e peso médio.
- Impedir excluir um tutor que tem pets (**409** com mensagem útil).
- Edição e exclusão de tutores pela tela.

## Casos de teste que a equipe deve fazer com `curl`

1. Criar pet com `especie: "dragao"` → **422** (e o banco também recusaria pelo `CHECK`).
2. Criar pet com `data_nascimento` no futuro → **422**.
3. Criar pet **sem** data de nascimento e sem peso → funciona (`NULLIF`).
4. Criar pet com `peso_kg: -2` → **422**.
5. Criar dois tutores com o mesmo e-mail → o segundo dá **409**; dois tutores sem e-mail → funcionam.
6. Criar pet com `tutor_id` que não existe → erro claro (**422**), sem derrubar o servidor.
