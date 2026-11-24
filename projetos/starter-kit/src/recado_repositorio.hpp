// recado_repositorio.hpp - Acesso à tabela "recados" (exemplo completo de CRUD).
//
// O "repositório" concentra TODO o SQL de um recurso. As rotas (rotas_recados.cpp) não escrevem SQL:
// elas só chamam estas funções. Para o seu tema, copie este par de arquivos e troque "recado" por
// "livro", "pet" ou "produto" (veja projetos/guia/04-banco-mariadb.md).
#pragma once

#include <string>

#include <nlohmann/json.hpp>

#include "banco.hpp"

class RecadoRepositorio {
public:
    explicit RecadoRepositorio(Conexao& banco) : banco_(banco) {}

    // Lista os recados (do mais novo para o mais antigo). Se "busca" não for vazia,
    // filtra pelos que contêm esse texto no título ou na mensagem.
    nlohmann::json listar(const std::string& busca = "");

    // Devolve o recado com o id informado, ou null se não existir.
    nlohmann::json buscar(long long id);

    // Insere e devolve o recado criado (com id e data).
    nlohmann::json criar(const nlohmann::json& dados);

    // Atualiza. Devolve o recado atualizado, ou null se o id não existir.
    nlohmann::json atualizar(long long id, const nlohmann::json& dados);

    // Remove. Devolve true se existia, false se o id não existe.
    bool remover(long long id);

private:
    Conexao& banco_;
};
