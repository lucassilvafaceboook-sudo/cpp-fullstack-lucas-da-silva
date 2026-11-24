// parametros.hpp - Funções pequenas para preparar os valores que vão nos "?" das consultas SQL.
//
// Todos os repositórios precisam das mesmas conversões, então elas ficam num lugar só
// (em vez de copiadas em cada arquivo .cpp).
#pragma once

#include <string>

#include <nlohmann/json.hpp>

namespace parametros {

// Converte um campo JSON (texto ou número) para o texto que vai como parâmetro "?" do SQL.
inline std::string comoTexto(const nlohmann::json& valor) {
    return valor.is_string() ? valor.get<std::string>() : valor.dump();
}

// Lê um campo opcional: se estiver ausente ou for null, devolve "padrao" ("" vira NULL com NULLIF no SQL).
inline std::string opcional(const nlohmann::json& dados, const char* campo, const std::string& padrao = "") {
    if (!dados.contains(campo) || dados[campo].is_null()) {
        return padrao;
    }
    return comoTexto(dados[campo]);
}

// Escapa % e _ para que a busca trate o texto digitado literalmente dentro do LIKE.
inline std::string escaparLike(const std::string& texto) {
    std::string saida;
    for (char c : texto) {
        if (c == '\\' || c == '%' || c == '_') {
            saida += '\\';
        }
        saida += c;
    }
    return saida;
}

}  // namespace parametros
