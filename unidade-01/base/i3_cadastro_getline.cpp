// Atividade I3 - O bug do getline
#include <iostream>
#include <string>

int main() {
    int idade{};
    std::string nome;

    std::cout << "Idade: ";
    std::cin >> idade;

    std::cout << "Nome completo: ";
    std::getline(std::cin, nome);   // BUG: o nome sai vazio

    std::cout << "Aluno: " << nome << " (" << idade << " anos)\n";
    return 0;
}
