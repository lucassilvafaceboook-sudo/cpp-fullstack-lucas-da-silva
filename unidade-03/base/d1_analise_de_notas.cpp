// Atividade D1 - Projeto da unidade: Análise de notas da turma
//
// TODO: documente aqui três casos de teste (entrada e saída esperada)
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
    // TODO: leia n e valide (1 a MAX_TURMA)

    // TODO: double* notas = new double[n]; leia as notas ("Nota 1: ", ...) validando 0 a 10
    //       (em caso de erro: mensagem em cerr, delete[] e return 1)

    std::cout << "--- Versao com array dinamico ---\n";
    // TODO: relatorio(notas, n);

    // TODO: copie as notas para um std::vector<double>, delete[] notas e notas = nullptr

    std::cout << "--- Versao com std::vector ---\n";
    // TODO: relatorio(vetor.data(), static_cast<int>(vetor.size()));
    (void)n;
    return 0;
}

// TODO: defina calcularMedia, encontrarMaior (com ponteiros), atualizarEstatistica e relatorio
