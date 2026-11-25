// Atividade I5 - Inverter um array com dois ponteiros
#include <iostream>

// Inverte a faixa [inicio, fim) usando apenas ponteiros (sem [])
void inverter(int* inicio, int* fim) {
    if (inicio >= fim) {
        return;
    }
    --fim; // Aponta para o ultimo elemento valido
    while (inicio < fim) {
        int temp{*inicio};
        *inicio = *fim;
        *fim = temp;
        ++inicio;
        --fim;
    }
}

void imprimir(const char* rotulo, const int* inicio, const int* fim) {
    std::cout << rotulo;
    for (const int* p = inicio; p < fim; ++p) {
        std::cout << ' ' << *p;
    }
    std::cout << '\n';
}

int main() {
    constexpr int CAPACIDADE{20};
    int v[CAPACIDADE]{};
    int n{};

    std::cout << "Quantidade: ";
    if (!(std::cin >> n) || n < 1 || n > CAPACIDADE) {
        std::cerr << "Entrada invalida.\n";
        return 1;
    }

    std::cout << "Valores: ";
    for (int i = 0; i < n; ++i) {
        if (!(std::cin >> v[i])) {
            std::cerr << "Entrada invalida.\n";
            return 1;
        }
    }

    imprimir("Original:", v, v + n);
    inverter(v, v + n);
    imprimir("Invertido:", v, v + n);
    return 0;
}