#include "projeto_repositorio.hpp"

#include "parametros.hpp"

using nlohmann::json;

namespace {

// LEFT JOIN: projetos SEM tarefas também aparecem (com total 0). COUNT(t.id) ignora os NULL do LEFT JOIN.
const char* const kSelect =
    "SELECT p.id, p.nome, p.descricao, p.criado_em, COUNT(t.id) AS total_tarefas "
    "FROM projetos p LEFT JOIN tarefas t ON t.projeto_id = p.id ";

const char* const kAgrupar = "GROUP BY p.id, p.nome, p.descricao, p.criado_em ";

}  // namespace

json ProjetoRepositorio::listar() {
    return banco_.consultar(std::string(kSelect) + kAgrupar + "ORDER BY p.nome");
}

json ProjetoRepositorio::buscar(long long id) {
    json linhas = banco_.consultar(std::string(kSelect) + "WHERE p.id = ? " + kAgrupar, {std::to_string(id)});
    return linhas.empty() ? json(nullptr) : linhas.front();
}

json ProjetoRepositorio::criar(const json& dados) {
    // NULLIF(?, ''): descrição vazia vira NULL de verdade (e não um texto vazio).
    banco_.executar("INSERT INTO projetos (nome, descricao) VALUES (?, NULLIF(?, ''))",
                    {parametros::comoTexto(dados.at("nome")), parametros::opcional(dados, "descricao")});
    return buscar(static_cast<long long>(banco_.ultimoId()));
}

bool ProjetoRepositorio::remover(long long id) {
    return banco_.executar("DELETE FROM projetos WHERE id = ?", {std::to_string(id)}) > 0;
}
