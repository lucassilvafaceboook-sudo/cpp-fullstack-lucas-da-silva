// Atividade F1 - Media e situacao do aluno
//
// Limites usados na classificacao:
//   - Aprovado:    media >= 6.0 (fronteira 6.0 -> Aprovado)
//   - Recuperacao: 4.0 <= media < 6.0 (fronteira 4.0 -> Recuperacao)
//   - Reprovado:   media < 4.0

#include <iomanip>
#include <iostream>

int main() {
    double nota1{};
    double nota2{};
    double nota3{};

    std::cout << "Tres notas: ";
    if (!(std::cin >> nota1 >> nota2 >> nota3)) {
        std::cerr << "Entrada invalida.\n";
        return 1;
    }

    double media{(nota1 + nota2 + nota3) / 3.0};

    std::cout << std::fixed << std::setprecision(2);
    std::cout << "Media: " << media << '\n';

    if (media >= 6.0) {
        std::cout << "Situacao: Aprovado\n";
    } else if (media >= 4.0) {
        std::cout << "Situacao: Recuperacao\n";
    } else {
        std::cout << "Situacao: Reprovado\n";
    }

    return 0;
}