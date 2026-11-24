// Atividade D2 - Nota fiscal alinhada
#include <iomanip>
#include <iostream>
#include <string>

int main() {
    // Dados dos itens (não altere)
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

    // TODO: calcule os subtotais, o subtotal geral, o imposto e o total
    // TODO: imprima a nota fiscal em formato de tabela alinhada
    std::cout << "NOTA FISCAL\n";
    return 0;
}
