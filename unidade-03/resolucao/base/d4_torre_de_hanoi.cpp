// Atividade D4 - Torre de Hanoi
#include <iostream>

void hanoi(int n, char origem, char destino, char auxiliar, int& movimentos, bool imprimir) {
    if (n == 0) {
        return; // Caso-base
    }

    hanoi(n - 1, origem, auxiliar, destino, movimentos, imprimir);

    ++movimentos;
    if (imprimir) {
        std::cout << "Mover disco " << n << " de " << origem << " para " << destino << '\n';
    }

    hanoi(n - 1, auxiliar, destino, origem, movimentos, imprimir);
}

int main() {
    int n{};

    std::cout << "Discos (1 a 10): ";
    if (!(std::cin >> n) || n < 1 || n > 10) {
        std::cerr << "Entrada invalida.\n";
        return 1;
    }

    int movimentos{0};
    hanoi(n, 'A', 'C', 'B', movimentos, n <= 4);

    if (n > 4) {
        std::cout << "Movimentos nao listados (n > 4).\n";
    }

    int minimoTeorico{(1 << n) - 1};
    std::cout << "Total de movimentos: " << movimentos << '\n';
    std::cout << "Minimo teorico (2^n - 1): " << minimoTeorico << '\n';
    return 0;
}