// Atividade I2 - Estatísticas devolvidas por referência
#include <iomanip>
#include <iostream>
#include <vector>

// TODO: escreva void estatisticas(const std::vector<double>& valores, double& soma, double& menor, double& maior)

int main() {
    int n{};

    std::cout << "Quantidade: ";
    // TODO: leia n e valide (1 a 100)

    std::vector<double> valores;
    std::cout << "Valores: ";
    // TODO: leia os n valores para o vetor (push_back) e valide as leituras

    double soma{0.0};
    double menor{0.0};
    double maior{0.0};
    // TODO: chame estatisticas(valores, soma, menor, maior)

    std::cout << std::fixed << std::setprecision(2);
    // TODO: mostre Soma, Menor, Maior e Media (a média é calculada aqui)
    (void)soma;
    (void)menor;
    (void)maior;
    (void)n;
    return 0;
}
