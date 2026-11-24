// Atividade D4 - Caixa eletrônico
#include <iostream>
#include <stdexcept>

int main() {
    constexpr int QUANTIDADE_NOTAS{5};
    constexpr int NOTAS[QUANTIDADE_NOTAS]{100, 50, 20, 10, 5};
    int valor{};

    std::cout << "Valor do saque: ";
    if (!(std::cin >> valor)) {
        std::cerr << "Entrada invalida.\n";
        return 1;
    }

    try {
        // TODO: valide o valor (> 0, múltiplo de 5, <= 5000) lançando as exceções do enunciado
        // TODO: laço sobre NOTAS: quantidade = restante / nota; continue se for zero; mostre a linha
    } catch (const std::invalid_argument& erro) {
        std::cerr << "Erro: " << erro.what() << '\n';
        return 1;
    } catch (const std::out_of_range& erro) {
        std::cerr << "Erro: " << erro.what() << '\n';
        return 1;
    }
    (void)NOTAS;
    return 0;
}
