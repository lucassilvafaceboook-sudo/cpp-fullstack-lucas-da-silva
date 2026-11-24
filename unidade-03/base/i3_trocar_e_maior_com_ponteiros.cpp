// Atividade I3 - Funções que recebem e devolvem ponteiros
#include <iostream>

// TODO: bool trocar(int* a, int* b)  - devolve false se algum ponteiro for nullptr
// TODO: int* maiorElemento(int* inicio, int* fim)  - faixa [inicio, fim); nullptr se vazia

int main() {
    constexpr int TAMANHO{6};
    int v[TAMANHO]{};

    std::cout << "Seis inteiros: ";
    // TODO: leia os seis inteiros e verifique a leitura

    // TODO: ache o maior com maiorElemento(v, v + TAMANHO) e mostre "Maior: X (posicao P)"
    // TODO: troque o maior com v[0] e mostre "Apos trocar com a primeira posicao: ..."
    // TODO: mostre "Troca com ponteiro nulo: ignorada" (ou realizada) ao testar trocar(nullptr, &v[0])
    // TODO: mostre "Elemento maximo de faixa vazia: nulo" ao testar maiorElemento(v, v)
    (void)v;
    return 0;
}
