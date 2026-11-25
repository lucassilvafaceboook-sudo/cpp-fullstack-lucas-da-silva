// Atividade I1 - Heranca simples: Pessoa, Estudante e Trabalhador
#include <iomanip>
#include <iostream>
#include <string>

class Pessoa {
public:
    Pessoa(const std::string& nome, int idade) : nome_(nome), idade_(idade) {
        std::cout << "Pessoa criada: " << nome_ << '\n';
    }
    ~Pessoa() {
        std::cout << "Pessoa destruida: " << nome_ << '\n';
    }
    void apresentar() const {
        std::cout << "Nome: " << nome_ << '\n';
        std::cout << "Idade: " << idade_ << '\n';
    }

protected:
    std::string nome_;
    int idade_;
};

class Estudante : public Pessoa {
public:
    Estudante(const std::string& nome, int idade, const std::string& curso)
        : Pessoa(nome, idade), curso_(curso) {
        std::cout << "Estudante criado: " << nome_ << '\n';
    }
    ~Estudante() {
        std::cout << "Estudante destruido: " << nome_ << '\n';
    }
    void apresentar() const {
        Pessoa::apresentar();
        std::cout << "Curso: " << curso_ << '\n';
    }

private:
    std::string curso_;
};

class Trabalhador : public Pessoa {
public:
    Trabalhador(const std::string& nome, int idade, double salario)
        : Pessoa(nome, idade), salario_(salario) {
        std::cout << "Trabalhador criado: " << nome_ << '\n';
    }
    ~Trabalhador() {
        std::cout << "Trabalhador destruido: " << nome_ << '\n';
    }
    void apresentar() const {
        Pessoa::apresentar();
        std::cout << std::fixed << std::setprecision(2);
        std::cout << "Salario: R$ " << salario_ << '\n';
    }

private:
    double salario_;
};

// Ordem de construcao e destruicao:
// Na construcao de cada objeto derivado, o construtor da classe base (Pessoa) roda
// primeiro e o da derivada (Estudante/Trabalhador) roda depois. Na destruicao, ao
// fim de main, os objetos sao destruidos na ordem inversa da criacao (primeiro
// trabalhador, depois estudante), e em cada um o destrutor da derivada roda antes
// do destrutor da base.

// O main ja esta pronto: nao precisa alterar.
int main() {
    Estudante estudante("Ana", 20, "ADS");
    Trabalhador trabalhador("Bruno", 35, 4200.0);
    estudante.apresentar();
    trabalhador.apresentar();
    return 0;
}