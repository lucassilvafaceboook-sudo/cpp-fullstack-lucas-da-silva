// Atividade I2 - Filtros com lambdas: captura por valor e por referência
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
    // TODO: std::copy_if(..., std::back_inserter(filtrados), lambda [minimo, maximo, &verificacoes])
    // TODO: mostre "Dentro da faixa: ..." e "Verificacoes feitas: N"

    int soma{0};
    // TODO: std::for_each com lambda [&soma]; mostre "Soma dos filtrados: N"
    // TODO: se houver filtrados, calcule a média e mostre
    //       "Maiores que a media dos filtrados (<media>): ..." usando uma lambda [media]
    (void)verificacoes;
    (void)soma;
    return 0;
}
