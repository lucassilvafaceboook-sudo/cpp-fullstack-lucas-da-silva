// banco.cpp - Implementação do acesso ao banco (libmariadb).
// Você normalmente NÃO precisa alterar este arquivo: use Conexao::consultar() e Conexao::executar().
#include "banco.hpp"

#include <cstring>
#include <type_traits>

#if __has_include(<mariadb/mysql.h>)
#include <mariadb/mysql.h>
#else
#include <mysql.h>
#endif

void iniciarBiblioteca() {
    mysql_library_init(0, nullptr, nullptr);
}

struct Conexao::Impl {
    MYSQL* mysql{nullptr};
    ~Impl() {
        if (mysql != nullptr) {
            mysql_close(mysql);
        }
    }
};

namespace {

// Tipo do ponteiro "is_null" de MYSQL_BIND (varia entre versões da biblioteca: char ou bool).
using TipoNulo = std::remove_pointer_t<decltype(MYSQL_BIND::is_null)>;

nlohmann::json converter(enum_field_types tipo, const std::string& valor) {
    try {
        switch (tipo) {
            case MYSQL_TYPE_TINY:
            case MYSQL_TYPE_SHORT:
            case MYSQL_TYPE_LONG:
            case MYSQL_TYPE_INT24:
            case MYSQL_TYPE_LONGLONG:
            case MYSQL_TYPE_YEAR:
                return std::stoll(valor);
            case MYSQL_TYPE_FLOAT:
            case MYSQL_TYPE_DOUBLE:
            case MYSQL_TYPE_DECIMAL:
            case MYSQL_TYPE_NEWDECIMAL:
                return std::stod(valor);
            default:
                return valor;
        }
    } catch (const std::exception&) {
        return valor;  // não coube no tipo numérico: devolve como texto
    }
}

// Uma instrução preparada (prepared statement), fechada automaticamente no destrutor.
class Instrucao {
public:
    Instrucao(MYSQL* mysql, const std::string& sql) : stmt_(mysql_stmt_init(mysql)) {
        if (stmt_ == nullptr) {
            throw ErroBanco("Sem memoria para criar a instrucao SQL", 0);
        }
        if (mysql_stmt_prepare(stmt_, sql.c_str(), static_cast<unsigned long>(sql.size())) != 0) {
            // Se o construtor lança, o destrutor NÃO roda: fechamos a instrução aqui para não vazar.
            ErroBanco erro(mysql_stmt_error(stmt_), mysql_stmt_errno(stmt_));
            mysql_stmt_close(stmt_);
            stmt_ = nullptr;
            throw erro;
        }
    }

    ~Instrucao() {
        if (stmt_ != nullptr) {
            mysql_stmt_close(stmt_);
        }
    }

    Instrucao(const Instrucao&) = delete;
    Instrucao& operator=(const Instrucao&) = delete;

    void executar(const Conexao::Parametros& parametros) {
        if (mysql_stmt_param_count(stmt_) != parametros.size()) {
            throw ErroBanco("Quantidade de parametros diferente da quantidade de '?' no SQL", 0);
        }

        std::vector<MYSQL_BIND> ligacoes(parametros.size());
        std::vector<unsigned long> tamanhos(parametros.size());
        if (!parametros.empty()) {
            std::memset(ligacoes.data(), 0, sizeof(MYSQL_BIND) * ligacoes.size());
            for (std::size_t i = 0; i < parametros.size(); ++i) {
                tamanhos[i] = static_cast<unsigned long>(parametros[i].size());
                ligacoes[i].buffer_type = MYSQL_TYPE_STRING;
                ligacoes[i].buffer = const_cast<char*>(parametros[i].c_str());
                ligacoes[i].buffer_length = tamanhos[i];
                ligacoes[i].length = &tamanhos[i];
            }
            if (mysql_stmt_bind_param(stmt_, ligacoes.data()) != 0) {
                falhar();
            }
        }

        if (mysql_stmt_execute(stmt_) != 0) {
            falhar();
        }
    }

    unsigned long long linhasAfetadas() const { return mysql_stmt_affected_rows(stmt_); }
    unsigned long long idInserido() const { return mysql_stmt_insert_id(stmt_); }

