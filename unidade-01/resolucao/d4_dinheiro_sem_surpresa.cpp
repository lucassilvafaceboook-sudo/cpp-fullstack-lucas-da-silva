// Atividade D4 - Dinheiro sem surpresa

#include <iomanip>
#include <iostream>

int main() {
    // Parte 1: o problema do double
    double a{0.1};
    double b{0.2};

    std::cout << std::boolalpha;
    std::cout << "0.1 + 0.2 == 0.3 ? " << (a + b == 0.3) << " (double)\n";
    std::cout << "0.1 + 0.2 = " << std::setprecision(17) << (a + b) << "\n";

    // Parte 2: dinheiro em centavos (long long)
    long long precoA{1990}; // R$ 19,90
    long long precoB{510};  // R$ 5,10
    long long precoC{10};   // R$ 0,10

    constexpr long long CENTAVOS_POR_REAL{100};
    constexpr long long TAXA_DESCONTO{15};
    constexpr long long MEIO_CENTAVO{50};

    long long totalCentavos{precoA + precoB + precoC};
    long long descontoCentavos{(totalCentavos * TAXA_DESCONTO + MEIO_CENTAVO) / CENTAVOS_POR_REAL};
    long long totalComDesconto{totalCentavos - descontoCentavos};

    std::cout << "Soma em centavos: " << totalCentavos << "\n";

    std::cout << "Total: R$ " << (totalCentavos / CENTAVOS_POR_REAL) << ","
              << std::setfill('0') << std::setw(2) << (totalCentavos % CENTAVOS_POR_REAL)
              << std::setfill(' ') << "\n";

    std::cout << "Desconto 15%: R$ " << (descontoCentavos / CENTAVOS_POR_REAL) << ","
              << std::setfill('0') << std::setw(2) << (descontoCentavos % CENTAVOS_POR_REAL)
              << std::setfill(' ') << "\n";

    std::cout << "Total com desconto: R$ " << (totalComDesconto / CENTAVOS_POR_REAL) << ","
              << std::setfill('0') << std::setw(2) << (totalComDesconto % CENTAVOS_POR_REAL)
              << std::setfill(' ') << "\n";

    // Por que nao guardar dinheiro em double?
    // O tipo double representa numeros em ponto flutuante binario (base 2), que nao consegue
    // armazenar exatamente varias fracoes decimais simples (como 0.1 ou 0.2). Em calculos
    // financeiros, esses pequenos erros de arredondamento se acumulam, causando divergencias
    // em somas, impostos e comparacoes de igualdade. Usar inteiros em centavos garante
    // aritmetica exata.

    return 0;
}