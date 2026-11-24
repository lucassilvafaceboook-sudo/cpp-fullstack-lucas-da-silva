// Atividade F4 - Conversor de temperatura

#include <iostream>

int main() {
    double celsius{};
    std::cout << "Temperatura em Celsius: ";
    if (!(std::cin >> celsius)) {
        std::cerr << "Entrada invalida.\n";
        return 1;
    }

    double fahrenheit{celsius * (9.0 / 5.0) + 32.0};
    double kelvin{celsius + 273.15};

    std::cout << "Celsius: " << celsius << '\n';
    std::cout << "Fahrenheit: " << fahrenheit << '\n';
    std::cout << "Kelvin: " << kelvin << '\n';

    return 0;
}