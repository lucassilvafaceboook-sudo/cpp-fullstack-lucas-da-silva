// Atividade I3 - Leitura de nota com do-while

#include <iostream>
#include <limits>

int main() {
    double nota{};
    int tentativas{0};
    bool valida{false};

    // Repete a leitura ate receber um numero valido no intervalo [0, 10]
    do {
        std::cout << "Nota (0 a 10): ";
        ++tentativas;

        if (!(std::cin >> nota)) {
            if (std::cin.eof()) {
                return 1;
            }
            // Limpa o estado de erro e descarta o texto restante no buffer
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Entrada invalida\n";
            continue;
        }

        if (nota < 0.0 || nota > 10.0) {
            std::cout << "Nota fora do intervalo (0 a 10)\n";
        } else {
            valida = true;
        }
    } while (!valida);

    std::cout << "Nota registrada: " << nota << '\n';
    std::cout << "Tentativas: " << tentativas << '\n';
    return 0;
}