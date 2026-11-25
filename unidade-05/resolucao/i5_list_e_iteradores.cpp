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
    if (!(std::cin >> n) || n < 1 || n > 30) {
        std::cerr << "Entrada invalida.\n";
        return 1;
    }

    std::cout << "Valores: ";
    for (int i = 0; i < n; ++i) {
        int valor{};
        if (!(std::cin >> valor)) {
            std::cerr << "Entrada invalida.\n";
            return 1;
        }
        lista.push_back(valor);
    }

    // Remove negativos usando o iterador devolvido por erase
    for (auto it = lista.begin(); it != lista.end();) {
        if (*it < 0) {
            it = lista.erase(it);
        } else {
            ++it;
        }
    }
    mostrar("Sem negativos:", lista);

    // Duplica cada par inserindo logo depois e avancando para a copia
    for (auto it = lista.begin(); it != lista.end(); ++it) {
        if (*it % 2 == 0) {
            it = lista.insert(std::next(it), *it);
        }
    }
    mostrar("Pares duplicados:", lista);

    lista.sort();
    lista.unique();
    mostrar("Ordenada sem repetidos:", lista);

    std::cout << "De tras para frente:";
    for (auto it = lista.rbegin(); it != lista.rend(); ++it) {
        std::cout << ' ' << *it;
    }
    std::cout << '\n';
    return 0;
}