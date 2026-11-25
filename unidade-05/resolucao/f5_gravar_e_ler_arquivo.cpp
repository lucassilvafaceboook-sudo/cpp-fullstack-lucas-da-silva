// Atividade F5 - Gravando e lendo um arquivo texto
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

int main() {
    int n{};
    std::vector<std::string> nomes;

    std::cout << "Quantidade: ";
    if (!(std::cin >> n) || n < 1 || n > 10) {
        std::cerr << "Entrada invalida.\n";
        return 1;
    }

    nomes.reserve(static_cast<std::size_t>(n));
    for (int i = 0; i < n; ++i) {
        std::string nome;
        std::cout << "Nome " << (i + 1) << ": ";
        if (!(std::cin >> nome)) {
            std::cerr << "Entrada invalida.\n";
            return 1;
        }
        nomes.push_back(nome);
    }

    // Bloco garante que o ofstream seja fechado antes de reabrir para leitura
    {
        std::ofstream saida("alunos.txt");
        if (!saida) {
            std::cerr << "Erro ao abrir alunos.txt para escrita.\n";
            return 1;
        }
        for (const std::string& nome : nomes) {
            saida << nome << '\n';
        }
        if (!saida) {
            std::cerr << "Erro ao gravar em alunos.txt.\n";
            return 1;
        }
    }
    std::cout << "Gravados " << n << " nome(s) em alunos.txt\n";

    std::cout << "Lidos do arquivo:\n";
    std::ifstream entrada("alunos.txt");
    if (!entrada) {
        std::cerr << "Erro ao abrir alunos.txt para leitura.\n";
        return 1;
    }
    std::string linha;
    int numero{1};
    while (std::getline(entrada, linha)) {
        std::cout << numero << ": " << linha << '\n';
        ++numero;
    }

    std::ifstream inexistente("inexistente.txt");
    if (!inexistente) {
        std::cout << "Arquivo inexistente.txt nao encontrado\n";
    }
    return 0;
}