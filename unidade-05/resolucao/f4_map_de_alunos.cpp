// Atividade F4 - Alunos por codigo em um std::map
#include <iostream>
#include <map>
#include <string>

int main() {
    std::map<int, std::string> alunos;
    alunos[3] = "Carla";
    alunos[1] = "Ana";
    alunos[2] = "Bruno";

    std::cout << "Alunos (ordem do map):\n";
    for (const auto& par : alunos) {
        std::cout << par.first << " - " << par.second << '\n';
    }

    int codigo{};
    std::cout << "Codigo a buscar: ";
    if (!(std::cin >> codigo)) {
        std::cerr << "Entrada invalida.\n";
        return 1;
    }

    auto it = alunos.find(codigo);
    if (it != alunos.end()) {
        std::cout << "Encontrado: " << it->second << '\n';
    } else {
        std::cout << "Codigo " << codigo << " nao encontrado\n";
    }

    std::cout << "Total de alunos: " << alunos.size() << '\n';
    return 0;
}