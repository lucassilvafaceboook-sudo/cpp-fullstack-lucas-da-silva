#include "validacao.hpp"

#include <cctype>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <regex>

#include "especies.hpp"

// Tira espaços do começo e do fim
std::string aparar(const std::string& s) {
    const char* espacos = " \t\r\n\f\v";
    const auto inicio = s.find_first_not_of(espacos);
    if (inicio == std::string::npos) return "";
    const auto fim = s.find_last_not_of(espacos);
    return s.substr(inicio, fim - inicio + 1);
}

// Quantidade de LETRAS (não de bytes): "Siamês" tem 6 letras e 7 bytes em UTF-8
size_t tamanho(const std::string& s) {
    size_t n = 0;
    for (unsigned char c : s)
        if ((c & 0xC0) != 0x80) ++n;
    return n;
}

namespace {

int anoAtual() {
    std::time_t agora = std::time(nullptr);
    std::tm local{};
#ifdef _WIN32
    localtime_s(&local, &agora);
#else
    localtime_r(&agora, &local);
#endif
    return local.tm_year + 1900;
}

int mesAtual() { // 1 a 12
    std::time_t agora = std::time(nullptr);
    std::tm local{};
#ifdef _WIN32
    localtime_s(&local, &agora);
#else
    localtime_r(&agora, &local);
#endif
    return local.tm_mon + 1;
}

// Converte texto em número; false se não for um número válido
bool paraNumero(const std::string& s, double& valor) {
    if (s.empty()) return false;
    char* fim = nullptr;
    valor = std::strtod(s.c_str(), &fim);
    return fim && *fim == '\0' && std::isfinite(valor);
}

std::string plural(int n, const char* singular, const char* varios) {
    return std::to_string(n) + " " + (n == 1 ? singular : varios);
}

} // namespace

// ---------------------------------------------------------------- utilidades

std::string campoTexto(const json& corpo, const std::string& campo) {
    if (!corpo.is_object() || !corpo.contains(campo)) return "";
    const json& v = corpo.at(campo);
    if (v.is_null()) return "";
    if (v.is_string()) return aparar(v.get<std::string>());
    if (v.is_number_integer()) return std::to_string(v.get<long long>());
    if (v.is_number_unsigned()) return std::to_string(v.get<unsigned long long>());
    return aparar(v.dump()); // números com vírgula, true/false...
}

bool somenteDigitos(const std::string& s) {
    if (s.empty()) return false;
    for (unsigned char c : s)
        if (!std::isdigit(c)) return false;
    return true;
}

std::string minusculas(std::string s) {
    for (auto& c : s) c = static_cast<char>(std::tolower(static_cast<unsigned char>(c)));
    return s;
}

// ---------------------------------------------------------------- tutor

Validacao validarTutor(const json& corpo) {
    Validacao v;
    v.dados["nome"] = campoTexto(corpo, "nome");
    v.dados["telefone"] = campoTexto(corpo, "telefone");
    v.dados["email"] = minusculas(campoTexto(corpo, "email"));
    const auto& d = v.dados;

    if (d.at("nome").empty()) v.erros["nome"] = "Nome é obrigatório.";
    else if (tamanho(d.at("nome")) > 100) v.erros["nome"] = "Nome pode ter até 100 caracteres.";

    if (d.at("telefone").empty()) v.erros["telefone"] = "Telefone é obrigatório.";
    else if (tamanho(d.at("telefone")) > 20) v.erros["telefone"] = "Telefone pode ter até 20 caracteres.";

    if (!d.at("email").empty()) {
        static const std::regex formatoEmail(R"(^[^\s@]+@[^\s@]+$)");
        if (tamanho(d.at("email")) > 120) v.erros["email"] = "E-mail pode ter até 120 caracteres.";
        else if (!std::regex_match(d.at("email"), formatoEmail))
            v.erros["email"] = "E-mail inválido (precisa ter um @).";
    }
    return v;
}

// ---------------------------------------------------------------- pet

