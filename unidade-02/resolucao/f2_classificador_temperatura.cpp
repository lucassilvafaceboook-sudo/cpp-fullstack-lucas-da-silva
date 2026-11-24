// Atividade F2 - Classificador de temperatura

#include <iostream>

int main() {
    double temperatura{};

    std::cout << "Temperatura em Celsius: ";
    if (!(std::cin >> temperatura)) {
        std::cerr << "Entrada invalida.\n";
        return 1;
    }

    std::cout << "Temperatura: " << temperatura << '\n';

    if (temperatura < 0.0) {
        std::cout << "Classificacao: Congelante\n";
    } else if (temperatura < 15.0) {
        std::cout << "Classificacao: Frio\n";
    } else if (temperatura < 25.0) {
        std::cout << "Classificacao: Agradavel\n";
    } else if (temperatura < 35.0) {
        std::cout << "Classificacao: Quente\n";
    } else {
        std::cout << "Classificacao: Muito quente\n";
    }

    return 0;
}