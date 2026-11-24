// banco.hpp - Acesso ao MariaDB/MySQL com a biblioteca C (libmariadb).
//
// Esta é uma "casca" simples sobre a API C. Ela oferece:
//   - Conexao: abre a conexão no construtor e fecha no destrutor (RAII, como o Buffer da Unidade 4);
//   - consultar(): executa um SELECT e devolve um JSON (array de objetos, um por linha);
//   - executar(): executa INSERT/UPDATE/DELETE e devolve o número de linhas afetadas.
//
// Os valores SEMPRE vão como parâmetros "?" (prepared statements), e nunca concatenados no texto do SQL.
// Isso evita SQL injection. Veja projetos/guia/04-banco-mariadb.md.
#pragma once

#include <memory>
#include <stdexcept>
#include <string>
#include <vector>

#include <nlohmann/json.hpp>

#include "config.hpp"

// Erro de banco: carrega o código numérico do MariaDB (por exemplo, 1062 = chave duplicada).
class ErroBanco : public std::runtime_error {
public:
    ErroBanco(const std::string& mensagem, unsigned int codigo) : std::runtime_error(mensagem), codigo_(codigo) {}

    unsigned int codigo() const { return codigo_; }
    bool chaveDuplicada() const { return codigo_ == 1062; }
    bool violacaoDeChaveEstrangeira() const { return codigo_ == 1451 || codigo_ == 1452; }
    // Violação de um CHECK (ex.: preco >= 0). 4025 = MariaDB, 3819 = MySQL 8.
    bool restricaoViolada() const { return codigo_ == 4025 || codigo_ == 3819; }

private:
    unsigned int codigo_;
};

// Deve ser chamada UMA vez, no início de main(), antes de criar threads/conexões.
void iniciarBiblioteca();

class Conexao {
public:
    using Parametros = std::vector<std::string>;

    explicit Conexao(const Config& config);  // lança ErroBanco se não conseguir conectar
    ~Conexao();

    Conexao(const Conexao&) = delete;
    Conexao& operator=(const Conexao&) = delete;

    // SELECT. Colunas inteiras viram números JSON, decimais viram números reais, NULL vira null,
    // o resto vira texto. Devolve sempre um array (vazio se não houver linhas).
    nlohmann::json consultar(const std::string& sql, const Parametros& parametros = {});

    // INSERT / UPDATE / DELETE. Devolve o número de linhas afetadas.
    unsigned long long executar(const std::string& sql, const Parametros& parametros = {});

    // Id gerado (AUTO_INCREMENT) pelo último INSERT feito com executar().
    unsigned long long ultimoId() const { return ultimoId_; }

private:
    struct Impl;
    std::unique_ptr<Impl> impl_;
    unsigned long long ultimoId_{0};
};
