#include "recado_repositorio.hpp"

#include <vector>

using nlohmann::json;

namespace {

// Converte um campo JSON (texto ou número) para o texto que vai como parâmetro "?" do SQL.
std::string comoTexto(const json& valor) {
    return valor.is_string() ? valor.get<std::string>() : valor.dump();
}

// Escapa % e _ para que a busca trate o texto digitado literalmente dentro do LIKE.
std::string escaparLike(const std::string& texto) {
    std::string saida;
    for (char c : texto) {
        if (c == '\\' || c == '%' || c == '_') {
            saida += '\\';
        }
        saida += c;
    }
    return saida;
}

const char* const kColunas = "id, titulo, mensagem, prioridade, criado_em";

}  // namespace

json RecadoRepositorio::listar(const std::string& busca) {
    const std::string base = std::string("SELECT ") + kColunas + " FROM recados";
    if (busca.empty()) {
        return banco_.consultar(base + " ORDER BY id DESC");
    }
    const std::string padrao = "%" + escaparLike(busca) + "%";
    return banco_.consultar(base + " WHERE titulo LIKE ? OR mensagem LIKE ? ORDER BY id DESC", {padrao, padrao});
}

json RecadoRepositorio::buscar(long long id) {
    json linhas = banco_.consultar(std::string("SELECT ") + kColunas + " FROM recados WHERE id = ?",
                                   {std::to_string(id)});
    return linhas.empty() ? json(nullptr) : linhas.front();
}

json RecadoRepositorio::criar(const json& dados) {
    banco_.executar("INSERT INTO recados (titulo, mensagem, prioridade) VALUES (?, ?, ?)",
                    {comoTexto(dados.at("titulo")),
                     dados.contains("mensagem") && !dados["mensagem"].is_null() ? comoTexto(dados["mensagem"]) : "",
                     dados.contains("prioridade") && !dados["prioridade"].is_null() ? comoTexto(dados["prioridade"])
                                                                                   : "1"});
    return buscar(static_cast<long long>(banco_.ultimoId()));
}

json RecadoRepositorio::atualizar(long long id, const json& dados) {
    // Conferimos se existe ANTES: no MariaDB, um UPDATE que não muda nenhum valor devolve 0 linhas
    // afetadas, e não poderíamos distinguir "id inexistente" de "nada mudou".
    if (buscar(id).is_null()) {
        return json(nullptr);
    }
    banco_.executar("UPDATE recados SET titulo = ?, mensagem = ?, prioridade = ? WHERE id = ?",
                    {comoTexto(dados.at("titulo")),
                     dados.contains("mensagem") && !dados["mensagem"].is_null() ? comoTexto(dados["mensagem"]) : "",
                     dados.contains("prioridade") && !dados["prioridade"].is_null() ? comoTexto(dados["prioridade"])
                                                                                   : "1",
                     std::to_string(id)});
    return buscar(id);
}

bool RecadoRepositorio::remover(long long id) {
    return banco_.executar("DELETE FROM recados WHERE id = ?", {std::to_string(id)}) > 0;
}
