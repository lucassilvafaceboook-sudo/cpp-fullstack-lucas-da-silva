// Atividade I5 - Padroes com lacos aninhados

#include <iostream>

int main() {
    int h{};

    std::cout << "Altura: ";
    if (!(std::cin >> h) || h < 1 || h > 20) {
        std::cerr << "Entrada invalida.\n";
        return 1;
    }

    // Triangulo retangulo: linha i tem i asteriscos
    for (int i = 1; i <= h; ++i) {
        for (int j = 0; j < i; ++j) {
            std::cout << '*';
        }
        std::cout << '\n';
    }

    std::cout << '\n';

    // Piramide centralizada: (h - i) espacos seguidos de (2 * i - 1) asteriscos
    for (int i = 1; i <= h; ++i) {
        for (int esp = 0; esp < h - i; ++esp) {
            std::cout << ' ';
        }
        for (int ast = 0; ast < 2 * i - 1; ++ast) {
            std::cout << '*';
        }
        std::cout << '\n';
    }

    return 0;
}