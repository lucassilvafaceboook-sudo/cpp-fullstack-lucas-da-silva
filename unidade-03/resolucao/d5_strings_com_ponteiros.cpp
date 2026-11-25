// Atividade D5 - Mini-biblioteca de strings C com ponteiros
#include <iostream>

int tamanho(const char* s) {
    const char* p{s};
    while (*p != '\0') {
        ++p;
    }
    return static_cast<int>(p - s);
}

void copiar(char* destino, const char* origem) {
    while (*origem != '\0') {
        *destino = *origem;
        ++destino;
        ++origem;
    }
    *destino = '\0'; // Copia o terminador nulo
}

int contarVogais(const char* s) {
    int total{0};
    for (const char* p = s; *p != '\0'; ++p) {
        char c{*p};
        if (c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u' ||
            c == 'A' || c == 'E' || c == 'I' || c == 'O' || c == 'U') {
            ++total;
        }
    }
    return total;
}

void maiusculas(char* s) {
    for (char* p = s; *p != '\0'; ++p) {
        if (*p >= 'a' && *p <= 'z') {
            *p = static_cast<char>(*p - ('a' - 'A'));
        }
    }
}

int main() {
    constexpr int CAPACIDADE{100};
    char texto[CAPACIDADE]{};
    char copia[CAPACIDADE]{};

    std::cout << "Texto: ";
    if (!std::cin.getline(texto, CAPACIDADE)) {
        std::cerr << "Entrada invalida.\n";
        return 1;
    }

    std::cout << "Tamanho: " << tamanho(texto) << '\n';
    std::cout << "Vogais: " << contarVogais(texto) << '\n';

    copiar(copia, texto);
    maiusculas(copia);

    std::cout << "Copia em maiusculas: " << copia << '\n';
    std::cout << "Original preservado: " << texto << '\n';
    return 0;
}