// Rotas de pets (entidade principal: CRUD completo) e resumo por espécie.
#include "auth.hpp"
#include "banco.hpp"
#include "rotas.hpp"

const std::string SELECT_PET =
    "SELECT p.id, p.nome, p.especie, p.raca, p.mes_nascimento, p.ano_nascimento, p.peso_kg, "
    "       p.tutor_id, t.nome AS tutor_nome, t.telefone AS tutor_telefone "
    "  FROM pets p "
    "  JOIN tutores t ON t.id = p.tutor_id";

// Valor da coluna como número inteiro, ou null
static json inteiroOuNull(const Linha& l, const std::string& coluna) {
    return l.nulo(coluna) ? json(nullptr) : json(l.inteiro(coluna));
}

json petParaJson(const Linha& l) {
    return {
        {"id", l.inteiro("id")},
        {"nome", l.texto("nome")},
        {"especie", l.texto("especie")},
        {"raca", l.nulo("raca") ? json(nullptr) : json(l.texto("raca"))},
        {"mes_nascimento", inteiroOuNull(l, "mes_nascimento")},
        {"ano_nascimento", inteiroOuNull(l, "ano_nascimento")},
        {"peso_kg", l.nulo("peso_kg") ? json(nullptr) : json(l.decimal("peso_kg"))},
        {"tutor_id", l.inteiro("tutor_id")},
        {"tutor_nome", l.texto("tutor_nome")},
        {"tutor_telefone", l.texto("tutor_telefone")},
        {"idade", calcularIdade(static_cast<int>(l.inteiro("ano_nascimento")),
                                static_cast<int>(l.inteiro("mes_nascimento")))},
    };
}

bool tutorExiste(const std::string& id) {
    return Conexao::consultarUm("SELECT id FROM tutores WHERE id = ?", {id}).has_value();
}

// Cliente só enxerga os pets do próprio cadastro de tutor; veterinário vê todos.
std::string filtroDono(const Usuario& usuario, std::vector<std::string>& parametros) {
    if (usuario.ehVet()) return "";
    parametros.push_back(std::to_string(usuario.tutorId));
    return "p.tutor_id = ?";
}

// Pet de outra pessoa = "não encontrado" (404): nem confirma que ele existe.
std::optional<Linha> buscarPet(const Usuario& usuario, const std::string& id) {
    if (!idValido(id)) return std::nullopt;
    std::vector<std::string> parametros = {id};
    const std::string dono = filtroDono(usuario, parametros);
    return Conexao::consultarUm(SELECT_PET + " WHERE p.id = ?" + (dono.empty() ? "" : " AND " + dono), parametros);
}

static void pet404(httplib::Response& res) { enviarErro(res, 404, "Pet não encontrado."); }

// Valida o corpo do pet. Para cliente, o tutor é sempre ele mesmo (ignora o que vier no corpo).
static Validacao validarPetDaRequisicao(const Usuario& usuario, json corpo) {
    if (!usuario.ehVet()) corpo["tutor_id"] = usuario.tutorId;
    Validacao v = validarPet(corpo);
    if (!v.erros.count("tutor_id") && !tutorExiste(v.dados["tutor_id"]))
        v.erros["tutor_id"] = "Tutor " + v.dados["tutor_id"] + " não existe.";
    return v;
}

static void criarAtendimento(const std::string& petId, Dados& motivo) {
    Conexao::executar("INSERT INTO atendimentos (pet_id, tipo, sintomas) VALUES (?, ?, NULLIF(?, ''))",
                      {petId, motivo["tipo"], motivo["sintomas"]});
}

