// Atividade I1 - Calculadora com menu e switch

#include <iostream>

int main() {
    int opcao{};
    double a{};
    double b{};

    std::cout << "1 - Somar\n2 - Subtrair\n3 - Multiplicar\n4 - Dividir\n";
    std::cout << "Opcao: ";
    if (!(std::cin >> opcao)) {
        std::cerr << "Entrada invalida.\n";
        return 1;
    }

    std::cout << "Dois numeros: ";
    if (!(std::cin >> a >> b)) {
        std::cerr << "Entrada invalida.\n";
        return 1;
    }

    // Seleciona a operacao conforme a opcao informada
    switch (opcao) {
        case 1:
            std::cout << "Resultado: " << (a + b) << '\n';
            break;
        case 2:
            std::cout << "Resultado: " << (a - b) << '\n';
            break;
        case 3:
            std::cout << "Resultado: " << (a * b) << '\n';
            break;
        case 4:
            if (b == 0.0) {
                std::cout << "Divisao por zero\n";
            } else {
                std::cout << "Resultado: " << (a / b) << '\n';
            }
            break;
        default:
            std::cout << "Opcao invalida\n";
            break;
    }

    // O que acontece sem o break (fall-through):
    // Sem o break, apos executar o case correspondente, o programa continua
    // executando em sequencia todos os cases seguintes (e o default) ate
    // encontrar um break ou o fim do switch, gerando resultados errados.

    return 0;
}