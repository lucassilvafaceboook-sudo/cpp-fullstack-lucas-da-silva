// Atividade D2 - Heranca multipla e o problema do diamante
#include <iostream>
#include <string>

class Pessoa {
public:
    explicit Pessoa(const std::string& nome) : nome_(nome) {
        std::cout << "Pessoa construida: " << nome_ << '\n';
    }
    ~Pessoa() {
        std::cout << "Pessoa destruida: " << nome_ << '\n';
    }
    const std::string& nome() const { return nome_; }

private:
    std::string nome_;
};

class Estudante : virtual public Pessoa {
public:
    Estudante(const std::string& nome, const std::string& curso) : Pessoa(nome), curso_(curso) {
        std::cout << "Estudante construido: " << curso_ << '\n';
    }
    ~Estudante() {
        std::cout << "Estudante destruido: " << curso_ << '\n';
    }
    const std::string& curso() const { return curso_; }

private:
    std::string curso_;
};

class Trabalhador : virtual public Pessoa {
public:
    Trabalhador(const std::string& nome, const std::string& empresa) : Pessoa(nome), empresa_(empresa) {
        std::cout << "Trabalhador construido: " << empresa_ << '\n';
    }
    ~Trabalhador() {
        std::cout << "Trabalhador destruido: " << empresa_ << '\n';
    }
    const std::string& empresa() const { return empresa_; }

private:
    std::string empresa_;
};

class EstudanteTrabalhador : public Estudante, public Trabalhador {
public:
    EstudanteTrabalhador(const std::string& nome, const std::string& curso, const std::string& empresa)
        : Pessoa(nome), Estudante(nome, curso), Trabalhador(nome, empresa) {
        std::cout << "EstudanteTrabalhador construido\n";
    }
    ~EstudanteTrabalhador() {
        std::cout << "EstudanteTrabalhador destruido\n";
    }

    void apresentar() const {
        std::cout << "Nome: " << nome() << '\n';
        std::cout << "Curso: " << curso() << '\n';
        std::cout << "Empresa: " << empresa() << '\n';
    }
};

// (a) Com heranca virtual, Estudante e Trabalhador compartilham uma unica subinstancia
//     de Pessoa, que e inicializada diretamente pela classe mais derivada (EstudanteTrabalhador).
// (b) Sem virtual, EstudanteTrabalhador teria duas copias de Pessoa (uma via Estudante e
//     outra via Trabalhador), e chamar nome() causaria erro de compilacao por ambiguidade.

int main() {
    std::cout << "-- Objeto Estudante --\n";
    {
        Estudante estudante("Davi", "Redes");
    }
    std::cout << "-- Objeto EstudanteTrabalhador --\n";
    EstudanteTrabalhador pessoa("Carla", "ADS", "ITEAM");
    pessoa.apresentar();
    std::cout << "-- Fim de main --\n";
    return 0;
}