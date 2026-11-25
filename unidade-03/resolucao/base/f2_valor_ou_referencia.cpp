// Atividade F2 - Trocar dois valores: por valor ou por referencia?
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
    int temp{a};
    a = b;
    b = temp;
    std::cout << "Dentro de trocarPorValor: a = " << a << ", b = " << b << '\n';
}

void trocarPorReferencia(int& a, int& b) {
    int temp{a};
    a = b;
    b = temp;
    std::cout << "Dentro de trocarPorReferencia: a = " << a << ", b = " << b << '\n';
}

// Na passagem por valor, a funcao recebe copias de x e y; a troca altera apenas
// essas copias locais. Na passagem por referencia (int&), a e b sao apelidos
// para as proprias variaveis x e y, modificando os valores originais.