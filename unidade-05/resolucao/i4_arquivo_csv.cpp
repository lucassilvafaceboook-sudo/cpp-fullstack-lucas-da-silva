// Atividade I4 - Lendo um CSV com linhas invalidas
// O arquivo notas.csv esta na mesma pasta deste arquivo.
#include <fstream>
#include <iomanip>
#include <iostream>
#include <stdexcept>
#include <string>

int main() {
    std::ifstream arquivo("notas.csv");
    if (!arquivo) {
        std::cerr << "Arquivo notas.csv nao encontrado\n";
        return 1;
    }

    int validos{0};
    int invalidos{0};
    double soma{0.0};
    std::string melhorNome;
    double melhorNota{-1.0};

    std::string linha;
    int numeroLinha{0};
    while (std::getline(arquivo, linha)) {
        ++numeroLinha;
        if (numeroLinha == 1) {
            continue;  // Ignora o cabecalho
        }
        if (!linha.empty() && linha.back() == '\r') {
            linha.pop_back();
        }

        std::size_t pos = linha.find(';');
        if (pos == std::string::npos) {
            std::cout << "Linha " << numeroLinha << " invalida: sem separador\n";
            ++invalidos;
            continue;
        }

        std::string nome = linha.substr(0, pos);
        std::string notaTexto = linha.substr(pos + 1);

        if (nome.empty()) {
            std::cout << "Linha " << numeroLinha << " invalida: nome vazio\n";
            ++invalidos;
            continue;
        }

        double nota{0.0};
        try {
            std::size_t idx{0};
            nota = std::stod(notaTexto, &idx);
            if (idx != notaTexto.size()) {
                throw std::invalid_argument("caracteres extras");
            }
        } catch (const std::exception&) {
            std::cout << "Linha " << numeroLinha << " invalida: nota \"" << notaTexto << "\"\n";
            ++invalidos;
            continue;
        }

        if (nota < 0.0 || nota > 10.0) {
            std::cout << "Linha " << numeroLinha << " invalida: nota fora de 0 a 10\n";
            ++invalidos;
            continue;
        }

        ++validos;
        soma += nota;
        if (nota > melhorNota) {
            melhorNota = nota;
            melhorNome = nome;
        }
    }

    if (validos == 0) {
        std::cout << "Nenhum registro valido\n";
        return 1;
    }

    std::cout << "Registros validos: " << validos << '\n';
    std::cout << "Registros invalidos: " << invalidos << '\n';
    std::cout << std::fixed << std::setprecision(2);
    std::cout << "Media: " << (soma / validos) << '\n';
    std::cout << std::defaultfloat;
    std::cout << "Melhor: " << melhorNome << " (" << melhorNota << ")\n";
    return 0;
}