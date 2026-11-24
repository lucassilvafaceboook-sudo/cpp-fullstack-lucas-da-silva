// Atividade D4 - Relatório de vendas só com algoritmos da STL
#include <algorithm>
#include <iostream>
#include <iterator>
#include <numeric>
#include <string>
#include <vector>

struct Venda {
    std::string produto;
    double preco;
    int quantidade;
};

double total(const Venda& venda) { return venda.preco * venda.quantidade; }

void mostrarNomes(const char* rotulo, const std::vector<Venda>& vendas) {
    std::cout << rotulo;
    for (std::size_t i = 0; i < vendas.size(); ++i) {
        std::cout << ' ' << vendas[i].produto;
    }
    std::cout << '\n';
}

int main() {
    int n{};
    std::vector<Venda> vendas;

    std::cout << "Quantidade de vendas: ";
    // TODO: leia n e valide (1 a 20)

    std::cout << "Vendas (produto preco quantidade):\n";
    // TODO: leia as n vendas, validando as leituras e rejeitando preço/quantidade negativos

    // TODO: transform -> vector<double> de totais; mostre "Totais: ..."
    // TODO: accumulate -> "Soma: ..."
    // TODO: max_element com lambda -> "Maior venda: produto (total)"
    // TODO: all_of / any_of -> "Todas com quantidade > 0: ..." e "Alguma abaixo de 10: ..."
    // TODO: erase-remove (total < 20) -> mostrarNomes("Apos remover totais abaixo de 20:", vendas)
    // TODO: stable_partition (total >= 60 primeiro) -> mostrarNomes("Ordem estavel (totais >= 60 primeiro):", vendas)
    (void)n;
    return 0;
}
