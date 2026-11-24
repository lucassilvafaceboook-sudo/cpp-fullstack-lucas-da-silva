// Atividade D1 - Menu interativo de operacoes
//
// Objetivo:
//   Exibir um menu repetitivo com as quatro operacoes basicas usando do-while,
//   switch, continue e tratamento de excecao para divisao por zero.
//
// Entradas:
//   - Opcao do menu (0 a 4)
//   - Dois numeros reais (double) para as operacoes 1 a 4
//
// Saidas:
//   - Resultado da operacao, mensagem de erro (sem encerrar) ou "Encerrando"
//
// Compilacao:
//   g++ -std=c++17 -Wall -Wextra d1_menu_interativo.cpp -o d1.exe

#include <iostream>
#include <limits>
#include <stdexcept>

double dividir(double a, double b) {
    if (b == 0.0) {
        throw std::invalid_argument("divisao por zero");
    }
    return a / b;
}

int main() {
    int opcao{-1};

    do {
        std::cout << "===== MENU =====\n"
                  << "1 - Somar\n"
                  << "2 - Subtrair\n"
                  << "3 - Multiplicar\n"
                  << "4 - Dividir\n"
                  << "0 - Sair\n"
                  << "Opcao: ";

        if (!(std::cin >> opcao)) {
            if (std::cin.eof()) {
                return 1;
            }
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Opcao invalida\n";
            opcao = -1;
            continue;
        }

        if (opcao == 0) {
            break;
        }

        if (opcao < 1 || opcao > 4) {
            std::cout << "Opcao invalida\n";
            continue;
        }

        double a{};
        double b{};
        std::cout << "Dois numeros: ";
        if (!(std::cin >> a >> b)) {
            if (std::cin.eof()) {
                return 1;
            }
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Entrada invalida\n";
            continue;
        }

        switch (opcao) {
            case 1:
                std::cout << "Resultado: " << (a + b) << '\n';
                break;
            case 2:
                std::cout << "Resultado: " << (a - b) << '\n';
                break;
            case 3:
                std::cout << "Resultado: " << (a * b) << '\n';
                break;
            case 4:
                try {
                    std::cout << "Resultado: " << dividir(a, b) << '\n';
                } catch (const std::invalid_argument& erro) {
                    std::cerr << "Erro: " << erro.what() << '\n';
                }
                break;
            default:
                std::cout << "Opcao invalida\n";
                break;
        }
    } while (opcao != 0);

    // Por que a solucao fica mais clara sem goto:
    // Estruturas como do-while, switch, break e continue deixam o fluxo de execucao
    // previsivel e facil de ler de cima para baixo. O uso de goto cria saltos
    // arbitrarios que dificultam o rastreamento do estado das variaveis e a manutencao.

    std::cout << "Encerrando\n";
    return 0;
}