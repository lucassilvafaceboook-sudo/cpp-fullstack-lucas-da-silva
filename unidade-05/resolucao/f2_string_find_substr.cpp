// Atividade F2 - Separando o nome: find e substr
#include <iostream>
#include <string>

int main() {
    std::string nome;

    std::cout << "Nome completo: ";
    if (!std::getline(std::cin, nome) || nome.empty()) {
        std::cerr << "Entrada invalida.\n";
        return 1;
    }

    std::cout << "Tamanho: " << nome.size() << '\n';

    std::size_t posEspaco = nome.find(' ');
    if (posEspaco == std::string::npos) {
        std::cout << "Primeiro nome: " << nome << '\n';
        std::cout << "Resto do nome: (nao informado)\n";
    } else {
        std::cout << "Primeiro nome: " << nome.substr(0, posEspaco) << '\n';
        std::cout << "Resto do nome: " << nome.substr(posEspaco + 1) << '\n';
    }

    bool temSilva = (nome.find("Silva") != std::string::npos);
    std::cout << "Contem \"Silva\": " << (temSilva ? "sim" : "nao") << '\n';
    return 0;
}