// Acesso ao MariaDB.
//
// Todo SQL usa parâmetros "?" (prepared statements): os valores nunca são
// colados no texto do SQL, então não existe SQL injection.
// Todos os parâmetros são enviados como TEXTO. Por isso um campo opcional
// vazio chega ao banco como '' e usamos NULLIF(?, '') para gravar NULL.
#pragma once

#include <map>
#include <optional>
#include <stdexcept>
#include <string>
#include <vector>

// Uma linha do resultado: nome da coluna -> valor (std::nullopt quando é NULL)
class Linha {
public:
    std::map<std::string, std::optional<std::string>> colunas;

    bool nulo(const std::string& coluna) const;
    std::string texto(const std::string& coluna) const;   // NULL vira ""
    long long inteiro(const std::string& coluna) const;   // NULL vira 0
    double decimal(const std::string& coluna) const;      // NULL vira 0
};

// Resultado de INSERT/UPDATE/DELETE
struct ResultadoExecucao {
    unsigned long long idInserido = 0;
    unsigned long long linhasAfetadas = 0;
};

// Erro vindo do banco, com o código do MariaDB (ex.: 1062 = chave duplicada)
class ErroBanco : public std::runtime_error {
public:
    ErroBanco(unsigned int codigo, const std::string& mensagem)
        : std::runtime_error(mensagem), codigo(codigo) {}
    unsigned int codigo;
};

// Códigos de erro do MariaDB usados no tratamento de erros da API
namespace CodigoErro {
    constexpr unsigned int DUPLICADO = 1062;           // UNIQUE violado
    constexpr unsigned int EM_USO = 1451;              // FK: registro usado por outro
    constexpr unsigned int REFERENCIA_INEXISTENTE = 1452; // FK: registro apontado não existe
    constexpr unsigned int CHECK_VIOLADO = 4025;       // CONSTRAINT CHECK
    constexpr unsigned int VALOR_INVALIDO = 1292;      // ex.: data inválida
}

class Conexao {
public:
    // SELECT: devolve as linhas
    static std::vector<Linha> consultar(const std::string& sql,
                                        const std::vector<std::string>& parametros = {});
    // SELECT que deve devolver no máximo uma linha
    static std::optional<Linha> consultarUm(const std::string& sql,
                                            const std::vector<std::string>& parametros = {});
    // INSERT / UPDATE / DELETE
    static ResultadoExecucao executar(const std::string& sql,
                                      const std::vector<std::string>& parametros = {});
    // Testa se o banco responde (rota /api/saude/banco)
    static bool funcionando();
};
