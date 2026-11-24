// Atividade I3 - Templates de função: menor, somaArray e trocar
#include <iostream>
#include <string>

// TODO: template <typename T> T menor(T a, T b)
template <typename T>
T menor(T a, T b) {
    (void)b;
    return a;
}

// TODO: template <typename T> T somaArray(const T* dados, int n)
template <typename T>
T somaArray(const T* dados, int n) {
    (void)dados;
    (void)n;
    return T{};
}

// TODO: template <typename T> void trocar(T& a, T& b)
template <typename T>
void trocar(T& a, T& b) {
    (void)a;
    (void)b;
}

// TODO (comentário): por que menor(3, 2.5) não compila e como corrigir?

// O main já está pronto: não precisa alterar.
int main() {
    std::cout << "menor(3, 8) = " << menor(3, 8) << '\n';
    std::cout << "menor(2.5, 1.5) = " << menor(2.5, 1.5) << '\n';
    std::cout << "menor(\"banana\", \"abacaxi\") = " << menor<std::string>("banana", "abacaxi") << '\n';

    int inteiros[]{1, 2, 3, 4};
    double reais[]{0.5, 1.5, 2.0};
    std::cout << "soma dos inteiros = " << somaArray(inteiros, 4) << '\n';
    std::cout << "soma dos reais = " << somaArray(reais, 3) << '\n';

    std::string x{"ola"};
    std::string y{"mundo"};
    std::cout << "antes: x=" << x << ", y=" << y << '\n';
    trocar(x, y);
    std::cout << "depois: x=" << x << ", y=" << y << '\n';
    return 0;
}
