#include "rotas_tarefas.hpp"

#include <string>
#include <vector>

#include <nlohmann/json.hpp>

#include "http_util.hpp"
#include "projeto_repositorio.hpp"
#include "tarefa_repositorio.hpp"
#include "validacao.hpp"

using nlohmann::json;

namespace {

const std::vector<std::string> kStatusPermitidos = {"pendente", "andamento", "feito"};

// Confere os campos recebidos. Devolve uma lista de mensagens; vazia = tudo certo.
json validarTarefa(const json& dados) {
    json erros = json::array();
    validacao::textoObrigatorio(dados, "titulo", 100, erros);
    validacao::textoOpcional(dados, "descricao", 65535, erros);
    validacao::inteiroEmFaixa(dados, "projeto_id", 1, 4294967295LL, true, erros);
    validacao::valorDaLista(dados, "status", kStatusPermitidos, erros);
    validacao::inteiroEmFaixa(dados, "prioridade", 1, 5, false, erros);
    validacao::dataOpcional(dados, "prazo", erros);
    validacao::decimalEmFaixa(dados, "horas_estimadas", 0, 9999.9, erros);
    return erros;
}

// Lê e valida os filtros da URL (?busca=...&status=...&projeto_id=...). Erros vão para "erros".
FiltrosTarefa lerFiltros(const httplib::Request& req, json& erros) {
    FiltrosTarefa filtros;
    filtros.busca = req.get_param_value("busca");

    // Reaproveita as funções de validacao.hpp: monta um JSON com os valores recebidos e valida como no corpo do POST.
    json recebidos = json::object();
    if (req.has_param("status") && !req.get_param_value("status").empty()) {
        recebidos["status"] = req.get_param_value("status");
    }
    if (req.has_param("projeto_id") && !req.get_param_value("projeto_id").empty()) {
        const std::string texto = req.get_param_value("projeto_id");
        const bool soDigitos = texto.size() <= 10 && texto.find_first_not_of("0123456789") == std::string::npos;
        recebidos["projeto_id"] = soDigitos ? json(std::stoll(texto)) : json(texto);  // texto -> será recusado
    }
    validacao::valorDaLista(recebidos, "status", kStatusPermitidos, erros);
    validacao::inteiroEmFaixa(recebidos, "projeto_id", 1, 4294967295LL, false, erros);

    if (recebidos.contains("status")) {
        filtros.status = recebidos["status"].get<std::string>();
    }
    if (recebidos.contains("projeto_id") && recebidos["projeto_id"].is_number_integer()) {
        filtros.projetoId = std::to_string(recebidos["projeto_id"].get<long long>());
    }
    return filtros;
}

// Chave estrangeira: confere ANTES de gravar se o projeto existe, para responder 422 com uma mensagem clara
// (sem isso, o banco recusaria com o erro 1452 e a API devolveria um 409 genérico).
bool projetoExiste(Conexao& banco, const json& dados) {
    return !ProjetoRepositorio(banco).buscar(dados.at("projeto_id").get<long long>()).is_null();
}

}  // namespace

