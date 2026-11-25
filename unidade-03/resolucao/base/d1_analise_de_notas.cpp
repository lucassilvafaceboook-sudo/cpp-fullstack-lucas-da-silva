// Atividade D1 - Projeto da unidade: Analise de notas da turma
//
// Casos de teste:
// 1) Entrada: n = 5; notas = 7.5, 4, 9, 6, 10
//    Saida esperada (ambas versoes): Media: 7.30 | Maior nota: 10.00 | Aprovados: 4 | Reprovados: 1
// 2) Entrada: n = 3; notas = 5.5, 2.0, 4.5
//    Saida esperada (ambas versoes): Media: 4.00 | Maior nota: 5.50 | Aprovados: 0 | Reprovados: 3
// 3) Entrada: n = 2; notas = 8.0, 11.0
//    Saida esperada: Nota invalida (use 0 a 10). (encerra com codigo 1 liberando memoria)

#include <iomanip>
#include <iostream>
#include <vector>

constexpr int MAX_TURMA{50};

double calcularMedia(const double* notas, int quantidade);
double encontrarMaior(const double* notas, int quantidade);
void atualizarEstatistica(double nota, int& aprovados, int& reprovados);
void relatorio(const double* notas, int quantidade);

int main() {
    int n{};

    std::cout << "Tamanho da turma (1 a " << MAX_TURMA << "): ";
    if (!(std::cin >> n) || n < 1 || n > MAX_TURMA) {
        std::cerr << "Entrada invalida.\n";
        return 1;
    }

    double* notas = new double[n];

    for (int i = 0; i < n; ++i) {
        std::cout << "Nota " << (i + 1) << ": ";
        if (!(std::cin >> notas[i]) || notas[i] < 0.0 || notas[i] > 10.0) {
            std::cerr << "Nota invalida (use 0 a 10).\n";
            delete[] notas;
            notas = nullptr;
            return 1;
        }
    }

    std::cout << "--- Versao com array dinamico ---\n";
    relatorio(notas, n);

    // Copia para std::vector e libera o array dinamico
    std::vector<double> vetor;
    vetor.reserve(static_cast<std::size_t>(n));
    for (int i = 0; i < n; ++i) {
        vetor.push_back(notas[i]);
    }

    delete[] notas;
    notas = nullptr;

    std::cout << "--- Versao com std::vector ---\n";
    relatorio(vetor.data(), static_cast<int>(vetor.size()));

    return 0;
}

double calcularMedia(const double* notas, int quantidade) {
    double soma{0.0};
    for (const double* p = notas; p < notas + quantidade; ++p) {
        soma += *p;
    }
    return soma / quantidade;
}

double encontrarMaior(const double* notas, int quantidade) {
    double maior{*notas};
    for (const double* p = notas + 1; p < notas + quantidade; ++p) {
        if (*p > maior) {
            maior = *p;
        }
    }
    return maior;
}

void atualizarEstatistica(double nota, int& aprovados, int& reprovados) {
    if (nota >= 6.0) {
        ++aprovados;
    } else {
        ++reprovados;
    }
}

void relatorio(const double* notas, int quantidade) {
    int aprovados{0};
    int reprovados{0};

    for (const double* p = notas; p < notas + quantidade; ++p) {
        atualizarEstatistica(*p, aprovados, reprovados);
    }

    std::cout << std::fixed << std::setprecision(2);
    std::cout << "Media: " << calcularMedia(notas, quantidade) << '\n';
    std::cout << "Maior nota: " << encontrarMaior(notas, quantidade) << '\n';
    std::cout << "Aprovados: " << aprovados << '\n';
    std::cout << "Reprovados: " << reprovados << '\n';
}