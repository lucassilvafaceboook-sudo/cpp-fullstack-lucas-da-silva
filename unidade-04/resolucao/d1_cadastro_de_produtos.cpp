// Atividade D1 - Projeto da unidade: Cadastro orientado a objetos
//
// Escolhas de projeto:
// 1) Atributos privados (nome_, preco_, quantidade_, diasParaVencer_): garantem
//    invariantes da classe, impedindo preco/quantidade negativos ou nome vazio fora
//    dos construtores e metodos validados.
// 2) Destrutor virtual em Produto: indispensavel porque o catalogo armazena ponteiros
//    Produto* que apontam para ProdutoPerecivel; sem virtual, delete causaria
//    comportamento indefinido e nao chamaria o destrutor da derivada.
// 3) operator+ exige o mesmo nome: somar estoques so faz sentido para o mesmo item;
//    combinar produtos distintos geraria dados inconsistentes.
//
// Tres testes de entrada invalida alem dos do main:
// 1) Produto("Caderno", 10.0, -5) -> lanca std::invalid_argument("Quantidade negativa")
// 2) catalogo[0]->atualizarPreco(-2.5) -> lanca std::invalid_argument("Preco negativo")
// 3) catalogo[1]->adicionarEstoque(-10) -> lanca std::invalid_argument("Quantidade a adicionar deve ser positiva")

#include <cstddef>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

template <typename A, typename B>
class Par {
public:
    Par(const A& primeiro, const B& segundo) : primeiro_(primeiro), segundo_(segundo) {}
    const A& primeiro() const { return primeiro_; }
    const B& segundo() const { return segundo_; }

private:
    A primeiro_;
    B segundo_;
};

class Produto {
public:
    Produto(const std::string& nome, double preco, int quantidade)
        : nome_(nome), preco_(preco), quantidade_(quantidade) {
        if (nome_.empty()) {
            throw std::invalid_argument("Nome vazio");
        }
        if (preco_ < 0.0) {
            throw std::invalid_argument("Preco negativo");
        }
        if (quantidade_ < 0) {
            throw std::invalid_argument("Quantidade negativa");
        }
    }
    virtual ~Produto() = default;

    const std::string& nome() const { return nome_; }
    double preco() const { return preco_; }
    int quantidade() const { return quantidade_; }

    void atualizarPreco(double novoPreco) {
        if (novoPreco < 0.0) {
            throw std::invalid_argument("Preco negativo");
        }
        preco_ = novoPreco;
    }

    void adicionarEstoque(int quantidade) {
        if (quantidade <= 0) {
            throw std::invalid_argument("Quantidade a adicionar deve ser positiva");
        }
        quantidade_ += quantidade;
    }

    virtual std::string descricao() const {
        std::ostringstream oss;
        oss << nome_ << " - R$ " << std::fixed << std::setprecision(2) << preco_
            << " - " << quantidade_ << " un.";
        return oss.str();
    }

    Produto operator+(const Produto& outro) const {
        if (nome_ != outro.nome_) {
            throw std::invalid_argument("Produtos diferentes nao podem ser combinados");
        }
        return Produto(nome_, preco_, quantidade_ + outro.quantidade_);
    }

private:
    std::string nome_;
    double preco_;
    int quantidade_;
};

class ProdutoPerecivel : public Produto {
public:
    ProdutoPerecivel(const std::string& nome, double preco, int quantidade, int diasParaVencer)
        : Produto(nome, preco, quantidade), diasParaVencer_(diasParaVencer) {
        if (diasParaVencer_ < 0) {
            throw std::invalid_argument("Prazo de validade invalido");
        }
    }

    std::string descricao() const override {
        return Produto::descricao() + " - vence em " + std::to_string(diasParaVencer_) + " dia(s)";
    }

private:
    int diasParaVencer_;
};

// O main ja esta pronto: nao precisa alterar.
void listar(const std::vector<Produto*>& catalogo) {
    for (std::size_t i = 0; i < catalogo.size(); ++i) {
        std::cout << catalogo[i]->descricao() << '\n';
    }
}

int main() {
    std::vector<Produto*> catalogo;
    catalogo.push_back(new Produto("Caneta", 2.5, 100));
    catalogo.push_back(new ProdutoPerecivel("Leite", 5.99, 20, 7));

    std::cout << "== Catalogo ==\n";
    listar(catalogo);

    catalogo[0]->atualizarPreco(3.0);
    catalogo[1]->adicionarEstoque(10);
    std::cout << "== Apos atualizacoes ==\n";
    listar(catalogo);

    Produto a("Caneta", 3.0, 100);
    Produto b("Caneta", 3.0, 50);
    Produto soma = a + b;
    std::cout << "== Combinacao ==\n";
    std::cout << soma.descricao() << '\n';

    std::cout << "== Entradas invalidas ==\n";
    try {
        Produto p("", 1.0, 1);
    } catch (const std::invalid_argument& erro) {
        std::cout << "Erro: " << erro.what() << '\n';
    }
    try {
        Produto p("Lapis", -1.0, 5);
    } catch (const std::invalid_argument& erro) {
        std::cout << "Erro: " << erro.what() << '\n';
    }
    try {
        ProdutoPerecivel p("Iogurte", 3.0, 5, -2);
    } catch (const std::invalid_argument& erro) {
        std::cout << "Erro: " << erro.what() << '\n';
    }
    try {
        Produto s = a + Produto("Borracha", 1.0, 1);
        (void)s;
    } catch (const std::invalid_argument& erro) {
        std::cout << "Erro: " << erro.what() << '\n';
    }
    try {
        catalogo[0]->adicionarEstoque(0);
    } catch (const std::invalid_argument& erro) {
        std::cout << "Erro: " << erro.what() << '\n';
    }

    double total{0.0};
    for (std::size_t i = 0; i < catalogo.size(); ++i) {
        total += catalogo[i]->preco() * catalogo[i]->quantidade();
    }
    Par<std::string, double> resumo("Valor total em estoque", total);
    std::cout << "== Resumo ==\n";
    std::cout << std::fixed << std::setprecision(2);
    std::cout << resumo.primeiro() << ": R$ " << resumo.segundo() << '\n';

    for (std::size_t i = 0; i < catalogo.size(); ++i) {
        delete catalogo[i];
    }
    return 0;
}