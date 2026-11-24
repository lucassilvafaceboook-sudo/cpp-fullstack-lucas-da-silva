// tarefa_repositorio.hpp - Acesso à tabela "tarefas" (entidade principal do demo).
//
// Cada tarefa vem com "projeto_nome" (JOIN com projetos), para a tela mostrar o nome em vez do número.
#pragma once

#include <string>

#include <nlohmann/json.hpp>

#include "banco.hpp"

// Filtros opcionais da listagem (campo vazio = sem filtro). Já chegam validados pela rota.
struct FiltrosTarefa {
    std::string busca;      // procura no título, na descrição e no nome do projeto
    std::string status;     // pendente | andamento | feito
    std::string projetoId;  // id do projeto
};

class TarefaRepositorio {
public:
    explicit TarefaRepositorio(Conexao& banco) : banco_(banco) {}

    // Lista as tarefas (da mais nova para a mais antiga), aplicando os filtros informados (todos juntos, com E).
    nlohmann::json listar(const FiltrosTarefa& filtros = {});

    // Números para o painel: totais por status, atrasadas, horas restantes e andamento por projeto.
    nlohmann::json resumo();

    // Marca a tarefa como "feito" e registra o momento da conclusão. Devolve a tarefa atualizada.
    nlohmann::json concluir(long long id);

    // Devolve a tarefa com o id informado, ou null se não existir.
    nlohmann::json buscar(long long id);

    // Insere e devolve a tarefa criada. A rota já conferiu que o projeto existe.
    nlohmann::json criar(const nlohmann::json& dados);

    // Atualiza (substitui todos os campos). Devolve a tarefa atualizada, ou null se o id não existir.
    nlohmann::json atualizar(long long id, const nlohmann::json& dados);

    // Remove. Devolve true se existia, false se o id não existe.
    bool remover(long long id);

private:
    Conexao& banco_;
};
