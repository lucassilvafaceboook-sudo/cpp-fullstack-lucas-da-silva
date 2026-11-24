// Atividade I5 - std::list e iteradores: remover, inserir e ordenar
#include <iostream>
#include <iterator>
#include <list>

void mostrar(const char* rotulo, const std::list<int>& lista) {
    std::cout << rotulo;
    for (auto it = lista.begin(); it != lista.end(); ++it) {
        std::cout << ' ' << *it;
    }
    std::cout << '\n';
}

int main() {
    int n{};
    std::list<int> lista;

    std::cout << "Quantidade: ";
    // TODO: leia n e valide (1 a 30)

    std::cout << "Valores: ";
    // TODO: leia os n valores para a lista (push_back) e valide as leituras

    // TODO: remova os negativos com iterador e erase; mostrar("Sem negativos:", lista);
    // TODO: duplique cada par com insert; mostrar("Pares duplicados:", lista);
    // TODO: lista.sort(); lista.unique(); mostrar("Ordenada sem repetidos:", lista);
    // TODO: mostre "De tras para frente:" percorrendo com rbegin()/rend()
    (void)n;
    (void)lista;
    return 0;
}
