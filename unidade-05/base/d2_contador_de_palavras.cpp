// Atividade D2 - Ranking de palavras de um texto
// O arquivo texto.txt está na mesma pasta deste arquivo.
#include <algorithm>
#include <cctype>
#include <fstream>
#include <iostream>
#include <map>
#include <string>
#include <utility>
#include <vector>

int main() {
    std::ifstream arquivo("texto.txt");
    // TODO: verifique a abertura ("Arquivo texto.txt nao encontrado" em cerr, return 1)

    std::map<std::string, int> contagem;
    int total{0};
    // TODO: leia palavra por palavra, normalize (minúsculas, só letras) e conte; ignore palavras vazias

    std::cout << "Total de palavras: " << total << '\n';
    std::cout << "Palavras distintas: " << contagem.size() << '\n';

    std::vector<std::pair<std::string, int>> ranking(contagem.begin(), contagem.end());
    // TODO: ordene com std::sort + lambda (frequência decrescente; empate por ordem alfabética)

    std::cout << "Top 3:\n";
    // TODO: mostre "1. palavra: N" para as 3 primeiras (ou menos, se houver menos palavras)

    // TODO: grave o ranking completo em ranking.txt (palavra frequencia, uma por linha), verificando
    //       abertura e escrita; mostre "Ranking gravado em ranking.txt (N linhas)"
    // TODO: leia a primeira linha de ranking.txt e mostre "Primeira linha do arquivo: ..."
    (void)ranking;
    return 0;
}
