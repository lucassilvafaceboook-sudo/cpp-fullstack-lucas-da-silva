// Atividade F3 - Tabuada com for e com while

#include <iostream>

int main() {
    int numero{};

    std::cout << "Numero: ";
    if (!(std::cin >> numero)) {
        std::cerr << "Entrada invalida.\n";
        return 1;
    }

    std::cout << "Com for:\n";
    for (int i = 1; i <= 10; ++i) {
        std::cout << numero << " x " << i << " = " << (numero * i) << '\n';
    }

    std::cout << "Com while:\n";
    int i{1};
    while (i <= 10) {
        std::cout << numero << " x " << i << " = " << (numero * i) << '\n';
        ++i;
    }

    // Quando cada laco e mais natural:
    // O for e mais natural quando sabemos previamente a quantidade de repeticoes
    // (como de 1 a 10), pois concentra inicializacao, condicao e atualizacao em
    // uma unica linha. Ja o while e mais natural quando o numero de repeticoes
    // depende de uma condicao externa ou dinamica (como ler ate um valor sentinela).

    return 0;
}