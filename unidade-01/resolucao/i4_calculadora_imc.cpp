// Atividade I4 - Calculadora de IMC com validacao

#include <iomanip>
#include <iostream>

int main() {
    double peso{};
    double altura{};

    std::cout << "Peso (kg): ";
    if (!(std::cin >> peso) || peso <= 0.0) {
        std::cerr << "Entrada invalida.\n";
        return 1;
    }

    std::cout << "Altura (m): ";
    if (!(std::cin >> altura) || altura <= 0.0) {
        std::cerr << "Entrada invalida.\n";
        return 1;
    }

    double imc{peso / (altura * altura)};

    std::cout << std::fixed << std::setprecision(2);
    std::cout << "IMC: " << imc << '\n';

    return 0;
}

/*
Registros de teste:

1) Execucao normal:
   Entradas: Peso = 70, Altura = 1.75
   Saida: IMC: 22.86
   Codigo de saida: 0

2) Altura igual a zero:
   Entradas: Peso = 70, Altura = 0
   Saida (std::cerr): Entrada invalida.
   Codigo de saida: 1

3) Texto no lugar de numero:
   Entradas: Peso = "abc"
   Saida (std::cerr): Entrada invalida.
   Codigo de saida: 1
*/