// Atividade F3 - Conta bancaria com encapsulamento
#include <iomanip>
#include <iostream>
#include <stdexcept>

class Conta {
public:
    explicit Conta(double saldoInicial);
    bool depositar(double valor);
    bool sacar(double valor);
    double saldo() const;

private:
    double saldo_;
};

Conta::Conta(double saldoInicial) : saldo_(saldoInicial) {
    if (saldoInicial < 0.0) {
        throw std::invalid_argument("Saldo inicial negativo");
    }
}

bool Conta::depositar(double valor) {
    if (valor > 0.0) {
        saldo_ += valor;
        return true;
    }
    return false;
}

bool Conta::sacar(double valor) {
    if (valor > 0.0 && valor <= saldo_) {
        saldo_ -= valor;
        return true;
    }
    return false;
}

double Conta::saldo() const { return saldo_; }

int main() {
    double inicial{};
    double deposito{};
    double saque{};

    std::cout << "Saldo inicial: ";
    if (!(std::cin >> inicial)) {
        std::cerr << "Entrada invalida.\n";
        return 1;
    }

    try {
        Conta conta(inicial);

        std::cout << "Deposito: ";
        if (!(std::cin >> deposito)) {
            std::cerr << "Entrada invalida.\n";
            return 1;
        }
        std::cout << (conta.depositar(deposito) ? "Deposito realizado\n" : "Deposito recusado\n");

        std::cout << "Saque: ";
        if (!(std::cin >> saque)) {
            std::cerr << "Entrada invalida.\n";
            return 1;
        }
        std::cout << (conta.sacar(saque) ? "Saque realizado\n" : "Saque recusado\n");

        std::cout << std::fixed << std::setprecision(2);
        std::cout << "Saldo final: " << conta.saldo() << '\n';
    } catch (const std::invalid_argument& erro) {
        std::cerr << "Erro: " << erro.what() << '\n';
        return 1;
    }

    return 0;
}