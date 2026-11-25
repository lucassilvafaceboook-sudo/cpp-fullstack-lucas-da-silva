// Atividade D2 - Busca binaria recursiva e iterativa
#include <iostream>

bool estaOrdenado(const int* v, int n) {
    for (int i = 1; i < n; ++i) {
        if (v[i] < v[i - 1]) {
            return false;
        }
    }
    return true;
}

int buscaRecursiva(const int* v, int inicio, int fim, int alvo, int& passos) {
    if (inicio > fim) {
        return -1; // Caso-base: faixa vazia
    }
    int meio{inicio + (fim - inicio) / 2};
    ++passos;

    if (v[meio] == alvo) return meio;
    if (v[meio] < alvo) return buscaRecursiva(v, meio + 1, fim, alvo, passos);
    return buscaRecursiva(v, inicio, meio - 1, alvo, passos);
}

int buscaIterativa(const int* v, int n, int alvo, int& passos) {
    int inicio{0};
    int fim{n - 1};

    while (inicio <= fim) {
        int meio{inicio + (fim - inicio) / 2};
        ++passos;

        if (v[meio] == alvo) return meio;
        if (v[meio] < alvo) {
            inicio = meio + 1;
        } else {
            fim = meio - 1;
        }
    }
    return -1;
}

int main() {
    constexpr int CAPACIDADE{20};
    int v[CAPACIDADE]{};
    int n{};
    int alvo{};

    std::cout << "Quantidade: ";
    if (!(std::cin >> n) || n < 1 || n > CAPACIDADE) {
        std::cerr << "Entrada invalida.\n";
        return 1;
    }

    std::cout << "Valores (ordem crescente): ";
    for (int i = 0; i < n; ++i) {
        if (!(std::cin >> v[i])) {
            std::cerr << "Entrada invalida.\n";
            return 1;
        }
    }

    if (!estaOrdenado(v, n)) {
        std::cerr << "Valores fora de ordem crescente.\n";
        return 1;
    }

    std::cout << "Alvo: ";
    if (!(std::cin >> alvo)) {
        std::cerr << "Entrada invalida.\n";
        return 1;
    }

    int passosRec{0};
    int posRec{buscaRecursiva(v, 0, n - 1, alvo, passosRec)};

    int passosIte{0};
    int posIte{buscaIterativa(v, n, alvo, passosIte)};

    if (posRec != -1) {
        std::cout << "Recursiva: posicao " << posRec << " (" << passosRec << " passo(s))\n";
    } else {
        std::cout << "Recursiva: nao encontrado (" << passosRec << " passo(s))\n";
    }

    if (posIte != -1) {
        std::cout << "Iterativa: posicao " << posIte << " (" << passosIte << " passo(s))\n";
    } else {
        std::cout << "Iterativa: nao encontrado (" << passosIte << " passo(s))\n";
    }

    return 0;
}