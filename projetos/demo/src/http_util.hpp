// http_util.hpp - Funções auxiliares para as rotas (respostas JSON, leitura do corpo, erros de banco).
#pragma once

#include <exception>
#include <iostream>
#include <string>

#include <httplib.h>
#include <nlohmann/json.hpp>

#include "banco.hpp"
#include "config.hpp"

namespace util {

// Envia um JSON com o status HTTP informado (200 = OK, 201 = criado, ...).
inline void enviarJson(httplib::Response& res, const nlohmann::json& corpo, int status = 200) {
    res.status = status;
    res.set_content(corpo.dump(-1, ' ', false, nlohmann::json::error_handler_t::replace),
                    "application/json; charset=utf-8");
}

// Envia {"erro": "mensagem"} (e, se houver, "detalhes": [...]) com o status informado.
inline void enviarErro(httplib::Response& res, int status, const std::string& mensagem,
                       const nlohmann::json& detalhes = nlohmann::json()) {
    nlohmann::json corpo = {{"erro", mensagem}};
    if (!detalhes.is_null()) {
        corpo["detalhes"] = detalhes;
    }
    enviarJson(res, corpo, status);
}

// Lê o corpo da requisição como um objeto JSON. Se for inválido, já responde 400 e devolve false.
inline bool lerCorpoObjeto(const httplib::Request& req, httplib::Response& res, nlohmann::json& corpo) {
    corpo = nlohmann::json::parse(req.body, nullptr, false);
    if (corpo.is_discarded() || !corpo.is_object()) {
        enviarErro(res, 400, "O corpo da requisicao deve ser um objeto JSON valido");
        return false;
    }
    return true;
}

// Lê o parâmetro de caminho ":id" (por exemplo, /api/tarefas/:id). Se for inválido, responde 400.
inline bool lerId(const httplib::Request& req, httplib::Response& res, long long& id) {
    try {
        const std::string& texto = req.path_params.at("id");
        std::size_t usados = 0;
        id = std::stoll(texto, &usados);
        if (usados == texto.size() && id > 0) {
            return true;
        }
    } catch (const std::exception&) {
    }
    enviarErro(res, 400, "Id invalido");
    return false;
}

// Abre uma conexão, executa o corpo da rota e traduz erros de banco para respostas HTTP:
//   chave duplicada -> 409, chave estrangeira -> 409, CHECK violado -> 422,
//   qualquer outro erro de banco -> 500 (sem expor detalhes internos).
// Uso:  comBanco(config, res, [&](Conexao& banco) { ...usa banco.consultar/executar... });
template <typename Corpo>
void comBanco(const Config& config, httplib::Response& res, Corpo&& corpo) {
    try {
        Conexao conexao(config);
        corpo(conexao);
    } catch (const ErroBanco& erro) {
        std::cerr << "[erro de banco " << erro.codigo() << "] " << erro.what() << '\n';
        if (erro.chaveDuplicada()) {
            enviarErro(res, 409, "Ja existe um registro com este valor unico");
        } else if (erro.violacaoDeChaveEstrangeira()) {
            enviarErro(res, 409, "Operacao bloqueada por registros relacionados");
        } else if (erro.restricaoViolada()) {
            enviarErro(res, 422, "Valor nao permitido pelas regras do banco de dados");
        } else {
            enviarErro(res, 500, "Erro no banco de dados");
        }
    } catch (const std::exception& erro) {
        std::cerr << "[erro interno] " << erro.what() << '\n';
        enviarErro(res, 500, "Erro interno do servidor");
    }
}

}  // namespace util
