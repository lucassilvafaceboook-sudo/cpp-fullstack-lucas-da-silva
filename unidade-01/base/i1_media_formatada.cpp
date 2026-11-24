// Atividade I1 - Média de notas com formatação
#include <iomanip>
#include <iostream>
#include <string>

int main() {
    std::string nome;
    double nota1{};
    double nota2{};

    std::cout << "Nome completo: ";
    // TODO: leia o nome completo com std::getline

    std::cout << "Nota 1 e nota 2: ";
    // TODO: leia as duas notas e verifique a leitura

    // TODO: calcule a média

    std::cout << "Aluno: " << nome << '\n';
    // TODO: formate com duas casas decimais e exiba "Media: ..."
    // TODO (comentário): explique o efeito de std::fixed e de std::setprecision(2)
    return 0;
}
