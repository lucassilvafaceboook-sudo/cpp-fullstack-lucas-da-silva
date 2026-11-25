// Atividade F1 - Calculadora organizada em funcoes
#include <iostream>

// Prototipos das funcoes
double somar(double a, double b);
double subtrair(double a, double b);
double multiplicar(double a, double b);
double dividir(double a, double b);

int main() {
    double a{};
    double b{};

    std::cout << "Dois numeros: ";
    if (!(std::cin >> a >> b)) {
        std::cerr << "Entrada invalida.\n";
        return 1;
    }

    std::cout << "Soma: " << somar(a, b) << '\n';
    std::cout << "Subtracao: " << subtrair(a, b) << '\n';
    std::cout << "Multiplicacao: " << multiplicar(a, b) << '\n';

    if (b == 0.0) {
        std::cout << "Divisao: indefinida (divisor zero)\n";
    } else {
        std::cout << "Divisao: " << dividir(a, b) << '\n';
    }

    return 0;
}

double somar(double a, double b) { return a + b; }
double subtrair(double a, double b) { return a - b; }
double multiplicar(double a, double b) { return a * b; }
double dividir(double a, double b) { return a / b; }