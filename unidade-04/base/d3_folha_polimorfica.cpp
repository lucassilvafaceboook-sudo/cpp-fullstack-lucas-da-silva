// Atividade D3 - Folha de pagamento polimórfica
#include <cstddef>
#include <iomanip>
#include <iostream>
#include <string>
#include <vector>

// TODO: class Funcionario (abstrata, destrutor virtual, salario() e cargo() virtuais puros)
class Funcionario {
public:
    explicit Funcionario(const std::string& nome) : nome_(nome) {}
    virtual ~Funcionario() = default;
    virtual double salario() const { return 0.0; }
    virtual std::string cargo() const { return ""; }
    const std::string& nome() const { return nome_; }

private:
    std::string nome_;
};

// TODO: class Assalariado : public Funcionario  (nome, salarioMensal)
class Assalariado : public Funcionario {
public:
    Assalariado(const std::string& nome, double salarioMensal) : Funcionario(nome) { (void)salarioMensal; }
};

// TODO: class Horista : public Funcionario  (nome, valorHora, horas; horas acima de 160 valem 1,5x)
class Horista : public Funcionario {
public:
    Horista(const std::string& nome, double valorHora, double horas) : Funcionario(nome) { (void)valorHora; (void)horas; }
};

// TODO: class Comissionado : public Funcionario  (nome, fixo, vendas, percentual)
class Comissionado : public Funcionario {
public:
    Comissionado(const std::string& nome, double fixo, double vendas, double percentual) : Funcionario(nome) {
        (void)fixo;
        (void)vendas;
        (void)percentual;
    }
};

// TODO (comentário): por que o destrutor da base precisa ser virtual?

// O main já está pronto: não precisa alterar.
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
