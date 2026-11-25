// Atividade F3 - Percorrendo um array por indice e por ponteiro
#include <iostream>

int main() {
    int numeros[6]{10, 20, 30, 40, 50, 60};
    int* ponteiro{numeros};

    std::cout << "Por indice:";
    for (int i = 0; i < 6; ++i) {
        std::cout << ' ' << numeros[i];
    }
    std::cout << '\n';

    std::cout << "Por ponteiro:";
    for (int i = 0; i < 6; ++i) {
        std::cout << ' ' << *(ponteiro + i);
    }
    std::cout << '\n';

    // Percorre de numeros ate a posicao logo apos o ultimo elemento (sem desreferenciar o fim)
    int soma{0};
    for (int* p = numeros; p < numeros + 6; ++p) {
        soma += *p;
    }
    std::cout << "Soma (ponteiro ate o fim): " << soma << '\n';

    *(ponteiro + 2) = 99;
    std::cout << "Apos *(ponteiro + 2) = 99, numeros[2] = " << numeros[2] << '\n';

    // Operador &: obtem o endereco de memoria de uma variavel.
    // Operador *: declara um ponteiro ou desreferencia (acessa o valor no endereco apontado).
    return 0;
}