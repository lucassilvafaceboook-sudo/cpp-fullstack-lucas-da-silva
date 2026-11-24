// Atividade I1 - Array dinâmico com new[] e depois std::vector
#include <iomanip>
#include <iostream>
#include <vector>

// TODO: escreva mediaArray(const double* dados, int n)
// TODO: escreva mediaVetor(const std::vector<double>& dados)

int main() {
    int n{};

    std::cout << "Quantidade (1 a 1000): ";
    // TODO: leia n e valide (1 a 1000)

    // TODO: double* dados = new double[n];
    // TODO: leia os n valores ("Valor 1: ", "Valor 2: ", ...); em caso de erro, delete[] antes de sair

    std::cout << std::fixed << std::setprecision(2);
    // TODO: mostre "Media (array dinamico): ..."

    // TODO: copie os valores para um std::vector<double>
    // TODO: delete[] dados; dados = nullptr;
    // TODO: mostre "Media (std::vector): ..."
    (void)n;
    return 0;
}
