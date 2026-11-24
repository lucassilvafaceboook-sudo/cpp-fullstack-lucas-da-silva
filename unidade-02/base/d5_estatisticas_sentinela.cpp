// Atividade D5 - Estatísticas com valor sentinela
#include <iomanip>
#include <iostream>
#include <limits>
#include <stdexcept>

int main() {
    int quantidade{0};
    double soma{0.0};
    double maior{0.0};
    double menor{0.0};

    try {
        // TODO: laço de leitura até o sentinela 0
        //   - texto: "Entrada invalida, ignorada" em cerr, clear(), ignore() e continue
        //   - atualizar quantidade, soma, maior e menor
        // TODO: se quantidade == 0, lance std::runtime_error("Nenhum valor informado")

        std::cout << std::fixed << std::setprecision(2);
        std::cout << "Quantidade: " << quantidade << '\n';
        // TODO: soma, média, maior e menor
    } catch (const std::runtime_error& erro) {
        std::cerr << "Erro: " << erro.what() << '\n';
        return 1;
    }
    (void)soma;
    (void)maior;
    (void)menor;
    return 0;
}
