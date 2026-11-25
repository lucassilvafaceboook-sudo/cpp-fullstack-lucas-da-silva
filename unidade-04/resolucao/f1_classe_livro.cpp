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

Livro::Livro(const std::string& titulo, int total)
    : titulo_(titulo), total_(total > 0 ? total : 0), disponiveis_(total_) {}

bool Livro::emprestar() {
    if (disponiveis_ > 0) {
        --disponiveis_;
        return true;
    }
    return false;
}

bool Livro::devolver() {
    if (disponiveis_ < total_) {
        ++disponiveis_;
        return true;
    }
    return false;
}

int Livro::disponiveis() const { return disponiveis_; }
const std::string& Livro::titulo() const { return titulo_; }

// O main ja esta pronto: nao precisa alterar.
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