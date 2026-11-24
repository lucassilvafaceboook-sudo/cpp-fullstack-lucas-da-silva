# Guia 4 — Banco de dados MariaDB

**Objetivo:** modelar as tabelas do tema, gravar e consultar pelo C++ com segurança e organizar o SQL em um **repositório**.

🎬 **No demo:** o `schema.sql` (passo 1) e os repositórios (passos 2, 3 e 5) usam todas as receitas da seção 5: `NULLIF`, chave estrangeira, `JOIN`, `LIKE` e agregações ([`demo/`](../demo/README.md)).

## 1. Revisão rápida de SQL

```sql
CREATE TABLE IF NOT EXISTS autores (
    id   INT UNSIGNED NOT NULL AUTO_INCREMENT,     -- número gerado pelo banco
    nome VARCHAR(100) NOT NULL,                    -- obrigatório
    PRIMARY KEY (id),
    UNIQUE KEY uq_autores_nome (nome)              -- não repete
) ENGINE = InnoDB;

CREATE TABLE IF NOT EXISTS livros (
    id       INT UNSIGNED NOT NULL AUTO_INCREMENT,
    titulo   VARCHAR(150) NOT NULL,
    autor_id INT UNSIGNED NOT NULL,
    preco    DECIMAL(10,2) NOT NULL,
    PRIMARY KEY (id),
    CONSTRAINT fk_livros_autor FOREIGN KEY (autor_id) REFERENCES autores (id),   -- aponta para autores
    CONSTRAINT ck_livros_preco CHECK (preco >= 0)
) ENGINE = InnoDB;

INSERT INTO livros (titulo, autor_id, preco) VALUES ('Dom Casmurro', 1, 29.90);
SELECT l.id, l.titulo, a.nome AS autor FROM livros l JOIN autores a ON a.id = l.autor_id WHERE l.id = 1;
UPDATE livros SET titulo = 'Dom Casmurro (2ª ed.)' WHERE id = 1;
DELETE FROM livros WHERE id = 1;
```

Pontos que o professor vai olhar no seu `schema.sql`:

- `IF NOT EXISTS`: o arquivo pode ser executado de novo sem erro.
- **Chave primária** em toda tabela e **chave estrangeira** em toda ligação.
- `NOT NULL` onde o campo é obrigatório; `UNIQUE` para códigos que não repetem (SKU, ISBN, e-mail); `CHECK` para regras simples (preço ≥ 0).
- Tipos adequados: dinheiro em `DECIMAL`, datas em `DATE`, nunca `FLOAT` para dinheiro.
- **Ordem de criação:** primeiro a tabela "pai" (autores), depois a que aponta para ela (livros).
- O banco **recusa** dados inválidos mesmo que a API falhe: validação na API **e** restrições no banco.
- Dados de exemplo no final, com `INSERT`, para a demonstração.

Dica: teste o SQL **antes** de colocar no C++. Duas formas (veja os comandos no README do starter kit):

- terminal SQL dentro do container: `docker compose exec db mariadb -uiteam -piteam123 projeto_iteam`;
- **Adminer** (tela no navegador, opcional): `docker compose --profile admin up -d` e abra <http://localhost:8081> (Servidor: `db`; usuário `iteam`; senha `iteam123`).

## 2. Usando o `Conexao` (src/banco.hpp)

```cpp
Conexao banco(config);                        // abre a conexão (fecha sozinha ao sair do escopo: RAII)

// SELECT -> JSON (array de objetos)
json linhas = banco.consultar("SELECT id, titulo FROM livros WHERE autor_id = ?", {"1"});

// INSERT / UPDATE / DELETE -> número de linhas afetadas
banco.executar("INSERT INTO autores (nome) VALUES (?)", {"Clarice Lispector"});
unsigned long long novoId = banco.ultimoId(); // id gerado pelo último INSERT
```

- Os valores vão **sempre** na lista entre chaves `{...}`, como `std::string`. Números usam `std::to_string(x)`.
- Colunas inteiras voltam como números JSON, `DECIMAL` como número real, `NULL` como `null`, o resto como texto.
- `Conexao` lança `ErroBanco` quando algo dá errado (SQL com erro, valor duplicado, chave estrangeira…). Nas rotas, `util::comBanco(config, res, [&](Conexao& banco) { ... })` abre a conexão e **traduz os erros para o status HTTP**: duplicado → **409**, registro em uso (FK) → **409**, `CHECK` violado → **422**, o resto → **500**.
- Como a conexão é um objeto com destrutor, **ela fecha mesmo se der exceção**. É o RAII da Unidade 4 trabalhando.

