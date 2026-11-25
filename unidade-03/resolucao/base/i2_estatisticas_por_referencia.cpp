// Atividade I2 - Estatisticas devolvidas por referencia
#include <iomanip>
#include <iostream>
#include <vector>

void estatisticas(const std::vector<double>& valores, double& soma, double& menor, double& maior) {
    soma = 0.0;
    menor = valores[0];
    maior = valores[0];

    for (double v : valores) {
        soma += v;
        if (v < menor) menor = v;
        if (v > maior) maior = v;
    }
}

int main() {
    int n{};

    std::cout << "Quantidade: ";
    if (!(std::cin >> n) || n < 1 || n > 100) {
        std::cerr << "Entrada invalida.\n";
        return 1;
    }

    std::vector<double> valores;
    valores.reserve(static_cast<std::size_t>(n));

    std::cout << "Valores: ";
    for (int i = 0; i < n; ++i) {
        double v{};
        if (!(std::cin >> v)) {
            std::cerr << "Entrada invalida.\n";
            return 1;
        }
        valores.push_back(v);
    }

    double soma{0.0};
    double menor{0.0};
    double maior{0.0};
    estatisticas(valores, soma, menor, maior);

    double media{soma / n};

    std::cout << std::fixed << std::setprecision(2);
    std::cout << "Soma: " << soma << '\n';
    std::cout << "Menor: " << menor << '\n';
    std::cout << "Maior: " << maior << '\n';
    std::cout << "Media: " << media << '\n';
    return 0;
}