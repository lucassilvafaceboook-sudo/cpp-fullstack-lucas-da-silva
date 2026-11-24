// Atividade I5 - Buffer: uma classe que cuida da própria memória (RAII)
#include <iostream>
#include <stdexcept>

class Buffer {
public:
    explicit Buffer(int tamanho);
    ~Buffer();
    // TODO: proíba a cópia (construtor de cópia e operador de atribuição = delete)
    int& operator[](int indice);
    int tamanho() const;

private:
    int* dados_;
    int tamanho_;
};

// TODO: implemente construtor, destrutor, operator[] e tamanho()
Buffer::Buffer(int tamanho) : dados_(nullptr), tamanho_(tamanho) {}
Buffer::~Buffer() {}
int& Buffer::operator[](int indice) {
    (void)indice;
    static int vazio{0};
    return vazio;
}
int Buffer::tamanho() const { return tamanho_; }

// TODO (comentário): por que "Buffer destruido" aparece antes de "Erro:" ?

// O main já está pronto: não precisa alterar.
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
