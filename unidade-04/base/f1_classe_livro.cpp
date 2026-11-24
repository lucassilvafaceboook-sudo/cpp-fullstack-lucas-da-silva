// Atividade F1 - Classe Livro: emprestar e devolver
#include <iostream>
#include <string>

class Livro {
public:
    Livro(const std::string& titulo, int total);
    bool emprestar();
    bool devolver();
    int disponiveis() const;
    const std::string& titulo() const;

private:
    std::string titulo_;
    int total_;
    int disponiveis_;
};

// TODO: implemente o construtor e os quatro métodos (os de consulta devem ser const)
Livro::Livro(const std::string& titulo, int total) : total_(0), disponiveis_(0) {
    (void)titulo;
    (void)total;
}
bool Livro::emprestar() { return false; }
bool Livro::devolver() { return false; }
int Livro::disponiveis() const { return 0; }
const std::string& Livro::titulo() const { return titulo_; }

// O main já está pronto: não precisa alterar.
int main() {
    Livro livro("Dom Casmurro", 2);
    std::cout << livro.titulo() << ": " << livro.disponiveis() << " disponivel(is)\n";
    for (int i = 1; i <= 3; ++i) {
        std::cout << "Emprestimo " << i << ": " << (livro.emprestar() ? "ok" : "sem exemplares") << '\n';
    }
    std::cout << livro.titulo() << ": " << livro.disponiveis() << " disponivel(is)\n";
    for (int i = 1; i <= 3; ++i) {
        std::cout << "Devolucao " << i << ": " << (livro.devolver() ? "ok" : "todos ja estao na biblioteca") << '\n';
    }
    std::cout << livro.titulo() << ": " << livro.disponiveis() << " disponivel(is)\n";
    return 0;
}
