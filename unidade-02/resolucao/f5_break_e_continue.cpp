// Atividade F5 - break e continue

#include <iostream>

int main() {
    for (int i = 1; i <= 20; ++i) {
        if (i == 17) {
            break;
        }
        if (i % 3 == 0) {
            continue;
        }
        std::cout << i << ' ';
    }
    std::cout << '\n';

    // Diferenca entre break e continue:
    // O continue interrompe apenas a iteracao atual, pulando o restante do corpo
    // do laco e indo diretamente para a proxima volta. Ja o break encerra o laco
    // por completo, passando a execucao para a primeira instrucao apos o laco.

    return 0;
}