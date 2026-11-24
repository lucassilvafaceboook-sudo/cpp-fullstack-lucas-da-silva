# Guia 3 — JSON e validação

**Objetivo:** ler e montar JSON com a biblioteca **nlohmann/json**, validar os dados que chegam e responder com o código de status certo.

🎬 **No demo:** o `validacao.hpp` do passo 3 reúne as validações reutilizáveis ([`demo/src/validacao.hpp`](../demo/src/validacao.hpp); roteiro em [`demo/ROTEIRO-LIVE-CODING.md`](../demo/ROTEIRO-LIVE-CODING.md)).

> Regra de ouro: **nunca confie no que chega pela rede.** O front-end pode ter um bug, o usuário pode mexer na requisição, e o `curl` envia o que quiser. A API sempre valida.

## 1. JSON em C++ com nlohmann/json

```cpp
#include <nlohmann/json.hpp>
using nlohmann::json;
```

### Montar

```cpp
json livro = {{"titulo", "Dom Casmurro"}, {"ano", 1899}, {"disponivel", true}};
livro["exemplares"] = 3;                       // acrescenta/altera um campo
json lista = json::array();                    // array vazio
lista.push_back(livro);                        // adiciona ao array
std::string texto = livro.dump();              // objeto -> texto JSON
```

### Ler (de um texto)

```cpp
json dados = json::parse(req.body, nullptr, false);   // false = NÃO lançar exceção se for inválido
if (dados.is_discarded() || !dados.is_object()) {
    // JSON inválido (ou não é um objeto): responda 400
}
```

O `false` no terceiro argumento é importante: sem ele, `parse` lança uma exceção para JSON inválido. No starter kit, `util::lerCorpoObjeto` já faz isso e responde **400** sozinho.

### Consultar campos com segurança

| Quero… | Código |
|--------|--------|
| saber se o campo existe | `dados.contains("titulo")` |
| saber o tipo | `dados["titulo"].is_string()`, `.is_number_integer()`, `.is_number()`, `.is_null()` |
| ler como `std::string` | `dados["titulo"].get<std::string>()` |
| ler como inteiro | `dados["autor_id"].get<long long>()` |
| ler com valor padrão (quando o campo **não existe**) | `dados.value("exemplares", 1)` — mas lança exceção se o campo existir com outro tipo, inclusive `null` |

> **Cuidado:** `dados["x"]` e `.get<T>()` **lançam exceção** (ou têm comportamento indefinido, em objetos `const`) se o campo não existir ou tiver outro tipo. Por isso: **primeiro** `contains` e `is_...`, **depois** `get`. `dados.at("x")` lança exceção clara quando falta o campo.

## 2. O padrão de validação do starter kit

A função devolve uma **lista de mensagens de erro**; lista vazia significa que está tudo certo. Veja `src/rotas_recados.cpp`:

```cpp
json validarRecado(const json& dados) {
    json erros = json::array();

    if (!dados.contains("titulo") || !dados["titulo"].is_string() || dados["titulo"].get<std::string>().empty()) {
        erros.push_back("titulo e obrigatorio");
    } else if (dados["titulo"].get<std::string>().size() > 100) {
        erros.push_back("titulo deve ter no maximo 100 caracteres");
    }

    if (dados.contains("prioridade") && !dados["prioridade"].is_null()) {
        const json& p = dados["prioridade"];
        if (!p.is_number_integer() || p.get<long long>() < 1 || p.get<long long>() > 5) {
            erros.push_back("prioridade deve ser um numero inteiro de 1 a 5");
        }
    }
    return erros;
}
```

E na rota:

```cpp
json erros = validarRecado(dados);
if (!erros.empty()) {
    util::enviarErro(res, 422, "Dados invalidos", erros);   // devolve TODOS os problemas de uma vez
    return;
}
```

Resposta:

```json
{"erro": "Dados invalidos", "detalhes": ["titulo e obrigatorio", "prioridade deve ser um numero inteiro de 1 a 5"]}
```

Por que devolver **todos** os erros de uma vez? Porque o usuário corrige tudo em uma só tentativa, em vez de descobrir um erro por vez.

### Dica: texto com acentos conta bytes

`std::string::size()` conta **bytes**, e "ç" ou "ã" ocupam 2 bytes em UTF-8. Para limites como "até 100 caracteres" isso é uma aproximação aceitável no projeto (o banco recusa o que passar do tamanho da coluna). Se quiserem contar caracteres de verdade, contem só os bytes que **não** são de continuação (`(c & 0xC0) != 0x80`).

## 3. Qual código de status usar?

| Situação | Status | Exemplo |
|----------|:------:|---------|
| Corpo não é JSON, ou id não é número | **400** Bad Request | `POST` com `nao e json`; `GET /api/livros/abc` |
| Registro não existe | **404** Not Found | `GET /api/livros/9999` |
| Valor único repetido (ISBN, SKU, e-mail); registro em uso | **409** Conflict | segundo livro com o mesmo ISBN |
| JSON válido, mas **dados** inválidos | **422** Unprocessable Content | título vazio, ano 3000, preço negativo |
| Criado com sucesso | **201** Created | resposta do `POST` |
| Removido com sucesso (sem corpo) | **204** No Content | resposta do `DELETE` |
| Erro nosso (banco fora do ar, bug) | **500** Internal Server Error | — |

Diferença entre **400** e **422**: 400 é "não consegui nem entender a requisição" (JSON quebrado, id `abc`); 422 é "entendi, mas os valores não fazem sentido" (preço negativo).

## 4. Validações que quase todo tema precisa

| Regra | Como |
|-------|------|
| Campo obrigatório de texto | `contains` + `is_string` + não vazio |
| Tamanho máximo | `.size() <= N` |
| Número inteiro em uma faixa | `is_number_integer()` + comparações com `get<long long>()` |
| Número decimal ≥ 0 | `is_number()` + `get<double>() >= 0` |
| Valor de uma lista fixa (ex.: espécie) | procurar em um `std::vector<std::string>` ou `std::set` (Unidade 5) |
| Data no formato `AAAA-MM-DD` | tamanho 10, hífens nas posições 4 e 7, dígitos nas demais; confira o mês (1–12) e o dia |
| E-mail simples | tem um `@` com texto antes e um `.` depois |
| Chave estrangeira existe | uma consulta `SELECT id FROM ... WHERE id = ?` antes de gravar (guia 04) |

Crie funções pequenas e **reutilizáveis** (por exemplo, `bool textoObrigatorio(const json&, const char* campo, size_t max, json& erros)`), em vez de repetir o mesmo `if` dez vezes. Isso conta no critério de qualidade do código.

## 5. Exercícios

1. No starter kit, envie `POST /api/recados` com: título vazio; prioridade `"alta"` (texto); prioridade `9`; corpo `[1,2]`; corpo `abc`. Qual status cada um devolve? Por quê?
2. Escreva uma função `bool dataValida(const std::string&)` para o formato `AAAA-MM-DD` e teste com `2024-02-30`, `2024-13-01`, `24-1-1`.
3. Escreva uma função de validação de **uma** entidade do seu tema e a use em `POST` **e** `PUT` (o mesmo código nas duas rotas, sem copiar e colar).

Próximo: [guia 04 — banco de dados MariaDB](04-banco-mariadb.md).
