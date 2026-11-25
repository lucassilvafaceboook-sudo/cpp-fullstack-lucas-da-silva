// Atividade I3 - unique_ptr, shared_ptr e weak_ptr em acao
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
        auto u1 = std::make_unique<Recurso>("A");
        u1->usar();
        auto u2 = std::move(u1);
        std::cout << "u1 vazio: " << (!u1 ? "sim" : "nao") << '\n';
        u2->usar();
    }

    std::cout << "-- shared_ptr --\n";
    {
        auto s1 = std::make_shared<Recurso>("B");
        {
            auto s2 = s1;
            std::cout << "Contagem: " << s1.use_count() << '\n';
        }
        std::cout << "Contagem: " << s1.use_count() << '\n';
    }

    std::cout << "-- weak_ptr --\n";
    std::weak_ptr<Recurso> observador;
    {
        auto dono = std::make_shared<Recurso>("C");
        observador = dono;
        if (auto p = observador.lock()) {
            p->usar();
        }
        std::cout << "Expirou antes: " << (observador.expired() ? "sim" : "nao") << '\n';
    }
    std::cout << "Expirou depois: " << (observador.expired() ? "sim" : "nao") << '\n';

    // Quando usar cada um:
    // - unique_ptr: padrao quando existe apenas um dono exclusivo do recurso.
    // - shared_ptr: quando a posse do recurso precisa ser compartilhada entre varios donos.
    // - weak_ptr: quando se quer apenas observar um objeto gerenciado por shared_ptr
    //   sem manter posse (evitando ciclos de referencia).
    return 0;
}