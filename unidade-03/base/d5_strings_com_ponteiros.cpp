// Atividade D5 - Mini-biblioteca de strings C com ponteiros
#include <iostream>

// TODO: int tamanho(const char* s)
// TODO: void copiar(char* destino, const char* origem)
// TODO: int contarVogais(const char* s)
// TODO: void maiusculas(char* s)
// (use apenas ponteiros: sem [], sem <cstring>, sem std::string)

int main() {
    constexpr int CAPACIDADE{100};
    char texto[CAPACIDADE]{};
    char copia[CAPACIDADE]{};

    std::cout << "Texto: ";
    // TODO: std::cin.getline(texto, CAPACIDADE) e verifique a leitura

    // TODO: mostre "Tamanho: N" e "Vogais: N"
    // TODO: copie texto para copia, converta copia para maiúsculas
    // TODO: mostre "Copia em maiusculas: ..." e "Original preservado: ..."
    (void)texto;
    (void)copia;
    return 0;
}
