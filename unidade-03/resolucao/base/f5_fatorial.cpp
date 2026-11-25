// Atividade F5 - Fatorial recursivo e iterativo
#include <iostream>

unsigned long long fatorialRecursivo(unsigned int n) {
    if (n <= 1) {
        return 1; // Caso-base: 0! = 1 e 1! = 1
    }
    return n * fatorialRecursivo(n - 1);
}

unsigned long long fatorialIterativo(unsigned int n) {
    unsigned long long resultado{1};
    for (unsigned int i = 2; i <= n; ++i) {
        resultado *= i;
    }
    return resultado;
}

int main() {
    int n{};

    std::cout << "N (0 a 20): ";
    if (!(std::cin >> n) || n < 0 || n > 20) {
        std::cerr << "Entrada invalida (use 0 a 20).\n";
        return 1;
    }

    auto un = static_cast<unsigned int>(n);
    unsigned long long rec{fatorialRecursivo(un)};
    unsigned long long ite{fatorialIterativo(un)};

    std::cout << "Recursivo: " << n << "! = " << rec << '\n';
    std::cout << "Iterativo: " << n << "! = " << ite << '\n';
    std::cout << "Resultados iguais: " << (rec == ite ? "sim" : "nao") << '\n';

    // Um unsigned long long de 64 bits armazena ate ~1,84 x 10^19.
    // 20! (~2,43 x 10^18) ainda cabe, mas 21! (~5,1 x 10^19) causa overflow.
    return 0;
}