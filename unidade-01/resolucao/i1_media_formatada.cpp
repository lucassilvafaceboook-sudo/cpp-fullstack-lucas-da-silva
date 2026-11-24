// Atividade I1 - Media de notas com formatacao

#include <iomanip>
#include <iostream>
#include <string>

int main() {
    std::string nome;
    double nota1{};
    double nota2{};

    std::cout << "Nome completo: ";
    if (!std::getline(std::cin, nome) || nome.empty()) {
        std::cerr << "Entrada invalida.\n";
        return 1;
    }

    std::cout << "Nota 1 e nota 2: ";
    if (!(std::cin >> nota1 >> nota2)) {
        std::cerr << "Entrada invalida.\n";
        return 1;
    }

    double media{(nota1 + nota2) / 2.0};

    std::cout << "Aluno: " << nome << '\n';
    std::cout << std::fixed << std::setprecision(2);
    std::cout << "Media: " << media << '\n';

    // Efeito de std::fixed e std::setprecision(2):
    // std::fixed fixa a exibicao em notacao decimal padrao (evitando notacao cientifica)
    // e faz com que std::setprecision(2) controle exatamente a quantidade de casas apos
    // o ponto decimal (por exemplo, 7.50). Sem std::fixed, setprecision(2) limita o total
    // de digitos significativos do numero, exibindo 7.5 em vez de 7.50.

    return 0;
}