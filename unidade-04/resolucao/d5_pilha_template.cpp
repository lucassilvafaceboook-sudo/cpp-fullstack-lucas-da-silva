// Atividade D5 - Pilha generica e verificador de parenteses
#include <cstddef>
#include <iostream>
#include <stdexcept>
#include <string>

template <typename T>
class Pilha {
public:
    explicit Pilha(int capacidade) : dados_(nullptr), capacidade_(capacidade), tamanho_(0) {
        if (capacidade <= 0) {
            throw std::invalid_argument("Capacidade deve ser positiva");
        }
        dados_ = new T[capacidade_];
    }

    ~Pilha() {
        delete[] dados_;
    }

    Pilha(const Pilha&) = delete;
    Pilha& operator=(const Pilha&) = delete;

    void empilhar(const T& valor) {
        if (tamanho_ == capacidade_) {
            throw std::overflow_error("Pilha cheia");
        }
        dados_[tamanho_] = valor;
        ++tamanho_;
    }

    T desempilhar() {
        if (vazia()) {
            throw std::underflow_error("Pilha vazia");
        }
        --tamanho_;
        return dados_[tamanho_];
    }

    const T& topo() const {
        if (vazia()) {
            throw std::underflow_error("Pilha vazia");
        }
        return dados_[tamanho_ - 1];
    }

    bool vazia() const { return tamanho_ == 0; }
    int tamanho() const { return tamanho_; }

private:
    T* dados_;
    int capacidade_;
    int tamanho_;
};

bool balanceada(const std::string& expressao) {
    Pilha<char> pilha(static_cast<int>(expressao.size()) + 1);
    for (char c : expressao) {
        if (c == '(' || c == '[' || c == '{') {
            pilha.empilhar(c);
        } else if (c == ')' || c == ']' || c == '}') {
            if (pilha.vazia()) {
                return false;
            }
            char aberto = pilha.desempilhar();
            if ((c == ')' && aberto != '(') ||
                (c == ']' && aberto != '[') ||
                (c == '}' && aberto != '{')) {
                return false;
            }
        }
    }
    return pilha.vazia();
}

// O main ja esta pronto: nao precisa alterar.
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