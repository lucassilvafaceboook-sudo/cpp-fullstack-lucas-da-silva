// projeto_repositorio.hpp - Acesso à tabela "projetos" (entidade de apoio do demo).
//
// Mesmo padrão do RecadoRepositorio: TODO o SQL do recurso fica aqui; as rotas só chamam estas funções.
#pragma once

#include <nlohmann/json.hpp>

#include "banco.hpp"

class ProjetoRepositorio {
public:
    explicit ProjetoRepositorio(Conexao& banco) : banco_(banco) {}

    // Lista os projetos em ordem alfabética, cada um com "total_tarefas" (LEFT JOIN + COUNT).
    nlohmann::json listar();

    // Devolve o projeto com o id informado (também com total_tarefas), ou null se não existir.
    nlohmann::json buscar(long long id);

    // Insere e devolve o projeto criado. Nome repetido lança ErroBanco (1062) -> a rota responde 409.
    nlohmann::json criar(const nlohmann::json& dados);

    // Remove. Devolve true se existia, false se o id não existe.
    // Projeto que ainda tem tarefas lança ErroBanco (1451) -> a rota responde 409.
    bool remover(long long id);

private:
    Conexao& banco_;
};
