// Atividade D3 - Jogo de adivinhação
#include <iostream>
#include <limits>
#include <random>

int main() {
    constexpr int MAX_TENTATIVAS{7};
    unsigned int semente{};

    std::cout << "Semente: ";
    // TODO: leia a semente e valide a leitura

    // Trecho pronto: sorteio reproduzível
    std::mt19937 gerador(semente);
    int segredo = static_cast<int>(gerador() % 100) + 1;

    // TODO: laço de até MAX_TENTATIVAS tentativas
    //   - ler palpite (tratar texto, fora de 1..100 e fim da entrada)
    //   - dicas "O numero e maior" / "O numero e menor"
    //   - acerto: "Acertou em N tentativa(s)!" e break
    // TODO: se perder, "Fim de jogo. O numero era X"
    (void)segredo;
    (void)MAX_TENTATIVAS;
    return 0;
}
