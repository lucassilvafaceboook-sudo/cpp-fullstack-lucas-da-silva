// Atividade F3 - Conta bancária com encapsulamento
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

// TODO: implemente o construtor (com validação) e os três métodos
Conta::Conta(double saldoInicial) : saldo_(saldoInicial) {}
bool Conta::depositar(double valor) {
    (void)valor;
    return false;
}
bool Conta::sacar(double valor) {
    (void)valor;
    return false;
}
double Conta::saldo() const { return saldo_; }

int main() {
    double inicial{};
    double deposito{};
    double saque{};

    std::cout << "Saldo inicial: ";
    // TODO: leia o saldo inicial e verifique a leitura

    // TODO: dentro de try, crie a Conta, leia "Deposito: " e "Saque: " e mostre os resultados
    //       catch (const std::invalid_argument& erro): "Erro: ..." em cerr e return 1
    // TODO: mostre "Saldo final: " com duas casas decimais
    (void)inicial;
    (void)deposito;
    (void)saque;
    return 0;
}
