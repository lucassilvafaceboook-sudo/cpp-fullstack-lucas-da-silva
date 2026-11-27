// Rotas de cadastro, login e logout.
#include "auth.hpp"
#include "banco.hpp"
#include "rotas.hpp"

void registrarRotasAuth(httplib::Server& servidor) {
    // POST /api/auth/registro
    // Cliente:     { nome, telefone, email, senha }       -> cria a conta e o cadastro de tutor
    // Veterinário: { papel: "veterinario", nome, email, senha, codigo_clinica }
    servidor.Post("/api/auth/registro", [](const httplib::Request& req, httplib::Response& res) {
        Validacao v = validarRegistro(lerCorpo(req));
        if (!v.ok()) return responder422(res, v.erros);
        auto& d = v.dados;
        if (d["papel"] == "veterinario" && d["codigo_clinica"] != codigoClinica())
            return responder422(res, {{"codigo_clinica", "Código da clínica incorreto."}});

        if (Conexao::consultarUm("SELECT id FROM usuarios WHERE email = ?", {d["email"]}))
            return enviarJson(res, 409, {{"erro", "Já existe uma conta com esse e-mail."},
                                         {"campos", {{"email", "E-mail já cadastrado. Faça login."}}}});

        std::string tutorId;
        if (d["papel"] == "cliente") {
            // Não liga a conta a um tutor que a recepção já cadastrou: sem confirmar o e-mail,
            // qualquer um poderia "assumir" os pets de outra pessoa só digitando o e-mail dela.
            if (Conexao::consultarUm("SELECT id FROM tutores WHERE email = ?", {d["email"]}))
                return enviarJson(res, 409,
                    {{"erro", "Esse e-mail já está no cadastro da clínica. Fale com a recepção para liberar seu acesso."},
                     {"campos", {{"email", "E-mail já está no cadastro da clínica."}}}});
            auto t = Conexao::executar("INSERT INTO tutores (nome, telefone, email) VALUES (?, ?, ?)",
                                       {d["nome"], d["telefone"], d["email"]});
            tutorId = std::to_string(t.idInserido);
        }

        ResultadoExecucao r;
        try {
            r = Conexao::executar(
                "INSERT INTO usuarios (nome, email, senha_hash, papel, tutor_id) VALUES (?, ?, ?, ?, NULLIF(?, ''))",
                {d["nome"], d["email"], gerarHashSenha(d["senha"]), d["papel"], tutorId});
        } catch (...) {
            // desfaz o tutor criado acima, para não sobrar cadastro sem conta
            if (!tutorId.empty()) Conexao::executar("DELETE FROM tutores WHERE id = ?", {tutorId});
            throw;
        }

        Usuario u;
        u.id = static_cast<long long>(r.idInserido);
        u.nome = d["nome"];
        u.email = d["email"];
        u.papel = d["papel"];
        u.tutorId = tutorId.empty() ? 0 : std::stoll(tutorId);
        enviarJson(res, 201, {{"token", criarSessao(u.id)}, {"usuario", u.paraJson()}});
    });

    // POST /api/auth/login { email, senha }
    servidor.Post("/api/auth/login", [](const httplib::Request& req, httplib::Response& res) {
        const json corpo = lerCorpo(req);
        const std::string email = minusculas(campoTexto(corpo, "email"));
        const std::string senha = corpo.contains("senha") && corpo["senha"].is_string()
                                      ? corpo["senha"].get<std::string>() : campoTexto(corpo, "senha");

        std::optional<Linha> u;
        if (!email.empty()) u = Conexao::consultarUm("SELECT * FROM usuarios WHERE email = ?", {email});
        if (!u || !senhaConfere(senha, u->texto("senha_hash")))
            return enviarErro(res, 401, "E-mail ou senha incorretos.");

        Usuario usuario;
        usuario.id = u->inteiro("id");
        usuario.nome = u->texto("nome");
        usuario.email = u->texto("email");
        usuario.papel = u->texto("papel");
        usuario.tutorId = u->inteiro("tutor_id");
        enviarJson(res, 200, {{"token", criarSessao(usuario.id)}, {"usuario", usuario.paraJson()}});
    });

    // GET /api/auth/eu — quem está logado
    servidor.Get("/api/auth/eu", [](const httplib::Request& req, httplib::Response& res) {
        auto u = exigirLogin(req, res);
        if (!u) return;
        enviarJson(res, 200, u->paraJson());
    });

    // POST /api/auth/logout — apaga a sessão atual
    servidor.Post("/api/auth/logout", [](const httplib::Request& req, httplib::Response& res) {
        auto u = exigirLogin(req, res);
        if (!u) return;
        encerrarSessao(u->token);
        res.status = 204;
    });
}
