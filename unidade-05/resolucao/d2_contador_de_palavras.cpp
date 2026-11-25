// Atividade D2 - Ranking de palavras de um texto
// O arquivo texto.txt esta na mesma pasta deste arquivo.
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
    if (!arquivo) {
        std::cerr << "Arquivo texto.txt nao encontrado\n";
        return 1;
    }

    std::map<std::string, int> contagem;
    int total{0};
    std::string bruta;

    while (arquivo >> bruta) {
        std::string limpa;
        for (char c : bruta) {
            unsigned char uc = static_cast<unsigned char>(c);
            if (std::isalpha(uc)) {
                limpa.push_back(static_cast<char>(std::tolower(uc)));
            }
        }
        if (!limpa.empty()) {
            ++contagem[limpa];
            ++total;
        }
    }

    std::cout << "Total de palavras: " << total << '\n';
    std::cout << "Palavras distintas: " << contagem.size() << '\n';

    std::vector<std::pair<std::string, int>> ranking(contagem.begin(), contagem.end());
    std::sort(ranking.begin(), ranking.end(),
              [](const std::pair<std::string, int>& a, const std::pair<std::string, int>& b) {
                  return a.second != b.second ? a.second > b.second : a.first < b.first;
              });

    std::cout << "Top 3:\n";
    std::size_t limite = ranking.size() < 3 ? ranking.size() : 3;
    for (std::size_t i = 0; i < limite; ++i) {
        std::cout << (i + 1) << ". " << ranking[i].first << ": " << ranking[i].second << '\n';
    }

    {
        std::ofstream saida("ranking.txt");
        if (!saida) {
            std::cerr << "Erro ao abrir ranking.txt para escrita.\n";
            return 1;
        }
        for (const auto& par : ranking) {
            saida << par.first << ' ' << par.second << '\n';
        }
        if (!saida) {
            std::cerr << "Erro ao gravar ranking.txt.\n";
            return 1;
        }
    }
    std::cout << "Ranking gravado em ranking.txt (" << ranking.size() << " linhas)\n";

    std::ifstream leitura("ranking.txt");
    if (!leitura) {
        std::cerr << "Erro ao abrir ranking.txt para leitura.\n";
        return 1;
    }
    std::string primeiraLinha;
    if (std::getline(leitura, primeiraLinha)) {
        std::cout << "Primeira linha do arquivo: " << primeiraLinha << '\n';
    }
    return 0;
}