    nlohmann::json lerResultado() {
        MYSQL_RES* metadados = mysql_stmt_result_metadata(stmt_);
        if (metadados == nullptr) {
            return nlohmann::json::array();  // instrução sem resultado (não é SELECT)
        }
        struct LiberaMetadados {
            MYSQL_RES* r;
            ~LiberaMetadados() { mysql_free_result(r); }
        } libera{metadados};

        const unsigned int colunas = mysql_num_fields(metadados);
        MYSQL_FIELD* campos = mysql_fetch_fields(metadados);

        std::vector<MYSQL_BIND> ligacoes(colunas);
        std::vector<unsigned long> tamanhos(colunas, 0);
        std::unique_ptr<TipoNulo[]> nulos(new TipoNulo[colunas]());
        std::memset(ligacoes.data(), 0, sizeof(MYSQL_BIND) * ligacoes.size());
        for (unsigned int i = 0; i < colunas; ++i) {
            // buffer vazio: só queremos saber o tamanho; o valor é buscado depois, com o tamanho exato
            ligacoes[i].buffer_type = MYSQL_TYPE_STRING;
            ligacoes[i].buffer = nullptr;
            ligacoes[i].buffer_length = 0;
            ligacoes[i].length = &tamanhos[i];
            ligacoes[i].is_null = &nulos[i];
        }
        if (mysql_stmt_bind_result(stmt_, ligacoes.data()) != 0) {
            falhar();
        }
        if (mysql_stmt_store_result(stmt_) != 0) {
            falhar();
        }

        nlohmann::json resultado = nlohmann::json::array();
        while (true) {
            int rc = mysql_stmt_fetch(stmt_);
            if (rc == MYSQL_NO_DATA) {
                break;
            }
            if (rc == 1) {
                falhar();
            }
            // rc == 0 ou MYSQL_DATA_TRUNCATED (esperado, pois o buffer é vazio)
            nlohmann::json linha = nlohmann::json::object();
            for (unsigned int i = 0; i < colunas; ++i) {
                if (nulos[i]) {
                    linha[campos[i].name] = nullptr;
                    continue;
                }
                std::string valor(tamanhos[i], '\0');
                if (tamanhos[i] > 0) {
                    MYSQL_BIND coluna;
                    std::memset(&coluna, 0, sizeof(coluna));
                    unsigned long tamanho = 0;
                    coluna.buffer_type = MYSQL_TYPE_STRING;
                    coluna.buffer = &valor[0];
                    coluna.buffer_length = tamanhos[i];
                    coluna.length = &tamanho;
                    if (mysql_stmt_fetch_column(stmt_, &coluna, i, 0) != 0) {
                        falhar();
                    }
                }
                linha[campos[i].name] = converter(campos[i].type, valor);
            }
            resultado.push_back(std::move(linha));
        }
        return resultado;
    }

private:
    [[noreturn]] void falhar() {
        throw ErroBanco(mysql_stmt_error(stmt_), mysql_stmt_errno(stmt_));
    }

    MYSQL_STMT* stmt_;
};

}  // namespace

Conexao::Conexao(const Config& config) : impl_(new Impl) {
    impl_->mysql = mysql_init(nullptr);
    if (impl_->mysql == nullptr) {
        throw ErroBanco("Falha ao inicializar o cliente MariaDB", 0);
    }
    mysql_options(impl_->mysql, MYSQL_SET_CHARSET_NAME, "utf8mb4");
    if (mysql_real_connect(impl_->mysql, config.host.c_str(), config.usuario.c_str(), config.senha.c_str(),
                           config.banco.c_str(), config.porta, nullptr, 0) == nullptr) {
        std::string mensagem = std::string("Nao foi possivel conectar ao banco: ") + mysql_error(impl_->mysql);
        unsigned int codigo = mysql_errno(impl_->mysql);
        throw ErroBanco(mensagem, codigo);  // o Impl fecha o que foi aberto
    }
}

Conexao::~Conexao() = default;

nlohmann::json Conexao::consultar(const std::string& sql, const Parametros& parametros) {
    Instrucao instrucao(impl_->mysql, sql);
    instrucao.executar(parametros);
    return instrucao.lerResultado();
}

unsigned long long Conexao::executar(const std::string& sql, const Parametros& parametros) {
    Instrucao instrucao(impl_->mysql, sql);
    instrucao.executar(parametros);
    ultimoId_ = instrucao.idInserido();
    return instrucao.linhasAfetadas();
}
