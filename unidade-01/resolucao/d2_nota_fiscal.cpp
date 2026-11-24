// Atividade D2 - Nota fiscal alinhada

#include <iomanip>
#include <iostream>
#include <string>

int main() {
    // Dados dos itens (nao altere)
    std::string item1{"Caneta"};
    int quantidade1{10};
    double preco1{2.50};

    std::string item2{"Caderno"};
    int quantidade2{3};
    double preco2{12.90};

    std::string item3{"Mochila"};
    int quantidade3{1};
    double preco3{89.90};

    constexpr double TAXA_IMPOSTO{0.12};

    // Calculos
    double subtotal1{quantidade1 * preco1};
    double subtotal2{quantidade2 * preco2};
    double subtotal3{quantidade3 * preco3};

    double subtotalGeral{subtotal1 + subtotal2 + subtotal3};
    double imposto{subtotalGeral * TAXA_IMPOSTO};
    double total{subtotalGeral + imposto};

    // Larguras das colunas (total = 43 caracteres)
    constexpr int LARGURA_TOTAL{43};
    constexpr int LARGURA_ITEM{14};
    constexpr int LARGURA_QTD{7};
    constexpr int LARGURA_PRECO{10};
    constexpr int LARGURA_SUBTOTAL{12};

    std::cout << std::fixed << std::setprecision(2);

    std::cout << "=============== NOTA FISCAL ===============\n";
    std::cout << std::left  << std::setw(LARGURA_ITEM)     << "Item"
              << std::right << std::setw(LARGURA_QTD)      << "Qtd"
              << std::right << std::setw(LARGURA_PRECO)    << "Preco"
              << std::right << std::setw(LARGURA_SUBTOTAL) << "Subtotal" << "\n";

    std::cout << std::left  << std::setw(LARGURA_ITEM)     << item1
              << std::right << std::setw(LARGURA_QTD)      << quantidade1
              << std::right << std::setw(LARGURA_PRECO)    << preco1
              << std::right << std::setw(LARGURA_SUBTOTAL) << subtotal1 << "\n";

    std::cout << std::left  << std::setw(LARGURA_ITEM)     << item2
              << std::right << std::setw(LARGURA_QTD)      << quantidade2
              << std::right << std::setw(LARGURA_PRECO)    << preco2
              << std::right << std::setw(LARGURA_SUBTOTAL) << subtotal2 << "\n";

    std::cout << std::left  << std::setw(LARGURA_ITEM)     << item3
              << std::right << std::setw(LARGURA_QTD)      << quantidade3
              << std::right << std::setw(LARGURA_PRECO)    << preco3
              << std::right << std::setw(LARGURA_SUBTOTAL) << subtotal3 << "\n";

    std::cout << std::string(LARGURA_TOTAL, '-') << "\n";

    std::cout << std::left  << std::setw(20) << "Subtotal"
              << std::right << std::setw(23) << subtotalGeral << "\n";

    std::cout << std::left  << std::setw(20) << "Imposto (12%)"
              << std::right << std::setw(23) << imposto << "\n";

    std::cout << std::left  << std::setw(20) << "Total"
              << std::right << std::setw(23) << total << "\n";

    return 0;
}