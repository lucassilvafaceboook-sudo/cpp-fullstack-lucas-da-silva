// Atividade I4 - Numeros primos ate N

#include <iostream>

int main() {
    int n{};

    std::cout << "N: ";
    if (!(std::cin >> n) || n < 2) {
        std::cerr << "Entrada invalida.\n";
        return 1;
    }

    int total{0};
    std::cout << "Primos:";

    // Testa cada numero de 2 ate n
    for (int num = 2; num <= n; ++num) {
        bool ehPrimo{true};

        // Verifica divisores apenas ate a raiz quadrada de num
        for (int d = 2; d * d <= num; ++d) {
            if (num % d == 0) {
                ehPrimo = false;
                break;
            }
        }

        if (ehPrimo) {
            std::cout << ' ' << num;
            ++total;
        }
    }

    std::cout << '\n';
    std::cout << "Total: " << total << " primos\n";
    return 0;
}