void registrarRotasTarefas(httplib::Server& servidor, const Config& config) {
    // LISTAR (com filtros opcionais: /api/tarefas?busca=site&status=pendente&projeto_id=1)
    servidor.Get("/api/tarefas", [&config](const httplib::Request& req, httplib::Response& res) {
        json erros = json::array();
        const FiltrosTarefa filtros = lerFiltros(req, erros);
        if (!erros.empty()) {
            util::enviarErro(res, 422, "Filtros invalidos", erros);
            return;
        }
        util::comBanco(config, res, [&](Conexao& banco) {
            TarefaRepositorio repositorio(banco);
            util::enviarJson(res, repositorio.listar(filtros));
        });
    });

    // RESUMO para o painel.
    // ATENCAO: esta rota precisa ser registrada ANTES de "/api/tarefas/:id". O httplib testa as rotas na ordem em que
    // foram registradas; se o ":id" viesse primeiro, ele receberia a palavra "resumo" e responderia 400 "Id invalido".
    servidor.Get("/api/tarefas/resumo", [&config](const httplib::Request&, httplib::Response& res) {
        util::comBanco(config, res, [&](Conexao& banco) {
            TarefaRepositorio repositorio(banco);
            util::enviarJson(res, repositorio.resumo());
        });
    });

    // BUSCAR UMA
    servidor.Get("/api/tarefas/:id", [&config](const httplib::Request& req, httplib::Response& res) {
        long long id = 0;
        if (!util::lerId(req, res, id)) {
            return;
        }
        util::comBanco(config, res, [&](Conexao& banco) {
            TarefaRepositorio repositorio(banco);
            json tarefa = repositorio.buscar(id);
            if (tarefa.is_null()) {
                util::enviarErro(res, 404, "Tarefa nao encontrada");
                return;
            }
            util::enviarJson(res, tarefa);
        });
    });

    // CRIAR
    servidor.Post("/api/tarefas", [&config](const httplib::Request& req, httplib::Response& res) {
        json dados;
        if (!util::lerCorpoObjeto(req, res, dados)) {
            return;
        }
        json erros = validarTarefa(dados);
        if (!erros.empty()) {
            util::enviarErro(res, 422, "Dados invalidos", erros);
            return;
        }
        util::comBanco(config, res, [&](Conexao& banco) {
            if (!projetoExiste(banco, dados)) {
                util::enviarErro(res, 422, "Dados invalidos", json::array({"projeto_id nao existe"}));
                return;
            }
            TarefaRepositorio repositorio(banco);
            util::enviarJson(res, repositorio.criar(dados), 201);
        });
    });

    // ATUALIZAR (substitui todos os campos)
    servidor.Put("/api/tarefas/:id", [&config](const httplib::Request& req, httplib::Response& res) {
        long long id = 0;
        if (!util::lerId(req, res, id)) {
            return;
        }
        json dados;
        if (!util::lerCorpoObjeto(req, res, dados)) {
            return;
        }
        json erros = validarTarefa(dados);
        if (!erros.empty()) {
            util::enviarErro(res, 422, "Dados invalidos", erros);
            return;
        }
        util::comBanco(config, res, [&](Conexao& banco) {
            if (!projetoExiste(banco, dados)) {
                util::enviarErro(res, 422, "Dados invalidos", json::array({"projeto_id nao existe"}));
                return;
            }
            TarefaRepositorio repositorio(banco);
            json atualizada = repositorio.atualizar(id, dados);
            if (atualizada.is_null()) {
                util::enviarErro(res, 404, "Tarefa nao encontrada");
                return;
            }
            util::enviarJson(res, atualizada);
        });
    });

    // CONCLUIR: uma AÇÃO sobre a tarefa (não é um PUT com todos os campos). Boa para botões como "Concluir".
    servidor.Post("/api/tarefas/:id/concluir", [&config](const httplib::Request& req, httplib::Response& res) {
        long long id = 0;
        if (!util::lerId(req, res, id)) {
            return;
        }
        util::comBanco(config, res, [&](Conexao& banco) {
            TarefaRepositorio repositorio(banco);
            const json tarefa = repositorio.buscar(id);
            if (tarefa.is_null()) {
                util::enviarErro(res, 404, "Tarefa nao encontrada");
                return;
            }
            if (tarefa["status"] == "feito") {
                util::enviarErro(res, 409, "A tarefa ja esta concluida");  // regra de negócio -> 409
                return;
            }
            util::enviarJson(res, repositorio.concluir(id));
        });
    });

    // REMOVER
    servidor.Delete("/api/tarefas/:id", [&config](const httplib::Request& req, httplib::Response& res) {
        long long id = 0;
        if (!util::lerId(req, res, id)) {
            return;
        }
        util::comBanco(config, res, [&](Conexao& banco) {
            TarefaRepositorio repositorio(banco);
            if (!repositorio.remover(id)) {
                util::enviarErro(res, 404, "Tarefa nao encontrada");
                return;
            }
            res.status = 204;  // sem conteudo
        });
    });
}
