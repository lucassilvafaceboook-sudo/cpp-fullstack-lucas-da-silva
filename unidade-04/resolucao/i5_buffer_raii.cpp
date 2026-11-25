// Atividade I5 - Buffer: uma classe que cuida da propria memoria (RAII)
#include <iostream>
#include <stdexcept>

class Buffer {
public:
    explicit Buffer(int tamanho);
    ~Buffer();
    Buffer(const Buffer&) = delete;
    Buffer& operator=(const Buffer&) = delete;
    int& operator[](int indice);
    int tamanho() const;

private:
    int* dados_;
    int tamanho_;
};

Buffer::Buffer(int tamanho) : dados_(nullptr), tamanho_(tamanho) {
    if (tamanho <= 0) {
        throw std::invalid_argument("Tamanho deve ser positivo");
    }
    dados_ = new int[tamanho_]{};
    std::cout << "Buffer criado (" << tamanho_ << " elementos)\n";
}

Buffer::~Buffer() {
    delete[] dados_;
    std::cout << "Buffer destruido\n";
}

int& Buffer::operator[](int indice) {
    if (indice < 0 || indice >= tamanho_) {
        throw std::out_of_range("Indice fora dos limites");
    }
    return dados_[indice];
}

int Buffer::tamanho() const { return tamanho_; }

// Quando operator[] lanca std::out_of_range, a execucao sai do bloco try e o C++
// realiza o desempilhamento da pilha (stack unwinding), chamando o destrutor de
// todos os objetos locais criados no bloco (como buffer) ANTES de entrar no catch.
// Por isso "Buffer destruido" aparece antes de "Erro:".

// O main ja esta pronto: nao precisa alterar.
int main() {
    int n{};

    std::cout << "Tamanho: ";
    if (!(std::cin >> n)) {
        std::cerr << "Entrada invalida.\n";
        return 1;
    }

    try {
        Buffer buffer(n);
        for (int i = 0; i < buffer.tamanho(); ++i) {
            buffer[i] = i * i;
        }
        std::cout << "Conteudo:";
        for (int i = 0; i < buffer.tamanho(); ++i) {
            std::cout << ' ' << buffer[i];
        }
        std::cout << '\n';
        std::cout << "Acessando indice " << n << "...\n";
        buffer[n] = 1;
        std::cout << "Nao deveria chegar aqui\n";
    } catch (const std::exception& erro) {
        std::cout << "Erro: " << erro.what() << '\n';
    }
    std::cout << "Fim\n";
    return 0;
}