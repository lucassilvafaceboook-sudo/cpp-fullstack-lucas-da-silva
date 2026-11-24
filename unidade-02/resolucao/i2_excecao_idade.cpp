// Atividade I2 - Validando idade com excecoes

#include <iostream>
#include <stdexcept>

// Valida os limites de idade e lanca excecoes especificas em caso de erro
void validarIdade(int idade) {
    if (idade < 0) {
        throw std::invalid_argument("Idade negativa");
    }
    if (idade > 150) {
        throw std::out_of_range("Idade acima de 150");
    }
}

int main() {
    int idade{};

    // Trata erro de leitura (texto) diretamente, sem usar excecao
    std::cout << "Idade: ";
    if (!(std::cin >> idade)) {
        std::cerr << "Entrada invalida.\n";
        return 1;
    }

    try {
        validarIdade(idade);
        std::cout << "Idade valida: " << idade << '\n';
    } catch (const std::invalid_argument& erro) {
        std::cerr << "Erro: " << erro.what() << '\n';
        return 1;
    } catch (const std::out_of_range& erro) {
        std::cerr << "Erro: " << erro.what() << '\n';
        return 1;
    }

    return 0;
}