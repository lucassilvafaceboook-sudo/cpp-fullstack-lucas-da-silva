// Atividade D1 - Calculadora de consumo
//
// TODO: escreva aqui o cabeçalho (objetivo, entradas, saídas, compilação)
#include <iomanip>
#include <iostream>
#include <string>

int main() {
    std::string produto;
    double precoUnitario{};
    int quantidade{};
    double descontoPercentual{};

    std::cout << "Produto: ";
    // TODO: leia o nome do produto (com espaços)

    std::cout << "Preco unitario: ";
    // TODO: leia e valide o preço (> 0)

    std::cout << "Quantidade: ";
    // TODO: leia e valide a quantidade (> 0)

    std::cout << "Desconto (%): ";
    // TODO: leia e valide o desconto (de 0 a 100)

    // TODO: calcule subtotal, valor do desconto e total
    // TODO: exiba o resumo alinhado, com duas casas decimais
    // TODO (comentário): registre três execuções de teste
    return 0;
}