## 3. A regra de ouro: parâmetros `?`, nunca concatenar

❌ **Errado** — vulnerável a *SQL injection*:

```cpp
std::string sql = "SELECT * FROM livros WHERE titulo = '" + busca + "'";
```

Se `busca` for `x' OR '1'='1`, o SQL vira `... WHERE titulo = 'x' OR '1'='1'` e **devolve a tabela inteira**. Com `; DROP TABLE livros; --`, um atacante pode até apagar dados.

✅ **Certo** — o valor viaja separado do SQL e nunca é interpretado como comando:

```cpp
banco.consultar("SELECT * FROM livros WHERE titulo = ?", {busca});
```

Isso vale para **todo** valor que veio de fora (corpo, caminho, `?busca=`). Nomes de tabela e coluna não podem ser `?`: se precisar escolher uma coluna para ordenar, aceite só valores de uma **lista fixa** escrita por vocês.

Teste: faça `curl "http://localhost:8080/api/recados?busca=x'%20OR%20'1'='1"`. O resultado deve ser uma lista vazia, não a tabela toda.

## 4. O padrão repositório

Para o código não virar uma bagunça, **todo o SQL de uma entidade fica em uma classe**, e as rotas só chamam métodos dela:

```
rotas_livros.cpp  ──►  LivroRepositorio  ──►  Conexao  ──►  MariaDB
(HTTP, validação)      (SQL)                  (API C)
```

Modelo (do starter kit, `recado_repositorio.*`):

```cpp
class RecadoRepositorio {
public:
    explicit RecadoRepositorio(Conexao& banco) : banco_(banco) {}
    nlohmann::json listar(const std::string& busca = "");
    nlohmann::json buscar(long long id);                       // null se não existir
    nlohmann::json criar(const nlohmann::json& dados);
    nlohmann::json atualizar(long long id, const nlohmann::json& dados);  // null se não existir
    bool remover(long long id);                                // false se não existir
private:
    Conexao& banco_;                                           // guarda uma referência (Unidade 3)
};
```

Na rota, uma linha por ação:

```cpp
util::comBanco(config, res, [&](Conexao& banco) {
    RecadoRepositorio repositorio(banco);
    json recado = repositorio.buscar(id);
    if (recado.is_null()) { util::enviarErro(res, 404, "Recado nao encontrado"); return; }
    util::enviarJson(res, recado);
});
```

## 5. Receitas e armadilhas

### 5.1 Campo opcional → `NULL` de verdade (`NULLIF`)

Todos os parâmetros chegam ao banco como **texto**. Um campo opcional que não foi informado vira `''` (texto vazio), e isso causa dois problemas:

- numa coluna **`DATE`**, `''` é recusado (*Incorrect date value*);
- numa coluna **`UNIQUE`** (ISBN, e-mail), dois registros com `''` colidem (erro de duplicado), enquanto dois `NULL` são permitidos.

A solução é `NULLIF(?, '')`, que devolve `NULL` quando o valor é `''`:

```cpp
banco.executar(
    "INSERT INTO livros (titulo, autor_id, isbn) VALUES (?, ?, NULLIF(?, ''))",
    {titulo, std::to_string(autorId), isbn});          // isbn pode ser "" -> vira NULL
```

Para um número com valor padrão quando ausente: `COALESCE(NULLIF(?, ''), 1)`.

### 5.2 Checar se existe antes de atualizar

No MariaDB, um `UPDATE` que **não muda nenhum valor** devolve **0 linhas afetadas**, igual a um `UPDATE` de um id que não existe. Por isso o repositório faz `buscar(id)` **antes** de atualizar: se for `null`, responde 404; senão, atualiza e devolve o registro novo.

### 5.3 Chave estrangeira inexistente

Se o `autor_id` não existe, o `INSERT` falha com erro de FK. Para dar uma mensagem melhor que um 500/409 genérico, **confira antes** com `SELECT id FROM autores WHERE id = ?` e responda **422** com "autor_id nao existe".

