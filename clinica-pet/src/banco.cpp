#include "banco.hpp"

#include <cstdlib>
#include <memory>

#include <mysql.h>

namespace {

std::string variavel(const char* nome, const char* padrao) {
    const char* valor = std::getenv(nome);
    return (valor && *valor) ? valor : padrao;
}

// Cada thread do servidor HTTP tem a sua própria conexão com o banco
// (uma conexão do MariaDB não pode ser usada por duas threads ao mesmo tempo).
struct ConexaoDaThread {
    MYSQL* mysql = nullptr;
    ~ConexaoDaThread() {
        if (mysql) mysql_close(mysql);
    }
};
thread_local ConexaoDaThread conexaoDaThread;

MYSQL* abrir() {
    MYSQL*& mysql = conexaoDaThread.mysql;
    if (mysql && mysql_ping(mysql) == 0) return mysql; // já conectado

    if (mysql) {
        mysql_close(mysql);
        mysql = nullptr;
    }
    mysql = mysql_init(nullptr);
    if (!mysql) throw ErroBanco(0, "Sem memória para conectar ao banco.");

    const std::string host = variavel("DB_HOST", "127.0.0.1");
    const std::string usuario = variavel("DB_USER", "root");
    const std::string senha = variavel("DB_PASSWORD", "root");
    const std::string banco = variavel("DB_NAME", "clinica_pet");
    const unsigned int porta = static_cast<unsigned int>(std::atoi(variavel("DB_PORT", "3306").c_str()));

    if (!mysql_real_connect(mysql, host.c_str(), usuario.c_str(), senha.c_str(), banco.c_str(), porta,
                            nullptr, 0)) {
        ErroBanco erro(mysql_errno(mysql), std::string("Não foi possível conectar ao banco: ") + mysql_error(mysql));
        mysql_close(mysql);
        mysql = nullptr;
        throw erro;
    }
    mysql_set_character_set(mysql, "utf8mb4");
    return mysql;
}

// Fecha o statement automaticamente ao sair do escopo
struct Statement {
    MYSQL_STMT* stmt;
    explicit Statement(MYSQL* mysql) : stmt(mysql_stmt_init(mysql)) {}
    ~Statement() {
        if (stmt) mysql_stmt_close(stmt);
    }
    [[noreturn]] void falhar() const {
        throw ErroBanco(mysql_stmt_errno(stmt), mysql_stmt_error(stmt));
    }
};

// Prepara o SQL e liga os parâmetros (todos como texto)
void preparar(Statement& st, const std::string& sql, const std::vector<std::string>& parametros,
              std::vector<MYSQL_BIND>& binds, std::vector<unsigned long>& tamanhos) {
    if (!st.stmt) throw ErroBanco(0, "Sem memória para preparar o SQL.");
    if (mysql_stmt_prepare(st.stmt, sql.c_str(), sql.size()) != 0) st.falhar();

    if (mysql_stmt_param_count(st.stmt) != parametros.size())
        throw ErroBanco(0, "Quantidade de parâmetros '?' diferente da quantidade de valores.");

    binds.assign(parametros.size(), MYSQL_BIND{});
    tamanhos.assign(parametros.size(), 0);
    for (size_t i = 0; i < parametros.size(); ++i) {
        tamanhos[i] = static_cast<unsigned long>(parametros[i].size());
        binds[i].buffer_type = MYSQL_TYPE_STRING;
        binds[i].buffer = const_cast<char*>(parametros[i].data());
        binds[i].buffer_length = tamanhos[i];
        binds[i].length = &tamanhos[i];
    }
    if (!binds.empty() && mysql_stmt_bind_param(st.stmt, binds.data()) != 0) st.falhar();
}

} // namespace

// ------------------------------------------------------------------ Linha

bool Linha::nulo(const std::string& coluna) const {
    auto it = colunas.find(coluna);
    return it == colunas.end() || !it->second.has_value();
}

std::string Linha::texto(const std::string& coluna) const {
    auto it = colunas.find(coluna);
    if (it == colunas.end() || !it->second) return "";
    return *it->second;
}

