// Atividade D2 - Reescrevendo codigo sem desvios incondicionais

#include <iostream>

int main() {
    // ----- Parte 1: soma ate o zero -----
    int soma{0};
    int valor{};

    while (true) {
        std::cout << "Numero (0 para encerrar): ";
        if (!(std::cin >> valor) || valor == 0) {
            break;
        }
        soma += valor;
    }

    std::cout << "Soma: " << soma << '\n';

    // ----- Parte 2: par (a, b) com a*b == 42 e a+b == 13 -----
    int achadoA{0};
    int achadoB{0};
    bool achou{false};

    for (int a = 1; a <= 9 && !achou; ++a) {
        for (int b = 1; b <= 9; ++b) {
            if (a * b == 42 && a + b == 13) {
                achadoA = a;
                achadoB = b;
                achou = true;
                break;
            }
        }
    }

    if (achou) {
        std::cout << "Par encontrado: " << achadoA << " e " << achadoB << '\n';
    } else {
        std::cout << "Nenhum par encontrado\n";
    }

    // Comparacao entre as versoes:
    // Na parte 1, o while deixa imediatamente claro que o bloco se repete ate a
    // condicao de parada, sem precisar procurar rotulos pelo codigo.
    // Na parte 2, escapar de lacos aninhados e o caso em que o goto mais "tenta"
    // os programadores porque o break sozinho interrompe apenas o laco mais interno.
    // Ainda assim, usar uma flag booleana (achou) combinada com break mantem o
    // fluxo estruturado e mais seguro de manter.

    return 0;
}