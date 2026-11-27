#include "auth.hpp"

#include <cstdlib>
#include <vector>

#include <openssl/crypto.h>
#include <openssl/evp.h>
#include <openssl/rand.h>

#include "banco.hpp"
#include "rotas.hpp"

namespace {

constexpr int DIAS_SESSAO = 7;

// Parâmetros do scrypt (os mesmos padrões do Node.js, para as senhas antigas continuarem valendo)
constexpr uint64_t SCRYPT_N = 16384;
constexpr uint64_t SCRYPT_R = 8;
constexpr uint64_t SCRYPT_P = 1;
constexpr size_t TAMANHO_HASH = 64;

std::string paraHex(const unsigned char* bytes, size_t n) {
    static const char* digitos = "0123456789abcdef";
    std::string hex;
    hex.reserve(n * 2);
    for (size_t i = 0; i < n; ++i) {
        hex += digitos[bytes[i] >> 4];
        hex += digitos[bytes[i] & 0x0F];
    }
    return hex;
}

std::string bytesAleatoriosHex(size_t n) {
    std::vector<unsigned char> bytes(n);
    if (RAND_bytes(bytes.data(), static_cast<int>(n)) != 1) throw std::runtime_error("Falha ao gerar números aleatórios.");
    return paraHex(bytes.data(), n);
}

std::string scryptHex(const std::string& senha, const std::string& sal) {
    unsigned char saida[TAMANHO_HASH];
    const int ok = EVP_PBE_scrypt(senha.data(), senha.size(),
                                  reinterpret_cast<const unsigned char*>(sal.data()), sal.size(),
                                  SCRYPT_N, SCRYPT_R, SCRYPT_P, 64 * 1024 * 1024, saida, TAMANHO_HASH);
    if (ok != 1) throw std::runtime_error("Falha ao calcular o hash da senha.");
    return paraHex(saida, TAMANHO_HASH);
}

std::string sha256Hex(const std::string& texto) {
    unsigned char hash[EVP_MAX_MD_SIZE];
    unsigned int tamanho = 0;
    if (EVP_Digest(texto.data(), texto.size(), hash, &tamanho, EVP_sha256(), nullptr) != 1)
        throw std::runtime_error("Falha ao calcular SHA-256.");
    return paraHex(hash, tamanho);
}

std::optional<Usuario> usuarioDoToken(const std::string& token) {
    auto linha = Conexao::consultarUm(
        "SELECT u.id, u.nome, u.email, u.papel, u.tutor_id "
        "  FROM sessoes s JOIN usuarios u ON u.id = s.usuario_id "
        " WHERE s.token_hash = ? AND s.expira_em > NOW()",
        {sha256Hex(token)});
    if (!linha) return std::nullopt;
    Usuario u;
    u.id = linha->inteiro("id");
    u.nome = linha->texto("nome");
    u.email = linha->texto("email");
    u.papel = linha->texto("papel");
    u.tutorId = linha->inteiro("tutor_id");
    u.token = token;
    return u;
}

} // namespace

json Usuario::paraJson() const {
    return {{"id", id},
            {"nome", nome},
            {"email", email},
            {"papel", papel},
            {"tutor_id", tutorId ? json(tutorId) : json(nullptr)}};
}

std::string codigoClinica() {
    const char* codigo = std::getenv("CODIGO_CLINICA");
    return (codigo && *codigo) ? codigo : "vet-2026";
}

std::string gerarHashSenha(const std::string& senha) {
    const std::string sal = bytesAleatoriosHex(16);
    return sal + ":" + scryptHex(senha, sal);
}

bool senhaConfere(const std::string& senha, const std::string& guardado) {
    const auto doisPontos = guardado.find(':');
    if (doisPontos == std::string::npos) return false;
    const std::string sal = guardado.substr(0, doisPontos);
    const std::string esperado = guardado.substr(doisPontos + 1);
    const std::string calculado = scryptHex(senha, sal);
    // comparação em tempo constante (não dá pistas por tempo de resposta)
    return esperado.size() == calculado.size() &&
           CRYPTO_memcmp(esperado.data(), calculado.data(), esperado.size()) == 0;
}

std::string criarSessao(long long usuarioId) {
    const std::string token = bytesAleatoriosHex(32);
    Conexao::executar(
        "INSERT INTO sessoes (token_hash, usuario_id, expira_em) VALUES (?, ?, NOW() + INTERVAL ? DAY)",
        {sha256Hex(token), std::to_string(usuarioId), std::to_string(DIAS_SESSAO)});
    return token;
}

void encerrarSessao(const std::string& token) {
    Conexao::executar("DELETE FROM sessoes WHERE token_hash = ?", {sha256Hex(token)});
}

std::optional<Usuario> exigirLogin(const httplib::Request& req, httplib::Response& res) {
    const std::string cabecalho = req.get_header_value("Authorization");
    const std::string prefixo = "Bearer ";
    std::string token;
    if (cabecalho.rfind(prefixo, 0) == 0) token = cabecalho.substr(prefixo.size());

    if (token.empty()) {
        enviarErro(res, 401, "Faça login para continuar.");
        return std::nullopt;
    }
    auto usuario = usuarioDoToken(token);
    if (!usuario) {
        enviarErro(res, 401, "Sessão expirada. Faça login de novo.");
        return std::nullopt;
    }
    return usuario;
}

std::optional<Usuario> exigirVet(const httplib::Request& req, httplib::Response& res) {
    auto usuario = exigirLogin(req, res);
    if (!usuario) return std::nullopt;
    if (!usuario->ehVet()) {
        enviarErro(res, 403, "Apenas a equipe da clínica pode acessar isso.");
        return std::nullopt;
    }
    return usuario;
}
