// Atividade F2 - Trocar dois valores: por valor ou por referência?
#include <iostream>

void trocarPorValor(int a, int b);
void trocarPorReferencia(int& a, int& b);

int main() {
    int x{};
    int y{};

    std::cout << "Dois inteiros: ";
    if (!(std::cin >> x >> y)) {
        std::cerr << "Entrada invalida.\n";
        return 1;
    }

    std::cout << "Antes: x = " << x << ", y = " << y << '\n';
    trocarPorValor(x, y);
    std::cout << "Depois de trocarPorValor: x = " << x << ", y = " << y << '\n';
    trocarPorReferencia(x, y);
    std::cout << "Depois de trocarPorReferencia: x = " << x << ", y = " << y << '\n';
    return 0;
}

void trocarPorValor(int a, int b) {
    // TODO: troque a e b com uma variável temporária e mostre "Dentro de trocarPorValor: a = ..., b = ..."
}

void trocarPorReferencia(int& a, int& b) {
    // TODO: troque a e b com uma variável temporária e mostre "Dentro de trocarPorReferencia: a = ..., b = ..."
}

// TODO (comentário): por que trocarPorValor não altera x e y?
