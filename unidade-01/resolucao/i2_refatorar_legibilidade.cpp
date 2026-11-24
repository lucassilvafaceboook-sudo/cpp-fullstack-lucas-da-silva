// Atividade I2 - Refatorar para ficar legivel
//
// Objetivo:
//   Ler o valor de uma compra, aplicar um desconto fixo de 10% e exibir
//   o valor original, o desconto e o total a pagar com duas casas decimais.
//
// Entradas:
//   - Valor da compra (double)
//
// Saidas:
//   - Valor original, valor do desconto e total a pagar formatados em reais
//
// Compilacao:
//   g++ -std=c++17 -Wall -Wextra i2_refatorar_legibilidade.cpp -o i2.exe

#include <iomanip>
#include <iostream>

int main() {
    constexpr double TAXA_DESCONTO{0.10};

    double valorCompra{};
    std::cout << "Valor da compra: ";
    if (!(std::cin >> valorCompra)) {
        std::cerr << "Entrada invalida.\n";
        return 1;
    }

    double desconto{valorCompra * TAXA_DESCONTO};
    double totalPagar{valorCompra - desconto};

    std::cout << std::fixed << std::setprecision(2);
    std::cout << "Valor: R$ " << valorCompra << '\n';
    std::cout << "Desconto: R$ " << desconto << '\n';
    std::cout << "Total: R$ " << totalPagar << '\n';

    return 0;
}