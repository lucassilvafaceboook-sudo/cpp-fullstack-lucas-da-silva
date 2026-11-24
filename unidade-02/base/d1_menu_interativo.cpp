// Atividade D1 - Menu interativo de operações
//
// TODO: escreva aqui o cabeçalho (objetivo, entradas, saídas, compilação)
#include <iostream>
#include <limits>
#include <stdexcept>

// TODO: função dividir(double a, double b) que lança std::invalid_argument("divisao por zero")

int main() {
    int opcao{};

    // TODO: do { ... } while (opcao != 0);
    //   - mostrar o menu e ler a opção (tratar texto e fim da entrada)
    //   - switch (opcao) com as quatro operações, break em cada caso
    //   - opção inválida: "Opcao invalida" e continue
    //   - try/catch para a divisão por zero: "Erro: divisao por zero"
    // TODO (comentário): por que a solução fica melhor sem goto?
    std::cout << "Encerrando\n";
    (void)opcao;
    return 0;
}
