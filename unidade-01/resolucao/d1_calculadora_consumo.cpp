// Atividade D1 - Calculadora de consumo
//
// Objetivo:
//   Ler os dados de uma compra (produto, preco unitario, quantidade e desconto),
//   validar cada entrada e exibir um resumo alinhado com duas casas decimais.
//
// Entradas:
//   - Nome do produto (texto com espacos)
//   - Preco unitario (double > 0)
//   - Quantidade (int > 0)
//   - Desconto percentual (double entre 0 e 100)
//
// Saidas:
//   - Resumo formatado com subtotal, valor do desconto e total final (ou erro em std::cerr)
//
// Compilacao:
//   g++ -std=c++17 -Wall -Wextra d1_calculadora_consumo.cpp -o d1.exe

#include <iomanip>
#include <iostream>
#include <string>

int main() {
    constexpr double DESCONTO_MIN{0.0};
    constexpr double DESCONTO_MAX{100.0};
    constexpr double DIVISOR_PERCENTUAL{100.0};

    std::string produto;
    double precoUnitario{};
    int quantidade{};
    double descontoPercentual{};

    std::cout << "Produto: ";
    if (!std::getline(std::cin, produto) || produto.empty()) {
        std::cerr << "Erro: nome do produto invalido.\n";
        return 1;
    }

    std::cout << "Preco unitario: ";
    if (!(std::cin >> precoUnitario)) {
        std::cerr << "Erro: falha na leitura do preco unitario.\n";
        return 1;
    }
    if (precoUnitario <= 0.0) {
        std::cerr << "Erro: o preco unitario deve ser maior que zero.\n";
        return 1;
    }

    std::cout << "Quantidade: ";
    if (!(std::cin >> quantidade)) {
        std::cerr << "Erro: falha na leitura da quantidade.\n";
        return 1;
    }
    if (quantidade <= 0) {
        std::cerr << "Erro: a quantidade deve ser maior que zero.\n";
        return 1;
    }

    std::cout << "Desconto (%): ";
    if (!(std::cin >> descontoPercentual)) {
        std::cerr << "Erro: falha na leitura do desconto.\n";
        return 1;
    }
    if (descontoPercentual < DESCONTO_MIN || descontoPercentual > DESCONTO_MAX) {
        std::cerr << "Erro: o desconto deve estar entre 0 e 100.\n";
        return 1;
    }

    double subtotal{precoUnitario * quantidade};
    double valorDesconto{subtotal * (descontoPercentual / DIVISOR_PERCENTUAL)};
    double total{subtotal - valorDesconto};

    std::cout << std::fixed << std::setprecision(2);
    std::cout << "\n===== RESUMO DA COMPRA =====\n";
    std::cout << std::left << std::setw(10) << "Produto"    << ": " << produto << "\n";
    std::cout << std::left << std::setw(10) << "Preco unit" << ": R$ " << precoUnitario << "\n";
    std::cout << std::left << std::setw(10) << "Quantidade" << ": " << quantidade << "\n";
    std::cout << std::left << std::setw(10) << "Subtotal"   << ": R$ " << subtotal << "\n";
    std::cout << std::left << std::setw(10) << "Desconto"   << ": " << descontoPercentual
              << "% (R$ " << valorDesconto << ")\n";
    std::cout << std::left << std::setw(10) << "Total"      << ": R$ " << total << "\n";

    return 0;
}

/*
Registros de teste:

1) Execucao normal:
   Entradas: "Caderno Espiral", 12.50, 4, 10
   Saida:
     ===== RESUMO DA COMPRA =====
     Produto   : Caderno Espiral
     Preco unit: R$ 12.50
     Quantidade: 4
     Subtotal  : R$ 50.00
     Desconto  : 10.00% (R$ 5.00)
     Total     : R$ 45.00
   Codigo de saida: 0

2) Preco invalido (<= 0):
   Entradas: "Caneta Azul", -5
   Saida (std::cerr): Erro: o preco unitario deve ser maior que zero.
   Codigo de saida: 1

3) Texto no lugar de numero:
   Entradas: "Mochila", "abc"
   Saida (std::cerr): Erro: falha na leitura do preco unitario.
   Codigo de saida: 1
*/