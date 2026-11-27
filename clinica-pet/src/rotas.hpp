// Funções usadas por todas as rotas + o registro de cada grupo de rotas.
#pragma once

#include <optional>
#include <string>
#include <vector>

#include "httplib.h"
#include "json.hpp"
#include "auth.hpp"
#include "banco.hpp"
#include "validacao.hpp"

// Responde com JSON e o status HTTP informado
inline void enviarJson(httplib::Response& res, int status, const json& corpo) {
    res.status = status;
    res.set_content(corpo.dump(), "application/json; charset=utf-8");
}

// Erro simples: { "erro": "mensagem" }
inline void enviarErro(httplib::Response& res, int status, const std::string& mensagem) {
    enviarJson(res, status, {{"erro", mensagem}});
}

// 422 com a mensagem de cada campo: { "erro": "Dados inválidos.", "campos": { ... } }
inline void responder422(httplib::Response& res, const Erros& erros) {
    enviarJson(res, 422, {{"erro", "Dados inválidos."}, {"campos", erros}});
}

// Corpo da requisição como JSON. Corpo vazio vira {}.
// JSON mal formatado lança json::parse_error (vira 400 no tratador de erros do main.cpp).
inline json lerCorpo(const httplib::Request& req) {
    if (req.body.empty()) return json::object();
    json corpo = json::parse(req.body);
    return corpo.is_object() ? corpo : json::object();
}

// Id da URL (/api/pets/:id) válido: só dígitos e maior que zero
inline bool idValido(const std::string& id) {
    return somenteDigitos(id) && id.size() <= 18 && std::stoll(id) > 0;
}

// ---- usadas por mais de um arquivo de rotas (implementadas em rotas_pets.cpp)
extern const std::string SELECT_PET;          // SELECT de pet com o nome e telefone do tutor
json petParaJson(const Linha& linha);         // linha do SELECT_PET -> JSON da API
bool tutorExiste(const std::string& id);
// Pet visível para o usuário (cliente: só os dele; veterinário: qualquer um)
std::optional<Linha> buscarPet(const Usuario& usuario, const std::string& id);
// Filtro "só os pets do cliente": devolve "" para veterinário
std::string filtroDono(const Usuario& usuario, std::vector<std::string>& parametros);

// Cada arquivo rotas_*.cpp registra as suas rotas no servidor
void registrarRotasAuth(httplib::Server& servidor);
void registrarRotasPets(httplib::Server& servidor);
void registrarRotasAtendimentos(httplib::Server& servidor);
void registrarRotasTutores(httplib::Server& servidor);
