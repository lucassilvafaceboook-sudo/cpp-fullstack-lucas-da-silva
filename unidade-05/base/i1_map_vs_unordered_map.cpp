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
    // TODO: leia a linha com std::getline e verifique a leitura

    // TODO: separe as palavras com std::istringstream e conte nos dois containers

    std::cout << "map (ordem alfabetica):\n";
    // TODO: percorra o map e mostre "palavra: N"
    // TODO: mostre "unordered_map: N palavras distintas"

    std::string consulta;
    std::cout << "Palavra a consultar: ";
    // TODO: leia a palavra; consulte os dois com find (ausente = 0); mostre "map: A | unordered_map: B"
    // TODO: compare todas as contagens e mostre "Contagens iguais nos dois: sim/nao"
    // TODO (comentário): diferença de ordenação entre map e unordered_map
    (void)consulta;
    return 0;
}
