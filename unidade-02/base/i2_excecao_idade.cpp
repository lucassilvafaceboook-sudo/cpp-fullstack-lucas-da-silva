// Atividade I2 - Validando idade com exceções
#include <iostream>
#include <stdexcept>

// TODO: implemente validarIdade(int idade)
//       negativa -> std::invalid_argument("Idade negativa")
//       maior que 150 -> std::out_of_range("Idade acima de 150")

int main() {
    int idade{};

    std::cout << "Idade: ";
    if (!(std::cin >> idade)) {
        std::cerr << "Entrada invalida.\n";
        return 1;
    }

    // TODO: chame validarIdade dentro de try, com dois catch separados
    std::cout << "Idade valida: " << idade << '\n';
    return 0;
}
