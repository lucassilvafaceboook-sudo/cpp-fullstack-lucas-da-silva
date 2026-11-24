// rotas_recados.hpp - Rotas HTTP do recurso "recados" (CRUD completo).
//
//   GET    /api/recados          lista (aceita ?busca=texto)
//   GET    /api/recados/:id      busca um
//   POST   /api/recados          cria
//   PUT    /api/recados/:id      atualiza
//   DELETE /api/recados/:id      remove
#pragma once

#include <httplib.h>

#include "config.hpp"

void registrarRotasRecados(httplib::Server& servidor, const Config& config);
