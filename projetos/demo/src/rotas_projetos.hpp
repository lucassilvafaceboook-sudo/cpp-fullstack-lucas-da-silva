// rotas_projetos.hpp - Rotas HTTP do recurso "projetos" (entidade de apoio: sem PUT de propósito).
//
//   GET    /api/projetos         lista (cada projeto traz total_tarefas)
//   POST   /api/projetos         cria            (nome repetido -> 409)
//   DELETE /api/projetos/:id     remove          (projeto com tarefas -> 409)
#pragma once

#include <httplib.h>

#include "config.hpp"

void registrarRotasProjetos(httplib::Server& servidor, const Config& config);
