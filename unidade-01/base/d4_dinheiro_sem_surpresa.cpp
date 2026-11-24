// Atividade D4 - Dinheiro sem surpresa
#include <iomanip>
#include <iostream>

int main() {
    // Parte 1: o problema do double
    double a{0.1};
    double b{0.2};
    // TODO: mostre se (a + b == 0.3) e imprima a + b com 17 dígitos

    // Parte 2: dinheiro em centavos
    long long precoA{1990};   // R$ 19,90
    long long precoB{510};    // R$ 5,10
    long long precoC{10};     // R$ 0,10
    // TODO: some os três e imprima o total como "R$ 25,10"
    // TODO: calcule 15% de desconto com aritmética inteira (meio centavo arredonda para cima)
    // TODO (comentário): por que não guardar dinheiro em double?

    std::cout << a + b << '\n';
    (void)precoA;
    (void)precoB;
    (void)precoC;
    return 0;
}
