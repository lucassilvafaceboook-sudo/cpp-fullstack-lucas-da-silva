// Atividade I4 - Fibonacci recursivo e o custo das chamadas
#include <iostream>

long long fibRecursivo(int n, long long& chamadas) {
    ++chamadas;
    if (n == 0) return 0; // Caso-base 1
    if (n == 1) return 1; // Caso-base 2
    return fibRecursivo(n - 1, chamadas) + fibRecursivo(n - 2, chamadas);
}

long long fibIterativo(int n) {
    if (n == 0) return 0;
    if (n == 1) return 1;

    long long anterior{0};
    long long atual{1};
    for (int i = 2; i <= n; ++i) {
        long long proximo{anterior + atual};
        anterior = atual;
        atual = proximo;
    }
    return atual;
}

int main() {
    int n{};

    std::cout << "N (0 a 30): ";
    if (!(std::cin >> n) || n < 0 || n > 30) {
        std::cerr << "Entrada invalida.\n";
        return 1;
    }

    long long chamadas{0};
    long long rec{fibRecursivo(n, chamadas)};
    long long ite{fibIterativo(n)};

    std::cout << "Fibonacci(" << n << ") recursivo = " << rec << " (" << chamadas << " chamadas)\n";
    std::cout << "Fibonacci(" << n << ") iterativo = " << ite << '\n';

    // O numero de chamadas cresce exponencialmente porque cada chamada com n >= 2
    // gera duas novas chamadas e recalcula os mesmos subproblemas varias vezes:
    // n = 10 -> 177 chamadas; n = 20 -> 21.891 chamadas; n = 30 -> 2.692.537 chamadas.
    return 0;
}