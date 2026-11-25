// Atividade D3 - Folha de pagamento polimorfica
#include <cstddef>
#include <iomanip>
#include <iostream>
#include <string>
#include <vector>

class Funcionario {
public:
    explicit Funcionario(const std::string& nome) : nome_(nome) {}
    virtual ~Funcionario() {
        std::cout << "Destruindo Funcionario: " << nome_ << '\n';
    }
    virtual double salario() const = 0;
    virtual std::string cargo() const = 0;
    const std::string& nome() const { return nome_; }

private:
    std::string nome_;
};

class Assalariado : public Funcionario {
public:
    Assalariado(const std::string& nome, double salarioMensal)
        : Funcionario(nome), salarioMensal_(salarioMensal) {}
    ~Assalariado() override {
        std::cout << "Destruindo Assalariado: " << nome() << '\n';
    }

    double salario() const override { return salarioMensal_; }
    std::string cargo() const override { return "Assalariado"; }

private:
    double salarioMensal_;
};

class Horista : public Funcionario {
public:
    Horista(const std::string& nome, double valorHora, double horas)
        : Funcionario(nome), valorHora_(valorHora), horas_(horas) {}
    ~Horista() override {
        std::cout << "Destruindo Horista: " << nome() << '\n';
    }

    double salario() const override {
        if (horas_ <= 160.0) {
            return valorHora_ * horas_;
        }
        double extras = horas_ - 160.0;
        return (160.0 * valorHora_) + (extras * valorHora_ * 1.5);
    }
    std::string cargo() const override { return "Horista"; }

private:
    double valorHora_;
    double horas_;
};

class Comissionado : public Funcionario {
public:
    Comissionado(const std::string& nome, double fixo, double vendas, double percentual)
        : Funcionario(nome), fixo_(fixo), vendas_(vendas), percentual_(percentual) {}
    ~Comissionado() override {
        std::cout << "Destruindo Comissionado: " << nome() << '\n';
    }

    double salario() const override { return fixo_ + vendas_ * (percentual_ / 100.0); }
    std::string cargo() const override { return "Comissionado"; }

private:
    double fixo_;
    double vendas_;
    double percentual_;
};

// Sem o destrutor virtual na base, deletar um objeto derivado atraves de um ponteiro
// Funcionario* gera comportamento indefinido: o destrutor da classe derivada pode nao
// ser executado, causando vazamento de recursos.

// O main ja esta pronto: nao precisa alterar.
int main() {
    std::vector<Funcionario*> equipe;
    equipe.push_back(new Assalariado("Ana", 3500.0));
    equipe.push_back(new Horista("Bruno", 25.0, 170.0));
    equipe.push_back(new Comissionado("Carla", 1500.0, 20000.0, 8.0));

    std::cout << std::fixed << std::setprecision(2);
    double total{0.0};
    const Funcionario* maior = equipe[0];
    for (std::size_t i = 0; i < equipe.size(); ++i) {
        const Funcionario* funcionario = equipe[i];
        std::cout << funcionario->nome() << " (" << funcionario->cargo() << "): R$ " << funcionario->salario() << '\n';
        total += funcionario->salario();
        if (funcionario->salario() > maior->salario()) {
            maior = funcionario;
        }
    }
    std::cout << "Total da folha: R$ " << total << '\n';
    std::cout << "Maior salario: " << maior->nome() << '\n';

    for (std::size_t i = 0; i < equipe.size(); ++i) {
        delete equipe[i];
    }
    return 0;
}