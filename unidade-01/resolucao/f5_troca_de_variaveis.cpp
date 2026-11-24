// Atividade F5 - Troca de variaveis

#include <iostream>
#include <utility>

int main() {
    int a{10};
    int b{20};

    // Por que o codigo abaixo nao troca os valores?
    // Na primeira linha (a = b), o valor original de 'a' (10) e sobrescrito pelo
    // valor de 'b' (20) e se perde. Quando 'b = a' e executado em seguida, 'a' ja
    // vale 20, entao ambas as variaveis terminam com 20.
    a = b;
    b = a;
    std::cout << "Versao com defeito: a=" << a << " b=" << b << '\n';

    // Correcao 1: com variavel auxiliar
    a = 10;
    b = 20;
    int auxiliar{a};
    a = b;
    b = auxiliar;
    std::cout << "Com variavel auxiliar: a=" << a << " b=" << b << '\n';

    // Correcao 2: com std::swap
    a = 10;
    b = 20;
    std::swap(a, b);
    std::cout << "Com std::swap: a=" << a << " b=" << b << '\n';

    return 0;
}