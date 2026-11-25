// Atividade I1 - map x unordered_map: contando palavras
#include <iostream>
#include <map>
#include <sstream>
#include <string>
#include <unordered_map>

int main() {
    std::string texto;
    std::map<std::string, int> ordenado;
    std::unordered_map<std::string, int> hash;

    std::cout << "Texto: ";
    if (!std::getline(std::cin, texto)) {
        std::cerr << "Entrada invalida.\n";
        return 1;
    }

    std::istringstream fluxo(texto);
    std::string palavra;
    while (fluxo >> palavra) {
        ++ordenado[palavra];
        ++hash[palavra];
    }

    std::cout << "map (ordem alfabetica):\n";
    for (const auto& par : ordenado) {
        std::cout << par.first << ": " << par.second << '\n';
    }
    std::cout << "unordered_map: " << hash.size() << " palavras distintas\n";

    std::string consulta;
    std::cout << "Palavra a consultar: ";
    if (!(std::cin >> consulta)) {
        std::cerr << "Entrada invalida.\n";
        return 1;
    }

    auto itMap = ordenado.find(consulta);
    auto itHash = hash.find(consulta);
    int qtdMap = (itMap != ordenado.end()) ? itMap->second : 0;
    int qtdHash = (itHash != hash.end()) ? itHash->second : 0;
    std::cout << "map: " << qtdMap << " | unordered_map: " << qtdHash << '\n';

    bool iguais = (ordenado.size() == hash.size());
    if (iguais) {
        for (const auto& par : ordenado) {
            auto it = hash.find(par.first);
            if (it == hash.end() || it->second != par.second) {
                iguais = false;
                break;
            }
        }
    }
    std::cout << "Contagens iguais nos dois: " << (iguais ? "sim" : "nao") << '\n';

    // std::map mantem as chaves sempre em ordem crescente (arvore balanceada).
    // std::unordered_map usa tabela hash: tem busca media mais rapida, mas nao
    // garante nenhuma ordem ao percorrer os elementos.
    return 0;
}