# Guia 2 — Sua primeira rota HTTP

**Pré-requisito:** o starter kit rodando em todos os computadores da equipe ([guia 1](01-preparar-ambiente.md)).
**Objetivo:** entender o que é uma rota e criar três rotas novas, sem banco de dados ainda.

🎬 **No demo:** o passo 2 mostra uma rota de verdade, com repositório e validação ([`demo-passo-2`](../demo/ROTEIRO-LIVE-CODING.md)).

## 1. O que acontece quando o navegador pede uma página

Uma requisição HTTP tem quatro partes que nos interessam:

| Parte | Exemplo | Para que serve |
|-------|---------|----------------|
| **Método** | `GET`, `POST`, `PUT`, `DELETE` | o que se quer fazer |
| **Caminho** | `/api/recados/3` | sobre qual recurso |
| **Corpo** | `{"titulo":"Oi"}` | os dados enviados (em `POST` e `PUT`) |
| **Parâmetros** | `?busca=pao` | filtros opcionais, depois do `?` |

E a resposta traz um **código de status** (200 = deu certo, 404 = não existe, 422 = dados inválidos…) e, em geral, um **corpo em JSON**.

| Método | Significado | Exemplo | Sucesso |
|--------|-------------|---------|:-------:|
| `GET` | ler | `GET /api/recados` | 200 |
| `POST` | criar | `POST /api/recados` | 201 |
| `PUT` | substituir/atualizar | `PUT /api/recados/3` | 200 |
| `DELETE` | remover | `DELETE /api/recados/3` | 204 |

## 2. Anatomia de uma rota no starter kit

Abra `src/main.cpp` e encontre a rota de saúde:

```cpp
servidor.Get("/api/saude", [](const httplib::Request&, httplib::Response& res) {
    util::enviarJson(res, {{"status", "ok"}});
});
```

Leia assim: *"quando chegar um **GET** em **/api/saude**, execute esta **função lambda**, que recebe a requisição e a resposta e preenche a resposta"*.

- `servidor` é um `httplib::Server`; `Get`, `Post`, `Put` e `Delete` registram rotas.
- A **lambda** (Unidade 5) é a função que roda a cada requisição. Entre os colchetes `[ ]` vai o que ela "captura" do lado de fora: nas rotas do banco, `[&config]` dá acesso à configuração.
- `req` (a requisição) traz o corpo (`req.body`), os parâmetros de caminho (`req.path_params`) e os parâmetros de consulta (`req.get_param_value("busca")`).
- `res` (a resposta) é preenchida por funções do `http_util.hpp`: `util::enviarJson(res, objeto, status)` e `util::enviarErro(res, status, "mensagem")`.

## 3. Mão na massa: três rotas

Crie as rotas **dentro do `main.cpp`**, logo abaixo da rota `/api/saude`. A cada rota nova: compile, **reinicie o servidor** e teste.

### Rota A — `GET /api/ola`

```cpp
servidor.Get("/api/ola", [](const httplib::Request&, httplib::Response& res) {
    util::enviarJson(res, {{"mensagem", "Ola, turma!"}});
});
```

Teste no navegador: <http://localhost:8080/api/ola>. Ou, no terminal: `curl http://localhost:8080/api/ola`.

### Rota B — com parâmetro no caminho: `GET /api/ola/:nome`

```cpp
servidor.Get("/api/ola/:nome", [](const httplib::Request& req, httplib::Response& res) {
    const std::string nome = req.path_params.at("nome");
    util::enviarJson(res, {{"mensagem", "Ola, " + nome + "!"}});
});
```

`http://localhost:8080/api/ola/Maria` deve devolver `{"mensagem":"Ola, Maria!"}`.

### Rota C — com parâmetros de consulta: `GET /api/somar?a=2&b=3`

```cpp
servidor.Get("/api/somar", [](const httplib::Request& req, httplib::Response& res) {
    if (!req.has_param("a") || !req.has_param("b")) {
        util::enviarErro(res, 400, "Informe os parametros a e b");
        return;
    }
    try {
        const double a = std::stod(req.get_param_value("a"));
        const double b = std::stod(req.get_param_value("b"));
        util::enviarJson(res, {{"resultado", a + b}});
    } catch (const std::exception&) {
        util::enviarErro(res, 400, "a e b devem ser numeros");
    }
});
```

Teste os caminhos felizes **e os de erro**: `/api/somar?a=2&b=3`, `/api/somar?a=2` e `/api/somar?a=2&b=banana`. Um bom servidor responde com um erro claro e continua de pé.

## 4. Desafios (ajudam no projeto)

1. `GET /api/hora`: devolva a data e hora do servidor em JSON (`<ctime>` ou `<chrono>`).
2. `GET /api/dobro/:n`: devolva o dobro de `n`, com **400** se `n` não for um inteiro válido (veja como `util::lerId` faz isso).
3. `POST /api/eco`: receba um corpo JSON qualquer e devolva o mesmo JSON dentro de `{"recebido": ...}` (use `util::lerCorpoObjeto`; veja o guia 03).
4. Teste um `POST` com `curl`: `curl -X POST http://localhost:8080/api/eco -d '{"a":1}'`.

## 5. Testando rotas: três ferramentas

| Ferramenta | Boa para |
|------------|----------|
| **Navegador** | só `GET` (digite o endereço) |
| **`curl`** (terminal do MSYS2) | todos os métodos; fácil de repetir e copiar para o README |
| **Thunder Client** (extensão do VS Code) | todos os métodos com interface gráfica; ótimo no PowerShell/Windows |

`curl` útil: `-i` mostra o status e os cabeçalhos; `-X POST` escolhe o método; `-d '{...}'` envia o corpo.

```bash
curl -i http://localhost:8080/api/recados/9999     # deve mostrar "HTTP/1.1 404"
```

## 6. Erros comuns

| Sintoma | Causa provável |
|---------|----------------|
| Mudei o código e a rota nova dá 404 | Esqueceu de **compilar** e/ou **reiniciar** o servidor. |
| `ERRO: nao foi possivel usar a porta 8080` | O servidor antigo ainda está rodando. Feche a janela dele (ou `Ctrl+C`) antes de iniciar o novo. |
| A rota dá 404 mas o código parece certo | Ordem e caminho: `/api/ola/:nome` não casa com `/api/ola` (sem nome). Confira o caminho exato. |
| O servidor "caiu" ao enviar dado inválido | Uma exceção não foi tratada (ex.: `std::stod` com texto). Use `try/catch` e responda **400**. O `main.cpp` tem um *exception handler* de segurança, mas não confie só nele. |

Próximo: [guia 03 — JSON e validação](03-json-e-validacao.md).
