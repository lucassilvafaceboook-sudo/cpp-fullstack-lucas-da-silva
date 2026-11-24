// rotas_tarefas.hpp - Rotas HTTP do recurso "tarefas" (CRUD completo).
//
//   GET    /api/tarefas          lista (aceita ?busca=texto&status=feito&projeto_id=2, combinados com E)
//   GET    /api/tarefas/resumo   números do painel (totais, atrasadas, horas, andamento por projeto)
//   GET    /api/tarefas/:id      busca uma
//   POST   /api/tarefas          cria            (projeto_id inexistente -> 422)
//   PUT    /api/tarefas/:id      atualiza
//   DELETE /api/tarefas/:id      remove
//   POST   /api/tarefas/:id/concluir   marca como feito (já concluída -> 409)
#pragma once

#include <httplib.h>

#include "config.hpp"

void registrarRotasTarefas(httplib::Server& servidor, const Config& config);
