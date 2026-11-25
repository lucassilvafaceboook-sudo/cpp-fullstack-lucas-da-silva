// Atividade I1 - Array dinamico com new[] e depois std::vector
#include <iomanip>
#include <iostream>
#include <vector>

double mediaArray(const double* dados, int n) {
    double soma{0.0};
    for (int i = 0; i < n; ++i) {
        soma += dados[i];
    }
    return soma / n;
}

double mediaVetor(const std::vector<double>& dados) {
    double soma{0.0};
    for (double valor : dados) {
        soma += valor;
    }
    return soma / static_cast<double>(dados.size());
}

int main() {
    int n{};

    std::cout << "Quantidade (1 a 1000): ";
    if (!(std::cin >> n) || n < 1 || n > 1000) {
        std::cerr << "Entrada invalida.\n";
        return 1;
    }

    double* dados = new double[n];

    for (int i = 0; i < n; ++i) {
        std::cout << "Valor " << (i + 1) << ": ";
        if (!(std::cin >> dados[i])) {
            std::cerr << "Entrada invalida.\n";
            delete[] dados;
            dados = nullptr;
            return 1;
        }
    }

    std::cout << std::fixed << std::setprecision(2);
    std::cout << "Media (array dinamico): " << mediaArray(dados, n) << '\n';

    // Copia os valores para std::vector e libera o array dinamico
    std::vector<double> vetor;
    vetor.reserve(static_cast<std::size_t>(n));
    for (int i = 0; i < n; ++i) {
        vetor.push_back(dados[i]);
    }

    delete[] dados;
    dados = nullptr;

    std::cout << "Media (std::vector): " << mediaVetor(vetor) << '\n';
    return 0;
}