long long Linha::inteiro(const std::string& coluna) const {
    return nulo(coluna) ? 0 : std::atoll(texto(coluna).c_str());
}

double Linha::decimal(const std::string& coluna) const {
    return nulo(coluna) ? 0.0 : std::atof(texto(coluna).c_str());
}

// ---------------------------------------------------------------- Conexao

std::vector<Linha> Conexao::consultar(const std::string& sql, const std::vector<std::string>& parametros) {
    Statement st(abrir());
    std::vector<MYSQL_BIND> bindsParam;
    std::vector<unsigned long> tamanhosParam;
    preparar(st, sql, parametros, bindsParam, tamanhosParam);

    // Pede ao banco o tamanho máximo de cada coluna, para criar buffers do tamanho certo
    bool atualizarTamanho = true;
    mysql_stmt_attr_set(st.stmt, STMT_ATTR_UPDATE_MAX_LENGTH, &atualizarTamanho);

    if (mysql_stmt_execute(st.stmt) != 0) st.falhar();
    if (mysql_stmt_store_result(st.stmt) != 0) st.falhar();

    std::unique_ptr<MYSQL_RES, decltype(&mysql_free_result)> meta(mysql_stmt_result_metadata(st.stmt),
                                                                  &mysql_free_result);
    if (!meta) return {}; // comando sem resultado

    const unsigned int qtdColunas = mysql_num_fields(meta.get());
    MYSQL_FIELD* campos = mysql_fetch_fields(meta.get());

    // Cada coluna é lida como texto
    std::vector<MYSQL_BIND> binds(qtdColunas, MYSQL_BIND{});
    std::vector<std::vector<char>> buffers(qtdColunas);
    std::vector<unsigned long> tamanhos(qtdColunas, 0);
    std::vector<my_bool> nulos(qtdColunas, 0);
    for (unsigned int i = 0; i < qtdColunas; ++i) {
        buffers[i].resize(campos[i].max_length + 1);
        binds[i].buffer_type = MYSQL_TYPE_STRING;
        binds[i].buffer = buffers[i].data();
        binds[i].buffer_length = static_cast<unsigned long>(buffers[i].size());
        binds[i].length = &tamanhos[i];
        binds[i].is_null = &nulos[i];
    }
    if (qtdColunas > 0 && mysql_stmt_bind_result(st.stmt, binds.data()) != 0) st.falhar();

    std::vector<Linha> linhas;
    while (true) {
        const int r = mysql_stmt_fetch(st.stmt);
        if (r == MYSQL_NO_DATA) break;
        if (r == 1) st.falhar();
        Linha linha;
        for (unsigned int i = 0; i < qtdColunas; ++i) {
            if (nulos[i]) linha.colunas[campos[i].name] = std::nullopt;
            else linha.colunas[campos[i].name] = std::string(buffers[i].data(), tamanhos[i]);
        }
        linhas.push_back(std::move(linha));
    }
    return linhas;
}

std::optional<Linha> Conexao::consultarUm(const std::string& sql, const std::vector<std::string>& parametros) {
    auto linhas = consultar(sql, parametros);
    if (linhas.empty()) return std::nullopt;
    return linhas.front();
}

ResultadoExecucao Conexao::executar(const std::string& sql, const std::vector<std::string>& parametros) {
    Statement st(abrir());
    std::vector<MYSQL_BIND> binds;
    std::vector<unsigned long> tamanhos;
    preparar(st, sql, parametros, binds, tamanhos);
    if (mysql_stmt_execute(st.stmt) != 0) st.falhar();

    ResultadoExecucao r;
    r.idInserido = mysql_stmt_insert_id(st.stmt);
    r.linhasAfetadas = mysql_stmt_affected_rows(st.stmt);
    return r;
}

bool Conexao::funcionando() {
    try {
        auto linha = consultarUm("SELECT 1 AS ok");
        return linha && linha->texto("ok") == "1";
    } catch (const ErroBanco&) {
        return false;
    }
}
