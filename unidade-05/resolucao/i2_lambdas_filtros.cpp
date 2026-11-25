// Atividade I2 - Filtros com lambdas: captura por valor e por referencia
#include <algorithm>
#include <iostream>
#include <iterator>
#include <vector>

int main() {
    std::vector<int> numeros{3, 8, 12, 5, 20, 7, 15, 10};
    int minimo{};
    int maximo{};

    std::cout << "Minimo e maximo: ";
    if (!(std::cin >> minimo >> maximo)) {
        std::cerr << "Entrada invalida.\n";
        return 1;
    }

    std::cout << "Numeros:";
    for (std::size_t i = 0; i < numeros.size(); ++i) {
        std::cout << ' ' << numeros[i];
    }
    std::cout << '\n';

    std::vector<int> filtrados;
    int verificacoes{0};
    std::copy_if(numeros.begin(), numeros.end(), std::back_inserter(filtrados),
                 [minimo, maximo, &verificacoes](int x) {
                     ++verificacoes;
                     return x >= minimo && x <= maximo;
                 });

    std::cout << "Dentro da faixa:";
    for (int x : filtrados) {
        std::cout << ' ' << x;
    }
    std::cout << '\n';
    std::cout << "Verificacoes feitas: " << verificacoes << '\n';

    int soma{0};
    std::for_each(filtrados.begin(), filtrados.end(), [&soma](int x) { soma += x; });
    std::cout << "Soma dos filtrados: " << soma << '\n';

    if (!filtrados.empty()) {
        double media = static_cast<double>(soma) / static_cast<double>(filtrados.size());
        std::cout << "Maiores que a media dos filtrados (" << media << "):";
        std::for_each(filtrados.begin(), filtrados.end(), [media](int x) {
            if (x > media) {
                std::cout << ' ' << x;
            }
        });
        std::cout << '\n';
    }
    return 0;
}