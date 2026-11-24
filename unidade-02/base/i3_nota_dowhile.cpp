// Atividade I3 - Leitura de nota com do-while
#include <iostream>
#include <limits>

int main() {
    double nota{};
    int tentativas{0};

    // TODO: do { ... } while (...) pedindo "Nota (0 a 10): " até receber um valor válido
    //       - texto: clear() + ignore() e mensagem "Entrada invalida"
    //       - fora do intervalo: "Nota fora do intervalo (0 a 10)"
    //       - fim da entrada (std::cin.eof()): encerrar com código 1

    std::cout << "Nota registrada: " << nota << '\n';
    std::cout << "Tentativas: " << tentativas << '\n';
    return 0;
}
