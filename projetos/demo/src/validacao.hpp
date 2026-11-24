// validacao.hpp - Funções pequenas e reutilizáveis para validar os campos recebidos no JSON.
//
// Cada função confere UM campo e, se houver problema, acrescenta uma mensagem à lista "erros".
// A rota chama várias delas e, no fim, responde 422 com TODOS os problemas de uma vez (guia 03).
#pragma once

#include <algorithm>
#include <cstddef>
#include <sstream>
#include <string>
#include <vector>

#include <nlohmann/json.hpp>

namespace validacao {

using nlohmann::json;

// O campo existe e não é null?
inline bool temValor(const json& dados, const char* campo) {
    return dados.contains(campo) && !dados[campo].is_null();
}

// Texto obrigatório: presente, é texto, não é vazio e tem até "max" bytes.
inline void textoObrigatorio(const json& dados, const char* campo, std::size_t max, json& erros) {
    const std::string nome = campo;
    if (!temValor(dados, campo) || !dados[campo].is_string() || dados[campo].get<std::string>().empty()) {
        erros.push_back(nome + " e obrigatorio");
    } else if (dados[campo].get<std::string>().size() > max) {
        erros.push_back(nome + " deve ter no maximo " + std::to_string(max) + " caracteres");
    }
}

// Texto opcional: se vier, precisa ser texto com até "max" bytes.
inline void textoOpcional(const json& dados, const char* campo, std::size_t max, json& erros) {
    if (!temValor(dados, campo)) {
        return;
    }
    const std::string nome = campo;
    if (!dados[campo].is_string()) {
        erros.push_back(nome + " deve ser texto");
    } else if (dados[campo].get<std::string>().size() > max) {
        erros.push_back(nome + " deve ter no maximo " + std::to_string(max) + " caracteres");
    }
}

// Número inteiro entre "minimo" e "maximo". Se "obrigatorio" for false, campo ausente ou null é aceito.
inline void inteiroEmFaixa(const json& dados, const char* campo, long long minimo, long long maximo,
                           bool obrigatorio, json& erros) {
    const std::string nome = campo;
    if (!temValor(dados, campo)) {
        if (obrigatorio) {
            erros.push_back(nome + " e obrigatorio");
        }
        return;
    }
    const json& valor = dados[campo];
    if (!valor.is_number_integer() || valor.get<long long>() < minimo || valor.get<long long>() > maximo) {
        erros.push_back(nome + " deve ser um numero inteiro de " + std::to_string(minimo) + " a " +
                        std::to_string(maximo));
    }
}

// Número (com ou sem casas decimais) entre "minimo" e "maximo". Opcional.
inline void decimalEmFaixa(const json& dados, const char* campo, double minimo, double maximo, json& erros) {
    if (!temValor(dados, campo)) {
        return;
    }
    const json& valor = dados[campo];
    if (!valor.is_number() || valor.get<double>() < minimo || valor.get<double>() > maximo) {
        std::ostringstream faixa;
        faixa << campo << " deve ser um numero de " << minimo << " a " << maximo;
        erros.push_back(faixa.str());
    }
}

// Valor de uma lista fixa (ex.: status). Opcional: ausente ou null é aceito (a rota usa o valor padrão).
inline void valorDaLista(const json& dados, const char* campo, const std::vector<std::string>& permitidos,
                         json& erros) {
    if (!temValor(dados, campo)) {
        return;
    }
    const bool existe = dados[campo].is_string() &&
                        std::find(permitidos.begin(), permitidos.end(), dados[campo].get<std::string>()) !=
                            permitidos.end();
    if (!existe) {
        std::string lista;
        for (const std::string& item : permitidos) {
            lista += (lista.empty() ? "" : ", ") + item;
        }
        erros.push_back(std::string(campo) + " deve ser um destes valores: " + lista);
    }
}

// "AAAA-MM-DD" existe no calendário? (confere dia 31 de abril, 29 de fevereiro em ano não bissexto...)
inline bool dataValida(const std::string& texto) {
    if (texto.size() != 10 || texto[4] != '-' || texto[7] != '-') {
        return false;
    }
    for (std::size_t i = 0; i < texto.size(); ++i) {
        if (i != 4 && i != 7 && (texto[i] < '0' || texto[i] > '9')) {
            return false;
        }
    }
    const int ano = std::stoi(texto.substr(0, 4));
    const int mes = std::stoi(texto.substr(5, 2));
    const int dia = std::stoi(texto.substr(8, 2));
    if (ano < 1000 || mes < 1 || mes > 12 || dia < 1) {
        return false;
    }
    const bool bissexto = (ano % 4 == 0 && ano % 100 != 0) || ano % 400 == 0;
    const int diasDoMes[] = {31, bissexto ? 29 : 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    return dia <= diasDoMes[mes - 1];
}

// Data opcional no formato AAAA-MM-DD.
inline void dataOpcional(const json& dados, const char* campo, json& erros) {
    if (!temValor(dados, campo)) {
        return;
    }
    if (!dados[campo].is_string() || !dataValida(dados[campo].get<std::string>())) {
        erros.push_back(std::string(campo) + " deve ser uma data valida no formato AAAA-MM-DD");
    }
}

}  // namespace validacao
