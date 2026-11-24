// Atividade D5 - Estatisticas com valor sentinela

#include <iomanip>
#include <iostream>
#include <limits>
#include <stdexcept>

int main() {
    int quantidade{0};
    double soma{0.0};
    double maior{0.0};
    double menor{0.0};

    try {
        while (true) {
            double valor{};
            std::cout << "Valor (0 para encerrar): ";

            if (!(std::cin >> valor)) {
                if (std::cin.eof()) {
                    break;
                }
                std::cerr << "Entrada invalida, ignorada\n";
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                continue;
            }

            if (valor == 0.0) {
                break;
            }

            if (quantidade == 0) {
                maior = valor;
                menor = valor;
            } else {
                if (valor > maior) {
                    maior = valor;
                }
                if (valor < menor) {
                    menor = valor;
                }
            }

            soma += valor;
            ++quantidade;
        }

        if (quantidade == 0) {
            throw std::runtime_error("Nenhum valor informado");
        }

        double media{soma / quantidade};

        std::cout << std::fixed << std::setprecision(2);
        std::cout << "Quantidade: " << quantidade << '\n';
        std::cout << "Soma: " << soma << '\n';
        std::cout << "Media: " << media << '\n';
        std::cout << "Maior: " << maior << '\n';
        std::cout << "Menor: " << menor << '\n';
    } catch (const std::runtime_error& erro) {
        std::cerr << "Erro: " << erro.what() << '\n';
        return 1;
    }

    return 0;
}