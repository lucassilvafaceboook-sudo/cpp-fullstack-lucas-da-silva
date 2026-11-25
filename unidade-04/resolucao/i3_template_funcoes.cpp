// Atividade I3 - Templates de funcao: menor, somaArray e trocar
#include <iostream>
#include <string>

template <typename T>
T menor(T a, T b) {
    return (a < b) ? a : b;
}

template <typename T>
T somaArray(const T* dados, int n) {
    T soma{};
    for (int i = 0; i < n; ++i) {
        soma += dados[i];
    }
    return soma;
}

template <typename T>
void trocar(T& a, T& b) {
    T temp{a};
    a = b;
    b = temp;
}

// menor(3, 2.5) nao compila porque o template exige que ambos os argumentos tenham o
// mesmo tipo T; o compilador deduz int para 3 e double para 2.5, gerando conflito.
// Para corrigir, informe o tipo explicitamente: menor<double>(3, 2.5).

// O main ja esta pronto: nao precisa alterar.
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