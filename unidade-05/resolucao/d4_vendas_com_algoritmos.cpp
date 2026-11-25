// Atividade D4 - Relatorio de vendas so com algoritmos da STL
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
    if (!(std::cin >> n) || n < 1 || n > 20) {
        std::cerr << "Entrada invalida.\n";
        return 1;
    }

    vendas.reserve(static_cast<std::size_t>(n));
    std::cout << "Vendas (produto preco quantidade):\n";
    for (int i = 0; i < n; ++i) {
        Venda v{};
        if (!(std::cin >> v.produto >> v.preco >> v.quantidade) || v.preco < 0.0 || v.quantidade < 0) {
            std::cerr << "Entrada invalida.\n";
            return 1;
        }
        vendas.push_back(v);
    }

    std::vector<double> totais;
    totais.reserve(vendas.size());
    std::transform(vendas.begin(), vendas.end(), std::back_inserter(totais),
                   [](const Venda& v) { return total(v); });

    std::cout << "Totais:";
    for (double t : totais) {
        std::cout << ' ' << t;
    }
    std::cout << '\n';

    double soma = std::accumulate(totais.begin(), totais.end(), 0.0);
    std::cout << "Soma: " << soma << '\n';

    auto itMaior = std::max_element(vendas.begin(), vendas.end(),
                                    [](const Venda& a, const Venda& b) { return total(a) < total(b); });
    std::cout << "Maior venda: " << itMaior->produto << " (" << total(*itMaior) << ")\n";

    bool todasPositivas = std::all_of(vendas.begin(), vendas.end(),
                                      [](const Venda& v) { return v.quantidade > 0; });
    bool algumaBaixa = std::any_of(vendas.begin(), vendas.end(),
                                   [](const Venda& v) { return total(v) < 10.0; });
    std::cout << "Todas com quantidade > 0: " << (todasPositivas ? "sim" : "nao") << '\n';
    std::cout << "Alguma abaixo de 10: " << (algumaBaixa ? "sim" : "nao") << '\n';

    vendas.erase(std::remove_if(vendas.begin(), vendas.end(),
                                [](const Venda& v) { return total(v) < 20.0; }),
                 vendas.end());
    mostrarNomes("Apos remover totais abaixo de 20:", vendas);

    std::stable_partition(vendas.begin(), vendas.end(),
                          [](const Venda& v) { return total(v) >= 60.0; });
    mostrarNomes("Ordem estavel (totais >= 60 primeiro):", vendas);
    return 0;
}