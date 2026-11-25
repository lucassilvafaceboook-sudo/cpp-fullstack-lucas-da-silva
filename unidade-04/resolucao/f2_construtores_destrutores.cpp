// Atividade F2 - Ordem de construtores e destrutores
#include <iostream>
#include <string>

class Rastro {
public:
    explicit Rastro(const std::string& nome) : nome_(nome) {
        std::cout << "Criando " << nome_ << '\n';
    }
    ~Rastro() {
        std::cout << "Destruindo " << nome_ << '\n';
    }

private:
    std::string nome_;
};

// Previsao antes de executar:
// Criando A, B, C -> "Dentro do bloco interno" -> Destruindo C -> "Dentro do bloco externo"
// -> Destruindo B -> Criando D -> "Antes do delete" -> Destruindo D -> Criando E, F
// -> "Fim de main" -> Destruindo F, E, A.
//
// Conclusao: objetos locais sao destruidos automaticamente ao fim do seu bloco na ordem
// inversa a da criacao (LIFO). Ja objetos alocados com new (como D) so sao destruidos
// no momento exato em que delete e chamado.

// O main ja esta pronto: nao precisa alterar.
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