// Atividade F2 - Variaveis e tipos

#include <iostream>
#include <string>

int main() {
    std::string nome{"Lucas da Silva Macuxi"};
    int idade{27};
    double altura{1.75};
    bool matriculado{true};

    std::cout << "Nome: " << nome << '\n';
    std::cout << "Idade: " << idade << '\n';
    std::cout << "Altura: " << altura << '\n';
    std::cout << "Matriculado: " << std::boolalpha << matriculado << '\n';

    return 0;
}