// Atividade D2 - Reescrevendo código com goto
// Reescreva as duas partes sem usar goto (veja o enunciado).
#include <iostream>

int main() {
    // ----- Parte 1: soma até o zero -----
    int soma{0};
    int valor{};

leitura:
    std::cout << "Numero (0 para encerrar): ";
    std::cin >> valor;
    if (valor == 0) {
        goto fim;
    }
    soma += valor;
    goto leitura;

fim:
    std::cout << "Soma: " << soma << '\n';

    // ----- Parte 2: par (a, b) com a*b == 42 e a+b == 13 -----
    int achadoA{0};
    int achadoB{0};
    for (int a = 1; a <= 9; ++a) {
        for (int b = 1; b <= 9; ++b) {
            if (a * b == 42 && a + b == 13) {
                achadoA = a;
                achadoB = b;
                goto encontrou;
            }
        }
    }
    std::cout << "Nenhum par encontrado\n";
    return 0;

encontrou:
    std::cout << "Par encontrado: " << achadoA << " e " << achadoB << '\n';
    return 0;
}
