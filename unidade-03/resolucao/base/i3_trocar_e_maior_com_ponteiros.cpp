// Atividade I3 - Funcoes que recebem e devolvem ponteiros
#include <iostream>

bool trocar(int* a, int* b) {
    if (a == nullptr || b == nullptr) {
        return false;
    }
    int temp{*a};
    *a = *b;
    *b = temp;
    return true;
}

// Faixa [inicio, fim): fim aponta uma posicao apos o ultimo elemento
int* maiorElemento(int* inicio, int* fim) {
    if (inicio == nullptr || fim == nullptr || inicio >= fim) {
        return nullptr;
    }
    int* maior{inicio};
    for (int* p = inicio + 1; p < fim; ++p) {
        if (*p > *maior) {
            maior = p;
        }
    }
    return maior;
}

int main() {
    constexpr int TAMANHO{6};
    int v[TAMANHO]{};

    std::cout << "Seis inteiros: ";
    for (int i = 0; i < TAMANHO; ++i) {
        if (!(std::cin >> v[i])) {
            std::cerr << "Entrada invalida.\n";
            return 1;
        }
    }

    int* maior{maiorElemento(v, v + TAMANHO)};
    std::cout << "Maior: " << *maior << " (posicao " << (maior - v) << ")\n";

    trocar(maior, &v[0]);
    std::cout << "Apos trocar com a primeira posicao:";
    for (int i = 0; i < TAMANHO; ++i) {
        std::cout << ' ' << v[i];
    }
    std::cout << '\n';

    bool trocouNulo{trocar(nullptr, &v[0])};
    std::cout << "Troca com ponteiro nulo: " << (trocouNulo ? "realizada" : "ignorada") << '\n';

    int* vazio{maiorElemento(v, v)};
    std::cout << "Elemento maximo de faixa vazia: " << (vazio == nullptr ? "nulo" : "nao nulo") << '\n';
    return 0;
}