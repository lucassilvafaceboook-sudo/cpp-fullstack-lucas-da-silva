// Rotas de atendimentos: pedido de consulta (com sintomas) ou só vacinação,
// feito pelo dono do pet; o veterinário registra observações e conclui.
#include "rotas.hpp"

static const std::string SELECT_ATENDIMENTO =
    "SELECT a.id, a.pet_id, a.tipo, a.sintomas, a.status, a.observacoes, a.criado_em, "
    "       p.nome AS pet_nome, p.especie AS pet_especie, "
    "       t.id AS tutor_id, t.nome AS tutor_nome, t.telefone AS tutor_telefone "
    "  FROM atendimentos a "
    "  JOIN pets p    ON p.id = a.pet_id "
    "  JOIN tutores t ON t.id = p.tutor_id";

static json textoOuNull(const Linha& l, const std::string& coluna) {
    return l.nulo(coluna) ? json(nullptr) : json(l.texto(coluna));
}

static json atendimentoParaJson(const Linha& l) {
    return {
        {"id", l.inteiro("id")},
        {"pet_id", l.inteiro("pet_id")},
        {"tipo", l.texto("tipo")},
        {"sintomas", textoOuNull(l, "sintomas")},
        {"status", l.texto("status")},
        {"observacoes", textoOuNull(l, "observacoes")},
        {"criado_em", l.texto("criado_em")},
        {"pet_nome", l.texto("pet_nome")},
        {"pet_especie", l.texto("pet_especie")},
        {"tutor_id", l.inteiro("tutor_id")},
        {"tutor_nome", l.texto("tutor_nome")},
        {"tutor_telefone", l.texto("tutor_telefone")},
    };
}

void registrarRotasAtendimentos(httplib::Server& servidor) {
    // GET /api/atendimentos?status=aguardando&pet_id=
    servidor.Get("/api/atendimentos", [](const httplib::Request& req, httplib::Response& res) {
        auto u = exigirLogin(req, res);
        if (!u) return;
        std::vector<std::string> filtros;
        std::vector<std::string> parametros;
        if (auto dono = filtroDono(*u, parametros); !dono.empty()) filtros.push_back(dono);
        if (!req.get_param_value("status").empty()) {
            filtros.push_back("a.status = ?");
            parametros.push_back(req.get_param_value("status"));
        }
        if (!req.get_param_value("pet_id").empty()) {
            filtros.push_back("a.pet_id = ?");
            parametros.push_back(req.get_param_value("pet_id"));
        }
        std::string where;
        for (size_t i = 0; i < filtros.size(); ++i) where += (i == 0 ? " WHERE " : " AND ") + filtros[i];

        json lista = json::array();
        for (const auto& l : Conexao::consultar(
                 SELECT_ATENDIMENTO + where + " ORDER BY a.status = 'concluido', a.criado_em DESC, a.id DESC", parametros))
            lista.push_back(atendimentoParaJson(l));
        enviarJson(res, 200, lista);
    });

    // POST /api/atendimentos { pet_id, tipo, sintomas }
    servidor.Post("/api/atendimentos", [](const httplib::Request& req, httplib::Response& res) {
        auto u = exigirLogin(req, res);
        if (!u) return;
        const json corpo = lerCorpo(req);
        Validacao v = validarAtendimento(corpo);
        const std::string petId = campoTexto(corpo, "pet_id");
        if (petId.empty()) v.erros["pet_id"] = "Escolha o pet.";
        else if (!buscarPet(*u, petId)) v.erros["pet_id"] = "Pet não encontrado.";
        if (!v.ok()) return responder422(res, v.erros);

        auto r = Conexao::executar("INSERT INTO atendimentos (pet_id, tipo, sintomas) VALUES (?, ?, NULLIF(?, ''))",
                                   {petId, v.dados["tipo"], v.dados["sintomas"]});
        auto a = Conexao::consultarUm(SELECT_ATENDIMENTO + " WHERE a.id = ?", {std::to_string(r.idInserido)});
        enviarJson(res, 201, atendimentoParaJson(*a));
    });

    // PATCH /api/atendimentos/:id { status, observacoes } — só a equipe da clínica
    servidor.Patch("/api/atendimentos/:id", [](const httplib::Request& req, httplib::Response& res) {
        if (!exigirVet(req, res)) return;
        const std::string id = req.path_params.at("id");
        std::optional<Linha> a;
        if (idValido(id)) a = Conexao::consultarUm("SELECT * FROM atendimentos WHERE id = ?", {id});
        if (!a) return enviarErro(res, 404, "Atendimento não encontrado.");

        const json corpo = lerCorpo(req);
        const std::string status = corpo.contains("status") ? campoTexto(corpo, "status") : a->texto("status");
        const std::string observacoes = corpo.contains("observacoes") ? campoTexto(corpo, "observacoes")
                                                                      : a->texto("observacoes");
        if (status != "aguardando" && status != "concluido")
            return responder422(res, {{"status", "Status inválido. Use: aguardando ou concluido."}});
        if (tamanho(observacoes) > 2000)
            return responder422(res, {{"observacoes", "Observações podem ter até 2000 caracteres."}});

        Conexao::executar("UPDATE atendimentos SET status = ?, observacoes = NULLIF(?, '') WHERE id = ?",
                          {status, observacoes, id});
        auto atualizado = Conexao::consultarUm(SELECT_ATENDIMENTO + " WHERE a.id = ?", {id});
        enviarJson(res, 200, atendimentoParaJson(*atualizado));
    });

    // GET /api/tipos-atendimento
    servidor.Get("/api/tipos-atendimento", [](const httplib::Request& req, httplib::Response& res) {
        if (!exigirLogin(req, res)) return;
        enviarJson(res, 200, json::array({"consulta", "vacina"}));
    });
}