void registrarRotasPets(httplib::Server& servidor) {
    // GET /api/pets?busca=&especie=&tutor_id=
    servidor.Get("/api/pets", [](const httplib::Request& req, httplib::Response& res) {
        auto u = exigirLogin(req, res);
        if (!u) return;
        std::vector<std::string> filtros;
        std::vector<std::string> parametros;
        if (auto dono = filtroDono(*u, parametros); !dono.empty()) filtros.push_back(dono);

        const std::string busca = aparar(req.get_param_value("busca"));
        if (!busca.empty()) {
            filtros.push_back("(p.nome LIKE ? OR p.raca LIKE ?)");
            parametros.push_back("%" + busca + "%");
            parametros.push_back("%" + busca + "%");
        }
        if (req.has_param("especie") && !req.get_param_value("especie").empty()) {
            filtros.push_back("p.especie = ?");
            parametros.push_back(req.get_param_value("especie"));
        }
        if (u->ehVet() && req.has_param("tutor_id") && !req.get_param_value("tutor_id").empty()) {
            filtros.push_back("p.tutor_id = ?");
            parametros.push_back(req.get_param_value("tutor_id"));
        }

        std::string where;
        for (size_t i = 0; i < filtros.size(); ++i) where += (i == 0 ? " WHERE " : " AND ") + filtros[i];

        json lista = json::array();
        for (const auto& linha : Conexao::consultar(SELECT_PET + where + " ORDER BY p.nome", parametros))
            lista.push_back(petParaJson(linha));
        enviarJson(res, 200, lista);
    });

    // GET /api/pets/resumo — números da clínica inteira, só para a equipe.
    // Precisa ser registrada ANTES de /api/pets/:id
    servidor.Get("/api/pets/resumo", [](const httplib::Request& req, httplib::Response& res) {
        if (!exigirVet(req, res)) return;
        auto geral = Conexao::consultarUm("SELECT COUNT(*) AS total, ROUND(AVG(peso_kg), 2) AS peso_medio FROM pets");
        json porEspecie = json::array();
        for (const auto& l : Conexao::consultar(
                 "SELECT especie, COUNT(*) AS quantidade, ROUND(AVG(peso_kg), 2) AS peso_medio "
                 "  FROM pets GROUP BY especie ORDER BY quantidade DESC")) {
            porEspecie.push_back({{"especie", l.texto("especie")},
                                  {"quantidade", l.inteiro("quantidade")},
                                  {"peso_medio", l.nulo("peso_medio") ? json(nullptr) : json(l.decimal("peso_medio"))}});
        }
        enviarJson(res, 200, {{"total", geral->inteiro("total")},
                              {"peso_medio", geral->nulo("peso_medio") ? json(nullptr) : json(geral->decimal("peso_medio"))},
                              {"por_especie", porEspecie}});
    });

    // GET /api/pets/:id
    servidor.Get("/api/pets/:id", [](const httplib::Request& req, httplib::Response& res) {
        auto u = exigirLogin(req, res);
        if (!u) return;
        auto pet = buscarPet(*u, req.path_params.at("id"));
        if (!pet) return pet404(res);
        enviarJson(res, 200, petParaJson(*pet));
    });

    // POST /api/pets
    // Cliente precisa dizer o motivo da visita junto: { ..., tipo: "consulta"|"vacina", sintomas }
    // Veterinário pode mandar o motivo ou não.
    servidor.Post("/api/pets", [](const httplib::Request& req, httplib::Response& res) {
        auto u = exigirLogin(req, res);
        if (!u) return;
        const json corpo = lerCorpo(req);
        Validacao v = validarPetDaRequisicao(*u, corpo);

        const bool querAtendimento = !u->ehVet() || !campoTexto(corpo, "tipo").empty();
        Validacao motivo;
        if (querAtendimento) {
            motivo = validarAtendimento(corpo);
            v.erros.insert(motivo.erros.begin(), motivo.erros.end());
        }
        if (!v.ok()) return responder422(res, v.erros);

        auto& d = v.dados;
        auto r = Conexao::executar(
            "INSERT INTO pets (nome, especie, raca, mes_nascimento, ano_nascimento, peso_kg, tutor_id) "
            "VALUES (?, ?, NULLIF(?, ''), NULLIF(?, ''), NULLIF(?, ''), NULLIF(?, ''), ?)",
            {d["nome"], d["especie"], d["raca"], d["mes_nascimento"], d["ano_nascimento"], d["peso_kg"], d["tutor_id"]});
        const std::string id = std::to_string(r.idInserido);
        if (querAtendimento) criarAtendimento(id, motivo.dados);

        auto pet = Conexao::consultarUm(SELECT_PET + " WHERE p.id = ?", {id});
        res.set_header("Location", "/api/pets/" + id);
        enviarJson(res, 201, petParaJson(*pet));
    });

    // PUT /api/pets/:id
    servidor.Put("/api/pets/:id", [](const httplib::Request& req, httplib::Response& res) {
        auto u = exigirLogin(req, res);
        if (!u) return;
        const std::string id = req.path_params.at("id");
        if (!buscarPet(*u, id)) return pet404(res);

        Validacao v = validarPetDaRequisicao(*u, lerCorpo(req));
        if (!v.ok()) return responder422(res, v.erros);

        auto& d = v.dados;
        Conexao::executar(
            "UPDATE pets SET nome = ?, especie = ?, raca = NULLIF(?, ''), "
            "       mes_nascimento = NULLIF(?, ''), ano_nascimento = NULLIF(?, ''), peso_kg = NULLIF(?, ''), tutor_id = ? "
            " WHERE id = ?",
            {d["nome"], d["especie"], d["raca"], d["mes_nascimento"], d["ano_nascimento"], d["peso_kg"], d["tutor_id"], id});
        auto pet = Conexao::consultarUm(SELECT_PET + " WHERE p.id = ?", {id});
        enviarJson(res, 200, petParaJson(*pet));
    });

    // DELETE /api/pets/:id (os pedidos de atendimento do pet são apagados junto: ON DELETE CASCADE)
    servidor.Delete("/api/pets/:id", [](const httplib::Request& req, httplib::Response& res) {
        auto u = exigirLogin(req, res);
        if (!u) return;
        const std::string id = req.path_params.at("id");
        if (!buscarPet(*u, id)) return pet404(res);
        Conexao::executar("DELETE FROM pets WHERE id = ?", {id});
        res.status = 204;
    });
}
