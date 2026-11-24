// Atividade I1 - Herança simples: Pessoa, Estudante e Trabalhador
#include <iomanip>
#include <iostream>
#include <string>

// TODO: class Pessoa (atributos protected nome_ e idade_; construtor, destrutor e apresentar() const)
class Pessoa {
public:
    Pessoa(const std::string& nome, int idade) : nome_(nome), idade_(idade) {}
    void apresentar() const {}

protected:
    std::string nome_;
    int idade_;
};

// TODO: class Estudante : public Pessoa (curso_)
class Estudante : public Pessoa {
public:
    Estudante(const std::string& nome, int idade, const std::string& curso) : Pessoa(nome, idade) { (void)curso; }
};

// TODO: class Trabalhador : public Pessoa (salario_)
class Trabalhador : public Pessoa {
public:
    Trabalhador(const std::string& nome, int idade, double salario) : Pessoa(nome, idade) { (void)salario; }
};

// TODO (comentário): explique a ordem das mensagens de construção e de destruição.

// O main já está pronto: não precisa alterar.
int main() {
    Estudante estudante("Ana", 20, "ADS");
    Trabalhador trabalhador("Bruno", 35, 4200.0);
    estudante.apresentar();
    trabalhador.apresentar();
    return 0;
}
