// Atividade F1 - Notas em um vector: sort e count_if
#include <algorithm>
#include <iostream>
#include <vector>

int main() {
    int n{};
    double limite{};
    std::vector<double> notas;

    std::cout << "Quantidade: ";
    if (!(std::cin >> n) || n < 1 || n > 50) {
        std::cerr << "Entrada invalida.\n";
        return 1;
    }

    notas.reserve(static_cast<std::size_t>(n));
    std::cout << "Notas: ";
    for (int i = 0; i < n; ++i) {
        double nota{};
        if (!(std::cin >> nota)) {
            std::cerr << "Entrada invalida.\n";
            return 1;
        }
        notas.push_back(nota);
    }

    std::cout << "Limite: ";
    if (!(std::cin >> limite)) {
        std::cerr << "Entrada invalida.\n";
        return 1;
    }

    std::sort(notas.begin(), notas.end());

    std::cout << "Ordenadas:";
    for (double nota : notas) {
        std::cout << ' ' << nota;
    }
    std::cout << '\n';

    auto acima = std::count_if(notas.begin(), notas.end(),
                               [limite](double nota) { return nota > limite; });

    std::cout << "Acima de " << limite << ": " << acima << '\n';
    return 0;
}