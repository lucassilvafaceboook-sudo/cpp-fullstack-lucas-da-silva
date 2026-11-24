// Atividade D2 - Herança múltipla e o problema do diamante
#include <iostream>
#include <string>

// TODO: class Pessoa (nome_ privado; construtor e destrutor com mensagens; nome() const)
class Pessoa {
public:
    explicit Pessoa(const std::string& nome) : nome_(nome) {}
    const std::string& nome() const { return nome_; }

private:
    std::string nome_;
};

// TODO: class Estudante : virtual public Pessoa (curso_; construtor, destrutor e curso() const)
class Estudante : public Pessoa {
public:
    Estudante(const std::string& nome, const std::string& curso) : Pessoa(nome), curso_(curso) {}
    const std::string& curso() const { return curso_; }

private:
    std::string curso_;
};

// TODO: class Trabalhador : virtual public Pessoa (empresa_; construtor, destrutor e empresa() const)
class Trabalhador : public Pessoa {
public:
    Trabalhador(const std::string& nome, const std::string& empresa) : Pessoa(nome), empresa_(empresa) {}
    const std::string& empresa() const { return empresa_; }

private:
    std::string empresa_;
};

// TODO: class EstudanteTrabalhador : public Estudante, public Trabalhador
//       (precisa inicializar Pessoa, Estudante e Trabalhador; apresentar() const)

// TODO (comentário): (a) por que Pessoa é construída uma só vez?  (b) o que ocorreria sem virtual?

// O main já está pronto: descomente o bloco do EstudanteTrabalhador quando a classe existir.
int main() {
    std::cout << "-- Objeto Estudante --\n";
    {
        Estudante estudante("Davi", "Redes");
    }
    std::cout << "-- Objeto EstudanteTrabalhador --\n";
    // EstudanteTrabalhador pessoa("Carla", "ADS", "ITEAM");
    // pessoa.apresentar();
    std::cout << "-- Fim de main --\n";
    return 0;
}
