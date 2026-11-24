#include "rotas_recados.hpp"

#include <string>

#include <nlohmann/json.hpp>

#include "http_util.hpp"
#include "recado_repositorio.hpp"

using nlohmann::json;

namespace {

// Confere os campos recebidos. Devolve uma lista de mensagens; vazia = tudo certo.
json validarRecado(const json& dados) {
    json erros = json::array();

    if (!dados.contains("titulo") || !dados["titulo"].is_string() || dados["titulo"].get<std::string>().empty()) {
        erros.push_back("titulo e obrigatorio");
    } else if (dados["titulo"].get<std::string>().size() > 100) {
        erros.push_back("titulo deve ter no maximo 100 caracteres");
    }

    if (dados.contains("mensagem") && !dados["mensagem"].is_null() && !dados["mensagem"].is_string()) {
        erros.push_back("mensagem deve ser texto");
    }

    if (dados.contains("prioridade") && !dados["prioridade"].is_null()) {
        const json& p = dados["prioridade"];
        if (!p.is_number_integer() || p.get<long long>() < 1 || p.get<long long>() > 5) {
            erros.push_back("prioridade deve ser um numero inteiro de 1 a 5");
        }
    }
    return erros;
}

}  // namespace

void registrarRotasRecados(httplib::Server& servidor, const Config& config) {
    // LISTAR (com busca opcional: /api/recados?busca=mercado)
    servidor.Get("/api/recados", [&config](const httplib::Request& req, httplib::Response& res) {
        util::comBanco(config, res, [&](Conexao& banco) {
            RecadoRepositorio repositorio(banco);
            const std::string busca = req.has_param("busca") ? req.get_param_value("busca") : "";
            util::enviarJson(res, repositorio.listar(busca));
        });
    });

    // BUSCAR UM
    servidor.Get("/api/recados/:id", [&config](const httplib::Request& req, httplib::Response& res) {
        long long id = 0;
        if (!util::lerId(req, res, id)) {
            return;
        }
        util::comBanco(config, res, [&](Conexao& banco) {
            RecadoRepositorio repositorio(banco);
            json recado = repositorio.buscar(id);
            if (recado.is_null()) {
                util::enviarErro(res, 404, "Recado nao encontrado");
                return;
            }
            util::enviarJson(res, recado);
        });
    });

    // CRIAR
    servidor.Post("/api/recados", [&config](const httplib::Request& req, httplib::Response& res) {
        json dados;
        if (!util::lerCorpoObjeto(req, res, dados)) {
            return;
        }
        json erros = validarRecado(dados);
        if (!erros.empty()) {
            util::enviarErro(res, 422, "Dados invalidos", erros);
            return;
        }
        util::comBanco(config, res, [&](Conexao& banco) {
            RecadoRepositorio repositorio(banco);
            util::enviarJson(res, repositorio.criar(dados), 201);
        });
    });

    // ATUALIZAR (substitui todos os campos)
    servidor.Put("/api/recados/:id", [&config](const httplib::Request& req, httplib::Response& res) {
        long long id = 0;
        if (!util::lerId(req, res, id)) {
            return;
        }
        json dados;
        if (!util::lerCorpoObjeto(req, res, dados)) {
            return;
        }
        json erros = validarRecado(dados);
        if (!erros.empty()) {
            util::enviarErro(res, 422, "Dados invalidos", erros);
            return;
        }
        util::comBanco(config, res, [&](Conexao& banco) {
            RecadoRepositorio repositorio(banco);
            json atualizado = repositorio.atualizar(id, dados);
            if (atualizado.is_null()) {
                util::enviarErro(res, 404, "Recado nao encontrado");
                return;
            }
            util::enviarJson(res, atualizado);
        });
    });

    // REMOVER
    servidor.Delete("/api/recados/:id", [&config](const httplib::Request& req, httplib::Response& res) {
        long long id = 0;
        if (!util::lerId(req, res, id)) {
            return;
        }
        util::comBanco(config, res, [&](Conexao& banco) {
            RecadoRepositorio repositorio(banco);
            if (!repositorio.remover(id)) {
                util::enviarErro(res, 404, "Recado nao encontrado");
                return;
            }
            res.status = 204;  // sem conteudo
        });
    });
}
