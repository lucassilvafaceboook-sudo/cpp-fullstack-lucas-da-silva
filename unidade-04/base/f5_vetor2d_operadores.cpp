// Atividade F5 - Sobrecarga de operadores: Vetor2D
#include <iostream>

// TODO: escreva a classe Vetor2D (x_ e y_ privados, construtor com valores padrão,
//       x(), y(), operator+, operator- e operator==, todos const)

void mostrar(const char* rotulo, double x, double y) {
    std::cout << rotulo << ": (" << x << ", " << y << ")\n";
}

int main() {
    double x1{};
    double y1{};
    double x2{};
    double y2{};

    std::cout << "Dois vetores (x1 y1 x2 y2): ";
    // TODO: leia x1 y1 x2 y2 e verifique a leitura

    // TODO: crie a e b, calcule a + b e a - b, e mostre com a função mostrar("Soma", ...) etc.
    // TODO: mostre "Iguais: sim" ou "Iguais: nao"
    (void)x1;
    (void)y1;
    (void)x2;
    (void)y2;
    return 0;
}
