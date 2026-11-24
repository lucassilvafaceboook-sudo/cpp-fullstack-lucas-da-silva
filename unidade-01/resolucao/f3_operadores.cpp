
// Atividade F3 - Operadores aritmeticos

#include <iostream>

int main() {
    int a{};
    int b{};

    std::cout << "Informe dois inteiros: ";
    if (!(std::cin >> a >> b)) {
        std::cerr << "Entrada invalida.\n";
        return 1;
    }

    std::cout << "Soma: " << (a + b) << '\n';
    std::cout << "Subtracao: " << (a - b) << '\n';
    std::cout << "Produto: " << (a * b) << '\n';

    if (b == 0) {
        std::cout << "Divisao por zero: operacao nao realizada\n";
    } else {
        std::cout << "Quociente (inteiro): " << (a / b) << '\n';
        std::cout << "Quociente (real): " << (static_cast<double>(a) / b) << '\n';
        std::cout << "Resto: " << (a % b) << '\n';
    }

    // Comparacao entre 7 / 2 e 7.0 / 2:
    // Em C++, 7 / 2 realiza divisao inteira (ambos os operandos sao int), descartando
    // a parte decimal e resultando em 3. Ja 7.0 / 2 envolve um double (7.0), o que
    // promove o 2 para double e realiza divisao real, resultando em 3.5.

    return 0;
}