// Atividade I3 - unique_ptr, shared_ptr e weak_ptr em ação
#include <iostream>
#include <memory>
#include <string>
#include <utility>

class Recurso {
public:
    explicit Recurso(const std::string& nome) : nome_(nome) { std::cout << "Criando " << nome_ << '\n'; }
    ~Recurso() { std::cout << "Destruindo " << nome_ << '\n'; }
    void usar() const { std::cout << "Usando " << nome_ << '\n'; }

private:
    std::string nome_;
};

int main() {
    std::cout << "-- unique_ptr --\n";
    {
        // TODO: u1 = make_unique<Recurso>("A"); usar(); u2 = std::move(u1); "u1 vazio: sim/nao"; u2->usar();
    }

    std::cout << "-- shared_ptr --\n";
    {
        // TODO: s1 = make_shared<Recurso>("B"); bloco interno com s2 = s1; "Contagem: N" dentro e depois
    }

    std::cout << "-- weak_ptr --\n";
    std::weak_ptr<Recurso> observador;
    {
        // TODO: dono = make_shared<Recurso>("C"); observador = dono; lock() + usar(); "Expirou antes: ..."
    }
    // TODO: mostre "Expirou depois: ..."

    // TODO (comentário): quando usar unique_ptr, shared_ptr e weak_ptr?
    return 0;
}
