// Atividade F5 - Troca de variáveis
#include <iostream>
#include <utility>

int main() {
    int a{10};
    int b{20};

    // TODO (comentário): por que o código abaixo não troca os valores?
    a = b;
    b = a;
    std::cout << "Versao com defeito: a=" << a << " b=" << b << '\n';

    // TODO: volte a e b para 10 e 20 e corrija com uma variável auxiliar
    // TODO: volte a e b para 10 e 20 e corrija com std::swap
    return 0;
}
