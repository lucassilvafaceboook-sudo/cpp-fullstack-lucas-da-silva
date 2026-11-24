// Atividade D4 - Caixa eletronico

#include <iostream>
#include <stdexcept>

int main() {
    constexpr int QUANTIDADE_NOTAS{5};
    constexpr int NOTAS[QUANTIDADE_NOTAS]{100, 50, 20, 10, 5};
    constexpr int LIMITE_SAQUE{5000};
    int valor{};

    std::cout << "Valor do saque: ";
    if (!(std::cin >> valor)) {
        std::cerr << "Entrada invalida.\n";
        return 1;
    }

    try {
        if (valor <= 0 || valor % 5 != 0) {
            throw std::invalid_argument("Valor deve ser multiplo de 5");
        }
        if (valor > LIMITE_SAQUE) {
            throw std::out_of_range("Limite de saque excedido");
        }

        int restante{valor};
        for (int i = 0; i < QUANTIDADE_NOTAS; ++i) {
            int nota{NOTAS[i]};
            int quantidade{restante / nota};
            if (quantidade == 0) {
                continue;
            }
            restante %= nota;
            std::cout << quantidade << " nota(s) de R$ " << nota << '\n';
        }
    } catch (const std::invalid_argument& erro) {
        std::cerr << "Erro: " << erro.what() << '\n';
        return 1;
    } catch (const std::out_of_range& erro) {
        std::cerr << "Erro: " << erro.what() << '\n';
        return 1;
    }

    return 0;
}