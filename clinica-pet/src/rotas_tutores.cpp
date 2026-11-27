// Rotas de tutores (entidade de apoio). A lista tem telefone e e-mail de todo mundo,
// então todas estas rotas são só para a equipe da clínica (veterinário).
#include "rotas.hpp"

static const std::string SELECT_TUTOR =
    "SELECT t.id, t.nome, t.telefone, t.email, COUNT(p.id) AS qtd_pets, "
    "       EXISTS (SELECT 1 FROM usuarios u WHERE u.tutor_id = t.id) AS tem_conta "
    "  FROM tutores t LEFT JOIN pets p ON p.tutor_id = t.id";

static json tutorParaJson(const Linha& l) {
    return {
        {"id", l.inteiro("id")},
        {"nome", l.texto("nome")},
        {"telefone", l.texto("telefone")},
        {"email", l.nulo("email") ? json(nullptr) : json(l.texto("email"))},
        {"qtd_pets", l.inteiro("qtd_pets")},
        {"tem_conta", l.inteiro("tem_conta") != 0},
    };
}

static std::optional<Linha> buscarTutor(const std::string& id) {
    if (!idValido(id)) return std::nullopt;
    return Conexao::consultarUm(SELECT_TUTOR + " WHERE t.id = ? GROUP BY t.id", {id});
}

static void tutor404(httplib::Response& res) { enviarErro(res, 404, "Tutor não encontrado."); }

static bool emailEmUso(const std::string& email, const std::string& ignorarId = "0") {
    if (email.empty()) return false;
    return Conexao::consultarUm("SELECT id FROM tutores WHERE email = ? AND id <> ?", {email, ignorarId}).has_value();
}

static void responder409Email(httplib::Response& res, const std::string& email) {
    enviarJson(res, 409, {{"erro", "Já existe um tutor com o e-mail " + email + "."},
                          {"campos", {{"email", "E-mail já cadastrado."}}}});
}

void registrarRotasTutores(httplib::Server& servidor) {
    // GET /api/tutores
    servidor.Get("/api/tutores", [](const httplib::Request& req, httplib::Response& res) {
        if (!exigirVet(req, res)) return;
        json lista = json::array();
        for (const auto& l : Conexao::consultar(SELECT_TUTOR + " GROUP BY t.id ORDER BY t.nome"))
            lista.push_back(tutorParaJson(l));
        enviarJson(res, 200, lista);
    });

    // GET /api/tutores/:id
    servidor.Get("/api/tutores/:id", [](const httplib::Request& req, httplib::Response& res) {
        if (!exigirVet(req, res)) return;
        auto t = buscarTutor(req.path_params.at("id"));
        if (!t) return tutor404(res);
        enviarJson(res, 200, tutorParaJson(*t));
    });

    // GET /api/tutores/:id/pets
    servidor.Get("/api/tutores/:id/pets", [](const httplib::Request& req, httplib::Response& res) {
        if (!exigirVet(req, res)) return;
        const std::string id = req.path_params.at("id");
        if (!idValido(id) || !tutorExiste(id)) return tutor404(res);
        json lista = json::array();
        for (const auto& l : Conexao::consultar(SELECT_PET + " WHERE p.tutor_id = ? ORDER BY p.nome", {id}))
            lista.push_back(petParaJson(l));
        enviarJson(res, 200, lista);
    });

    // POST /api/tutores
    servidor.Post("/api/tutores", [](const httplib::Request& req, httplib::Response& res) {
        if (!exigirVet(req, res)) return;
        Validacao v = validarTutor(lerCorpo(req));
        if (!v.ok()) return responder422(res, v.erros);
        auto& d = v.dados;
        if (emailEmUso(d["email"])) return responder409Email(res, d["email"]);

        auto r = Conexao::executar("INSERT INTO tutores (nome, telefone, email) VALUES (?, ?, NULLIF(?, ''))",
                                   {d["nome"], d["telefone"], d["email"]});
        const std::string id = std::to_string(r.idInserido);
        res.set_header("Location", "/api/tutores/" + id);
        enviarJson(res, 201, tutorParaJson(*buscarTutor(id)));
    });

    // PUT /api/tutores/:id
    servidor.Put("/api/tutores/:id", [](const httplib::Request& req, httplib::Response& res) {
        if (!exigirVet(req, res)) return;
        const std::string id = req.path_params.at("id");
        if (!idValido(id) || !tutorExiste(id)) return tutor404(res);
        Validacao v = validarTutor(lerCorpo(req));
        if (!v.ok()) return responder422(res, v.erros);
        auto& d = v.dados;
        if (emailEmUso(d["email"], id)) return responder409Email(res, d["email"]);

        Conexao::executar("UPDATE tutores SET nome = ?, telefone = ?, email = NULLIF(?, '') WHERE id = ?",
                          {d["nome"], d["telefone"], d["email"], id});
        enviarJson(res, 200, tutorParaJson(*buscarTutor(id)));
    });

    // DELETE /api/tutores/:id
    servidor.Delete("/api/tutores/:id", [](const httplib::Request& req, httplib::Response& res) {
        if (!exigirVet(req, res)) return;
        const std::string id = req.path_params.at("id");
        auto t = buscarTutor(id);
        if (!t) return tutor404(res);
        if (const auto qtd = t->inteiro("qtd_pets"); qtd > 0)
            return enviarErro(res, 409, "Não é possível excluir " + t->texto("nome") + ": ainda tem " + std::to_string(qtd) +
                                            " pet(s) cadastrado(s). Transfira ou exclua os pets primeiro.");
        if (t->inteiro("tem_conta"))
            return enviarErro(res, 409, "Não é possível excluir " + t->texto("nome") +
                                            ": esse tutor tem uma conta de acesso ao sistema.");
        Conexao::executar("DELETE FROM tutores WHERE id = ?", {id});
        res.status = 204;
    });
}
