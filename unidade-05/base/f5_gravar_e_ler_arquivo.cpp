// Atividade F5 - Gravando e lendo um arquivo texto
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

int main() {
    int n{};
    std::vector<std::string> nomes;

    std::cout << "Quantidade: ";
    // TODO: leia n e valide (1 a 10)

    // TODO: leia os n nomes ("Nome 1: ", "Nome 2: ", ...) para o vetor

    // TODO: em um bloco { }, grave os nomes em alunos.txt (um por linha) com ofstream,
    //       verificando a abertura e a escrita; depois mostre "Gravados N nome(s) em alunos.txt"

    std::cout << "Lidos do arquivo:\n";
    // TODO: leia alunos.txt com ifstream + getline e mostre "1: Ana", "2: Bruno", ...

    // TODO: tente abrir inexistente.txt e mostre "Arquivo inexistente.txt nao encontrado"
    (void)n;
    return 0;
}
