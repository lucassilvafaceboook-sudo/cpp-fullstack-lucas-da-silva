// Atividade F4 - Soma de 1 a N e lista de pares

#include <iostream>

int main() {
    int n{};

    std::cout << "N: ";
    if (!(std::cin >> n) || n <= 0) {
        std::cerr << "Entrada invalida.\n";
        return 1;
    }

    int soma{0};
    for (int i = 1; i <= n; ++i) {
        soma += i;
    }

    std::cout << "Soma de 1 a " << n << ": " << soma << '\n';

    int quantidadePares{0};
    std::cout << "Pares:";
    for (int i = 1; i <= n; ++i) {
        if (i % 2 == 0) {
            std::cout << ' ' << i;
            ++quantidadePares;
        }
    }
    std::cout << '\n';
    std::cout << "Quantidade de pares: " << quantidadePares << '\n';

    return 0;
}