### 5.4 Mostrar o nome em vez do número (`JOIN`)

```sql
SELECT l.id, l.titulo, l.autor_id, a.nome AS autor
FROM livros l JOIN autores a ON a.id = l.autor_id
ORDER BY l.titulo
```

### 5.5 Busca parcial (`LIKE`)

```cpp
const std::string padrao = "%" + busca + "%";
banco.consultar("SELECT ... WHERE titulo LIKE ? OR genero LIKE ?", {padrao, padrao});
```

O `%` fica no **valor** do parâmetro, não no SQL. (O starter kit ainda escapa `%` e `_` digitados pelo usuário; veja `escaparLike` em `recado_repositorio.cpp`.)

### 5.6 Agregações para rotas de resumo

```sql
SELECT genero, COUNT(*) AS total, SUM(exemplares) AS exemplares FROM livros GROUP BY genero
```

### 5.7 Mudar a tabela depois de criada

O Docker executa o `schema.sql` **uma única vez**: quando o banco é criado (volume vazio). Se vocês mudarem o arquivo, o banco que já existe **não muda**. Para aplicar o novo schema, apaguem os dados e subam de novo:

```bash
docker compose down -v          # apaga o container E os dados (volume)
docker compose up -d --wait     # cria tudo de novo e executa o schema.sql
```

Por isso o `schema.sql` deve ser a **única fonte da verdade** da estrutura **e** ter os dados de exemplo (`INSERT`): quem apagar o banco recupera tudo com dois comandos. Não façam alterações "só no Adminer" ou "só no terminal SQL": elas somem no próximo `down -v`.

Se o `schema.sql` tiver um erro de SQL, o banco não termina de ser criado (o container fica `unhealthy`). Veja a mensagem com `docker compose logs db`, corrija o arquivo e zere o banco de novo.

## 6. Erros do banco que você vai ver

| Código | Mensagem (resumo) | Significa | Resposta da API |
|:------:|-------------------|-----------|-----------------|
| 1062 | Duplicate entry | valor `UNIQUE` repetido | 409 |
| 1451 | Cannot delete… foreign key | tentou apagar o "pai" com "filhos" | 409 |
| 1452 | Cannot add… foreign key | `autor_id` que não existe | 409 (melhor: checar antes e dar 422) |
| 4025 / 3819 | CONSTRAINT … failed | violou um `CHECK` | 422 |
| 1292 | Incorrect date value | data inválida (ex.: `''`) | 500 (corrija a validação ou use `NULLIF`) |
| 1054 | Unknown column | nome de coluna errado no SQL | 500 (é bug nosso: veja o console do servidor) |
| 1146 | Table doesn't exist | tabela não criada | 500 (o `schema.sql` não foi aplicado: `down -v` e `up`) |
| 2002 / 2003 | Can't connect | banco desligado (container parado ou Docker fechado) | 500 |

Os detalhes aparecem **no console do servidor**, não na resposta (não expomos detalhes internos a quem chama a API).

### Acentos trocados ("CiÃªncias" em vez de "Ciências")

Os dados de exemplo (`INSERT`) foram gravados com a codificação errada. O `schema.sql` do starter kit já começa com `SET NAMES utf8mb4;` justamente para evitar isso: **mantenha essa linha** no topo do seu arquivo. Se o problema aparecer, corrija o `schema.sql` e zere o banco (`down -v`, `up -d --wait`).

## 7. Exercícios

1. Suba o banco do starter kit (`docker compose up -d --wait`) e rode, no terminal SQL do container ou no Adminer, um `SELECT` da tabela `recados`.
2. Escreva o `schema.sql` do **seu tema** (use o modelo sugerido em [`../temas/`](../temas/)) e aplique (`docker compose down -v` e `up -d --wait`). Teste: o que acontece se você tentar inserir um filho com pai inexistente? E repetir um valor `UNIQUE`?
3. Crie `<entidade>_repositorio.hpp/.cpp` copiando o de recados e adaptando. Teste cada método com uma rota e `curl`.
4. Rode o teste de *SQL injection* da seção 3 contra a sua rota de busca.

Próximo: [guia 05 — front-end](05-front-end.md).
