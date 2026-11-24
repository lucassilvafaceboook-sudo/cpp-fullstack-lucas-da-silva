// Atividade D2 - Busca binária recursiva e iterativa
#include <iostream>

// TODO: bool estaOrdenado(const int* v, int n)
// TODO: int buscaRecursiva(const int* v, int inicio, int fim, int alvo, int& passos)
// TODO: int buscaIterativa(const int* v, int n, int alvo, int& passos)

int main() {
    constexpr int CAPACIDADE{20};
    int v[CAPACIDADE]{};
    int n{};
    int alvo{};

    std::cout << "Quantidade: ";
    // TODO: leia n e valide (1 a 20)

    std::cout << "Valores (ordem crescente): ";
    // TODO: leia os valores e verifique se estão em ordem crescente (senão: mensagem em cerr e return 1)

    std::cout << "Alvo: ";
    // TODO: leia o alvo

    // TODO: execute as duas buscas e mostre:
    //   Recursiva: posicao P (N passo(s))      ou      Recursiva: nao encontrado (N passo(s))
    //   Iterativa: posicao P (N passo(s))      ou      Iterativa: nao encontrado (N passo(s))
    (void)v;
    (void)n;
    (void)alvo;
    return 0;
}
