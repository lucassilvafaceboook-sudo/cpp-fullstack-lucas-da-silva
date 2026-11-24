// Atividade I4 - Lendo um CSV com linhas inválidas
// O arquivo notas.csv está na mesma pasta deste arquivo.
#include <fstream>
#include <iomanip>
#include <iostream>
#include <string>

int main() {
    std::ifstream arquivo("notas.csv");
    // TODO: verifique a abertura ("Arquivo notas.csv nao encontrado" em cerr, return 1)

    int validos{0};
    int invalidos{0};
    double soma{0.0};
    std::string melhorNome;
    double melhorNota{-1.0};

    std::string linha;
    int numeroLinha{0};
    // TODO: while (std::getline(arquivo, linha)) { ++numeroLinha; ... }
    //   - ignore a linha 1 (cabeçalho); remova um '\r' do fim
    //   - find(';') / substr para separar nome e nota; valide cada caso do enunciado
    //   - atualize validos, invalidos, soma e o melhor aluno

    // TODO: se validos == 0: "Nenhum registro valido" e return 1
    std::cout << "Registros validos: " << validos << '\n';
    std::cout << "Registros invalidos: " << invalidos << '\n';
    std::cout << std::fixed << std::setprecision(2);
    // TODO: mostre "Media: ..." e "Melhor: nome (nota)"
    (void)soma;
    (void)melhorNome;
    (void)melhorNota;
    return 0;
}
