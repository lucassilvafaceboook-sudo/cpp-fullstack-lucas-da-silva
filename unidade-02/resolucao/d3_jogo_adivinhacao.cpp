// Atividade D3 - Jogo de adivinhacao

#include <iostream>
#include <limits>
#include <random>

int main() {
    constexpr int MAX_TENTATIVAS{7};
    unsigned int semente{};

    std::cout << "Semente: ";
    if (!(std::cin >> semente)) {
        std::cerr << "Entrada invalida.\n";
        return 1;
    }

    // Trecho pronto: sorteio reproduzivel
    std::mt19937 gerador(semente);
    int segredo = static_cast<int>(gerador() % 100) + 1;

    int tentativas{0};
    bool acertou{false};

    while (tentativas < MAX_TENTATIVAS) {
        int palpite{};
        std::cout << "Palpite: ";

        if (!(std::cin >> palpite)) {
            if (std::cin.eof()) {
                return 1;
            }
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Palpite invalido\n";
            continue;
        }

        if (palpite < 1 || palpite > 100) {
            std::cout << "Palpite invalido\n";
            continue;
        }

        ++tentativas;

        if (palpite < segredo) {
            std::cout << "O numero e maior\n";
        } else if (palpite > segredo) {
            std::cout << "O numero e menor\n";
        } else {
            std::cout << "Acertou em " << tentativas << " tentativa(s)!\n";
            acertou = true;
            break;
        }
    }

    if (!acertou) {
        std::cout << "Fim de jogo. O numero era " << segredo << '\n';
    }

    return 0;
}