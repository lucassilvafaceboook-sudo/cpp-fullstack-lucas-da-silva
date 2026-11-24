// Atividade F3 - Percorrendo um array por índice e por ponteiro
#include <iostream>

int main() {
    int numeros[6]{10, 20, 30, 40, 50, 60};
    int* ponteiro{numeros};

    std::cout << "Por indice:";
    // TODO: mostre os seis valores usando numeros[i]
    std::cout << '\n';

    std::cout << "Por ponteiro:";
    // TODO: mostre os seis valores usando *(ponteiro + i)
    std::cout << '\n';

    int soma{0};
    // TODO: some os valores com um ponteiro p que avança até numeros + 6
    std::cout << "Soma (ponteiro ate o fim): " << soma << '\n';

    // TODO: altere o terceiro elemento por ponteiro e mostre numeros[2]
    // TODO (comentário): o que significam & e * ?
    (void)ponteiro;
    return 0;
}
