// Atividade D5 - Pilha genérica e verificador de parênteses
#include <cstddef>
#include <iostream>
#include <stdexcept>
#include <string>

// TODO: template <typename T> class Pilha  (dados_, capacidade_, tamanho_; construtor com validação;
//       destrutor; cópia proibida; empilhar, desempilhar, topo, vazia, tamanho)
template <typename T>
class Pilha {
public:
    explicit Pilha(int capacidade) : dados_(nullptr), capacidade_(capacidade), tamanho_(0) {}
    ~Pilha() {}
    void empilhar(const T& valor) { (void)valor; }
    T desempilhar() { return T{}; }
    const T& topo() const {
        static T vazio{};
        return vazio;
    }
    bool vazia() const { return true; }
    int tamanho() const { return tamanho_; }

private:
    T* dados_;
    int capacidade_;
    int tamanho_;
};

// TODO: bool balanceada(const std::string& expressao)  - usa Pilha<char>
bool balanceada(const std::string& expressao) {
    (void)expressao;
    return false;
}

// O main já está pronto: não precisa alterar.
int main() {
    std::cout << "-- Pilha<int> --\n";
    try {
        Pilha<int> numeros(3);
        std::cout << "Empilhando 10 20 30\n";
        numeros.empilhar(10);
        numeros.empilhar(20);
        numeros.empilhar(30);
        try {
            numeros.empilhar(40);
        } catch (const std::runtime_error& erro) {
            std::cout << "Erro: " << erro.what() << '\n';
        }
        std::cout << "Desempilhando:";
        while (!numeros.vazia()) {
            std::cout << ' ' << numeros.desempilhar();
        }
        std::cout << '\n';
        try {
            numeros.desempilhar();
        } catch (const std::runtime_error& erro) {
            std::cout << "Erro: " << erro.what() << '\n';
        }

        std::cout << "-- Pilha<std::string> --\n";
        Pilha<std::string> palavras(2);
        palavras.empilhar("ola");
        palavras.empilhar("mundo");
        std::cout << "Topo: " << palavras.topo() << '\n';
    } catch (const std::exception& erro) {
        std::cerr << "Erro: " << erro.what() << '\n';
        return 1;
    }

    std::cout << "-- Balanceamento --\n";
    std::cout << "Expressao: ";
    std::string expressao;
    if (!std::getline(std::cin, expressao)) {
        std::cerr << "Entrada invalida.\n";
        return 1;
    }
    std::cout << (balanceada(expressao) ? "Balanceada" : "Desbalanceada") << '\n';
    return 0;
}