Validacao validarPet(const json& corpo) {
    Validacao v;
    auto& d = v.dados;
    auto& erros = v.erros;
    d["nome"] = campoTexto(corpo, "nome");
    d["especie"] = minusculas(campoTexto(corpo, "especie"));
    d["raca"] = campoTexto(corpo, "raca");
    d["mes_nascimento"] = campoTexto(corpo, "mes_nascimento");
    d["ano_nascimento"] = campoTexto(corpo, "ano_nascimento");
    d["peso_kg"] = campoTexto(corpo, "peso_kg");
    d["tutor_id"] = campoTexto(corpo, "tutor_id");

    // aceita "28,4" vindo do front
    if (auto virgula = d["peso_kg"].find(','); virgula != std::string::npos) d["peso_kg"][virgula] = '.';

    if (d["nome"].empty()) erros["nome"] = "Nome é obrigatório.";
    else if (tamanho(d["nome"]) > 60) erros["nome"] = "Nome pode ter até 60 caracteres.";

    if (d["especie"].empty()) erros["especie"] = "Espécie é obrigatória.";
    else if (!especieValida(d["especie"])) erros["especie"] = "Espécie inválida. Veja a lista em GET /api/especies.";

    if (tamanho(d["raca"]) > 60) erros["raca"] = "Raça pode ter até 60 caracteres.";

    // Mês e ano de nascimento: opcionais, mas vêm juntos (os dois ou nenhum)
    static const std::regex formatoMes(R"(^(0?[1-9]|1[0-2])$)");
    const std::string& mes = d["mes_nascimento"];
    const std::string& ano = d["ano_nascimento"];
    if (!mes.empty() && !std::regex_match(mes, formatoMes)) erros["mes_nascimento"] = "Mês inválido. Use de 1 a 12.";
    else if (!mes.empty()) d["mes_nascimento"] = std::to_string(std::atoi(mes.c_str())); // "03" -> "3"

    if (!ano.empty()) {
        const int anoNum = std::atoi(ano.c_str());
        if (ano.size() != 4 || !somenteDigitos(ano)) erros["ano_nascimento"] = "Ano inválido. Use 4 dígitos, ex.: 2021.";
        else if (anoNum < 1900) erros["ano_nascimento"] = "Ano de nascimento muito antigo.";
        else if (anoNum > anoAtual()) erros["ano_nascimento"] = "Nascimento não pode ser no futuro.";
        else if (d["mes_nascimento"].empty() && !erros.count("mes_nascimento"))
            erros["mes_nascimento"] = "Informe o mês de nascimento.";
        else if (anoNum == anoAtual() && std::atoi(d["mes_nascimento"].c_str()) > mesAtual())
            erros["mes_nascimento"] = "Nascimento não pode ser no futuro.";
    } else if (!mes.empty() && !erros.count("mes_nascimento")) {
        erros["ano_nascimento"] = "Informe o ano de nascimento.";
    }

    if (!d["peso_kg"].empty()) {
        double peso = 0;
        if (!paraNumero(d["peso_kg"], peso)) erros["peso_kg"] = "Peso deve ser um número.";
        else if (peso <= 0) erros["peso_kg"] = "Peso deve ser maior que 0.";
        else if (peso > 999.99) erros["peso_kg"] = "Peso máximo é 999,99 kg.";
        else {
            char texto[32];
            std::snprintf(texto, sizeof texto, "%.2f", peso);
            d["peso_kg"] = texto;
        }
    }

    if (d["tutor_id"].empty()) erros["tutor_id"] = "Tutor é obrigatório.";
    else if (!somenteDigitos(d["tutor_id"]) || std::atoll(d["tutor_id"].c_str()) < 1) erros["tutor_id"] = "Tutor inválido.";

    return v;
}

// ------------------------------------------------- cadastro de usuário

Validacao validarRegistro(const json& corpo) {
    std::string papel = minusculas(campoTexto(corpo, "papel"));
    if (papel.empty()) papel = "cliente";

    // Cliente também vira um tutor, então reaproveita as regras de tutor (nome, telefone, e-mail)
    Validacao v = validarTutor(corpo);
    v.dados["papel"] = papel;
    v.dados["codigo_clinica"] = campoTexto(corpo, "codigo_clinica");
    // A senha não é "aparada": espaço também conta
    std::string senha;
    if (corpo.is_object() && corpo.contains("senha") && corpo["senha"].is_string()) senha = corpo["senha"].get<std::string>();
    else senha = campoTexto(corpo, "senha");
    v.dados["senha"] = senha;

    if (papel != "cliente" && papel != "veterinario") v.erros["papel"] = "Tipo de conta inválido.";
    if (v.dados["email"].empty()) v.erros["email"] = "E-mail é obrigatório para criar a conta.";
    if (tamanho(senha) < 6) v.erros["senha"] = "A senha precisa ter pelo menos 6 caracteres.";
    else if (tamanho(senha) > 100) v.erros["senha"] = "Senha muito longa.";
    // Telefone só é obrigatório para clientes (é o contato do tutor)
    if (papel == "veterinario" && v.erros.count("telefone") && v.erros["telefone"] == "Telefone é obrigatório.")
        v.erros.erase("telefone");
    if (papel == "veterinario" && v.dados["codigo_clinica"].empty())
        v.erros["codigo_clinica"] = "Informe o código da clínica.";
    return v;
}

// ------------------------------------- pedido de atendimento (motivo)

Validacao validarAtendimento(const json& corpo) {
    Validacao v;
    v.dados["tipo"] = minusculas(campoTexto(corpo, "tipo"));
    v.dados["sintomas"] = campoTexto(corpo, "sintomas");
    const std::string& tipo = v.dados["tipo"];
    const std::string& sintomas = v.dados["sintomas"];

    if (tipo.empty()) v.erros["tipo"] = "Diga se é consulta (com sintomas) ou apenas vacinação.";
    else if (tipo != "consulta" && tipo != "vacina") v.erros["tipo"] = "Tipo inválido. Use: consulta ou vacina.";
    else if (tipo == "consulta" && tamanho(sintomas) < 3) v.erros["sintomas"] = "Descreva os sintomas do pet.";
    if (tamanho(sintomas) > 1000) v.erros["sintomas"] = "Sintomas podem ter até 1000 caracteres.";
    return v;
}

// ---------------------------------------------------------------- idade

json calcularIdade(int anoNascimento, int mesNascimento) {
    if (anoNascimento <= 0) return nullptr;
    if (mesNascimento <= 0) { // só o ano: idade aproximada em anos
        const int anos = std::max(0, anoAtual() - anoNascimento);
        return {{"anos", anos}, {"meses", nullptr}, {"texto", anos == 0 ? "menos de 1 ano" : plural(anos, "ano", "anos")}};
    }
    // Sem o dia, a conta é aproximada (pode errar por 1 mês)
    const int total = std::max(0, (anoAtual() - anoNascimento) * 12 + (mesAtual() - mesNascimento));
    const int anos = total / 12;
    const int meses = total % 12;
    std::string texto;
    if (anos) texto = plural(anos, "ano", "anos");
    if (meses || !anos) texto += (texto.empty() ? "" : " e ") + plural(meses, "mês", "meses");
    return {{"anos", anos}, {"meses", meses}, {"texto", texto}};
}
