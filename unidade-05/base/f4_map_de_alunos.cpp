// Atividade F4 - Alunos por código em um std::map
#include <iostream>
#include <map>
#include <string>

int main() {
    std::map<int, std::string> alunos;
    alunos[3] = "Carla";
    alunos[1] = "Ana";
    alunos[2] = "Bruno";

    std::cout << "Alunos (ordem do map):\n";
    // TODO: percorra o map e mostre "codigo - nome"

    int codigo{};
    std::cout << "Codigo a buscar: ";
    // TODO: leia o código e verifique a leitura

    // TODO: busque com find: "Encontrado: <nome>" ou "Codigo <N> nao encontrado"
    // TODO: mostre "Total de alunos: ..."
    (void)codigo;
    return 0;
}
