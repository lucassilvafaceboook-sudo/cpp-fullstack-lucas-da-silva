// Atividade D3 - Matriz dinamica e sua transposta
#include <iomanip>
#include <iostream>

int** criarMatriz(int linhas, int colunas) {
    int** m = new int*[linhas];
    for (int i = 0; i < linhas; ++i) {
        m[i] = new int[colunas]{};
    }
    return m;
}

// Libera cada linha primeiro e depois o array de ponteiros
void liberarMatriz(int** m, int linhas) {
    for (int i = 0; i < linhas; ++i) {
        delete[] m[i];
    }
    delete[] m;
}

int** transpor(int** m, int linhas, int colunas) {
    int** t = criarMatriz(colunas, linhas);
    for (int i = 0; i < linhas; ++i) {
        for (int j = 0; j < colunas; ++j) {
            t[j][i] = m[i][j];
        }
    }
    return t;
}

void imprimir(int** m, int linhas, int colunas) {
    for (int i = 0; i < linhas; ++i) {
        for (int j = 0; j < colunas; ++j) {
            std::cout << std::setw(4) << m[i][j];
        }
        std::cout << '\n';
    }
}

int main() {
    int linhas{};
    int colunas{};

    std::cout << "Linhas (1 a 10): ";
    if (!(std::cin >> linhas) || linhas < 1 || linhas > 10) {
        std::cerr << "Entrada invalida.\n";
        return 1;
    }

    std::cout << "Colunas (1 a 10): ";
    if (!(std::cin >> colunas) || colunas < 1 || colunas > 10) {
        std::cerr << "Entrada invalida.\n";
        return 1;
    }

    int** matriz = criarMatriz(linhas, colunas);
    for (int i = 0; i < linhas; ++i) {
        for (int j = 0; j < colunas; ++j) {
            matriz[i][j] = i * colunas + j + 1;
        }
    }

    std::cout << "Matriz " << linhas << 'x' << colunas << ":\n";
    imprimir(matriz, linhas, colunas);

    int** transposta = transpor(matriz, linhas, colunas);
    std::cout << "Transposta " << colunas << 'x' << linhas << ":\n";
    imprimir(transposta, colunas, linhas);

    std::cout << "Soma por linha:";
    for (int i = 0; i < linhas; ++i) {
        int soma{0};
        for (int j = 0; j < colunas; ++j) {
            soma += matriz[i][j];
        }
        std::cout << ' ' << soma;
    }
    std::cout << '\n';

    liberarMatriz(matriz, linhas);
    liberarMatriz(transposta, colunas);
    return 0;
}