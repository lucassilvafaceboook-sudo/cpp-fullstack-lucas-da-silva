// Atividade D1 - Projeto da unidade: Cadastro orientado a objetos
//
// TODO: documente aqui suas escolhas de projeto e três testes de entrada inválida.
#include <cstddef>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

// TODO: template Par<A, B> completo (já há um esqueleto)
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

// TODO: complete a classe Produto (validações, atualizarPreco, adicionarEstoque, descricao, operator+)
class Produto {
public:
    Produto(const std::string& nome, double preco, int quantidade) : preco_(preco), quantidade_(quantidade) {
        (void)nome;
    }
    virtual ~Produto() = default;

    const std::string& nome() const { return nome_; }
    double preco() const { return preco_; }
    int quantidade() const { return quantidade_; }
    void atualizarPreco(double novoPreco) { (void)novoPreco; }
    void adicionarEstoque(int quantidade) { (void)quantidade; }
    virtual std::string descricao() const { return ""; }
    Produto operator+(const Produto& outro) const { return outro; }

private:
    std::string nome_;
    double preco_;
    int quantidade_;
};

// TODO: complete ProdutoPerecivel (diasParaVencer_, validação, descricao com override)
class ProdutoPerecivel : public Produto {
public:
    ProdutoPerecivel(const std::string& nome, double preco, int quantidade, int diasParaVencer)
        : Produto(nome, preco, quantidade) {
        (void)diasParaVencer;
    }
};

// O main já está pronto: não precisa alterar.
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
