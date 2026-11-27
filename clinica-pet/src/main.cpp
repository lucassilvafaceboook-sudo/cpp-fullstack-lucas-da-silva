// Clínica Pet — API em C++17 (cpp-httplib + nlohmann/json) com MariaDB.
//
// Uso:
//   clinica-pet                                  sobe o servidor (http://localhost:3000)
//   clinica-pet --redefinir-senha email@x.com    define uma senha nova para a conta
//
// Variáveis de ambiente (todas opcionais):
//   PORT (3000), DB_HOST (127.0.0.1), DB_PORT (3306), DB_USER (root), DB_PASSWORD (root),
//   DB_NAME (clinica_pet), CODIGO_CLINICA (vet-2026), PUBLIC_DIR (./public)
#include <cstdlib>
#include <iostream>

// rotas.hpp primeiro: o httplib.h precisa incluir o winsock2.h antes do windows.h
#include "especies.hpp"
#include "rotas.hpp"

#include <mysql.h>

#ifdef _WIN32
#include <windows.h>
#else
#include <termios.h>
#include <unistd.h>
#endif

namespace {

std::string variavel(const char* nome, const char* padrao) {
    const char* valor = std::getenv(nome);
    return (valor && *valor) ? valor : padrao;
}

// ---------------------------------------------------- tratamento de erros

// Exceções que escapam de uma rota viram uma resposta JSON (o servidor nunca cai).
void tratarExcecao(const httplib::Request&, httplib::Response& res, std::exception_ptr ep) {
    try {
        std::rethrow_exception(ep);
    } catch (const json::parse_error&) {
        enviarErro(res, 400, "JSON mal formatado no corpo da requisição.");
    } catch (const ErroBanco& e) {
        // Redes de segurança caso algo escape da validação da API:
        switch (e.codigo) {
        case CodigoErro::DUPLICADO:
            return enviarErro(res, 409, "Registro duplicado (e-mail já cadastrado).");
        case CodigoErro::REFERENCIA_INEXISTENTE:
            return enviarJson(res, 422, {{"erro", "Tutor informado não existe."}, {"campos", {{"tutor_id", "Tutor não existe."}}}});
        case CodigoErro::EM_USO:
            return enviarErro(res, 409, "Registro em uso por outro cadastro.");
        case CodigoErro::CHECK_VIOLADO:
        case CodigoErro::VALOR_INVALIDO:
            return enviarErro(res, 422, "Valor recusado pelo banco de dados.");
        default:
            std::cerr << "Erro do banco (" << e.codigo << "): " << e.what() << "\n";
            return enviarErro(res, 500, "Erro interno no servidor.");
        }
    } catch (const std::exception& e) {
        std::cerr << "Erro: " << e.what() << "\n";
        enviarErro(res, 500, "Erro interno no servidor.");
    } catch (...) {
        enviarErro(res, 500, "Erro interno no servidor.");
    }
}

// Respostas de erro sem corpo (ex.: rota que não existe) ganham um JSON
void tratarErroHttp(const httplib::Request& req, httplib::Response& res) {
    if (!res.body.empty()) return;
    if (req.path.rfind("/api", 0) == 0 && res.status == 404) enviarErro(res, 404, "Rota não encontrada.");
}

// ---------------------------------------------------- servidor

int subirServidor() {
    httplib::Server servidor;
    servidor.set_exception_handler(tratarExcecao);
    servidor.set_error_handler(tratarErroHttp);

    // Front-end (public/) servido pela própria API
    const std::string pastaPublica = variavel("PUBLIC_DIR", "./public");
    if (!servidor.set_mount_point("/", pastaPublica)) {
        std::cerr << "Pasta do front-end não encontrada: " << pastaPublica
                  << " (rode o programa de dentro da pasta do projeto)\n";
        return 1;
    }

    // Rotas públicas
    servidor.Get("/api/saude/banco", [](const httplib::Request&, httplib::Response& res) {
        if (Conexao::funcionando()) enviarJson(res, 200, {{"status", "ok"}});
        else enviarJson(res, 503, {{"status", "erro"}, {"erro", "Sem conexão com o banco de dados."}});
    });
    // Lista de espécies com nome e grupo: [{ codigo, nome, grupo }, ...]
    servidor.Get("/api/especies", [](const httplib::Request&, httplib::Response& res) {
        json lista = json::array();
        for (const auto& e : listaEspecies()) lista.push_back({{"codigo", e.codigo}, {"nome", e.nome}, {"grupo", e.grupo}});
        enviarJson(res, 200, lista);
    });

    registrarRotasAuth(servidor);
    registrarRotasPets(servidor);
    registrarRotasAtendimentos(servidor);
    registrarRotasTutores(servidor);

    const int porta = std::atoi(variavel("PORT", "3000").c_str());
    std::cout << "Clinica Pet rodando em http://localhost:" << porta << std::endl;
    if (!servidor.listen("0.0.0.0", porta)) {
        std::cerr << "Não foi possível usar a porta " << porta << " (já está em uso?)\n";
        return 1;
    }
    return 0;
}

// ---------------------------------------------------- redefinir senha

// Lê uma linha sem mostrar o que é digitado (quando é um terminal)
std::string lerSenhaEscondida(const std::string& pergunta) {
    std::cout << pergunta << std::flush;
    std::string senha;
#ifdef _WIN32
    HANDLE entrada = GetStdHandle(STD_INPUT_HANDLE);
    DWORD modo = 0;
    const bool terminal = GetConsoleMode(entrada, &modo);
    if (terminal) SetConsoleMode(entrada, modo & ~static_cast<DWORD>(ENABLE_ECHO_INPUT));
    std::getline(std::cin, senha);
    if (terminal) SetConsoleMode(entrada, modo);
#else
    termios antigo{};
    const bool terminal = isatty(STDIN_FILENO) && tcgetattr(STDIN_FILENO, &antigo) == 0;
    if (terminal) {
        termios novo = antigo;
        novo.c_lflag &= ~static_cast<tcflag_t>(ECHO);
        tcsetattr(STDIN_FILENO, TCSANOW, &novo);
    }
    std::getline(std::cin, senha);
    if (terminal) tcsetattr(STDIN_FILENO, TCSANOW, &antigo);
#endif
    std::cout << "\n";
    if (!senha.empty() && senha.back() == '\r') senha.pop_back();
    return senha;
}

// A senha antiga não pode ser recuperada (no banco só existe o hash): define uma nova.
int redefinirSenha(const std::string& emailInformado) {
    const std::string email = minusculas(aparar(emailInformado));
    if (email.empty()) {
        std::cout << "Informe o e-mail. Ex.: clinica-pet --redefinir-senha email@exemplo.com\n";
        return 1;
    }
    auto u = Conexao::consultarUm("SELECT id, nome, papel FROM usuarios WHERE email = ?", {email});
    if (!u) {
        std::cout << "Nenhuma conta com o e-mail " << email << ".\n";
        return 1;
    }
    std::cout << "Conta encontrada: " << u->texto("nome") << " ("
              << (u->texto("papel") == "veterinario" ? "veterinário" : "tutor") << ")\n";

    const std::string senha = lerSenhaEscondida("Nova senha (mínimo 6 caracteres): ");
    if (tamanho(senha) < 6 || tamanho(senha) > 100) {
        std::cout << "A senha precisa ter entre 6 e 100 caracteres. Nada foi alterado.\n";
        return 1;
    }
    if (lerSenhaEscondida("Repita a nova senha: ") != senha) {
        std::cout << "As senhas não conferem. Nada foi alterado.\n";
        return 1;
    }
    const std::string id = u->texto("id");
    Conexao::executar("UPDATE usuarios SET senha_hash = ? WHERE id = ?", {gerarHashSenha(senha), id});
    // Desconecta as sessões abertas com a senha antiga
    Conexao::executar("DELETE FROM sessoes WHERE usuario_id = ?", {id});
    std::cout << "Senha alterada. Já dá para entrar com a nova senha.\n";
    return 0;
}

} // namespace

int main(int argc, char* argv[]) {
#ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8); // acentos certos no terminal do Windows
#endif
    mysql_library_init(0, nullptr, nullptr);
    int codigo = 0;
    try {
        const std::string comando = argc > 1 ? argv[1] : "";
        if (comando == "--redefinir-senha") codigo = redefinirSenha(argc > 2 ? argv[2] : "");
        else codigo = subirServidor();
    } catch (const std::exception& e) {
        std::cerr << "Erro: " << e.what() << "\n";
        codigo = 1;
    }
    mysql_library_end();
    return codigo;
}
