// Atividade F2 - Ordem de construtores e destrutores
#include <iostream>
#include <string>

class Rastro {
public:
    explicit Rastro(const std::string& nome) : nome_(nome) {
        // TODO: mostre "Criando <nome>"
    }
    ~Rastro() {
        // TODO: mostre "Destruindo <nome>"
    }

private:
    std::string nome_;
};

// TODO (comentário): escreva aqui a ordem que você PREVÊ, antes de executar.

// O main já está pronto: não precisa alterar.
int main() {
    Rastro a("A");
    {
        Rastro b("B");
        {
            Rastro c("C");
            std::cout << "Dentro do bloco interno\n";
        }
        std::cout << "Dentro do bloco externo\n";
    }
    Rastro* d = new Rastro("D");
    std::cout << "Antes do delete\n";
    delete d;
    Rastro e("E");
    Rastro f("F");
    std::cout << "Fim de main\n";
    return 0;
}
