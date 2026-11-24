// Atividade D4 - Classe Fracao com operadores sobrecarregados
#include <iostream>
#include <stdexcept>

// TODO: class Fracao (numerador_, denominador_ privados; construtor com validação e normalização;
//       numerador(), denominador(), valor(); operator+ - * / == <, todos const)
class Fracao {
public:
    Fracao(int numerador = 0, int denominador = 1) : numerador_(numerador), denominador_(denominador) {}
    int numerador() const { return numerador_; }
    int denominador() const { return denominador_; }
    double valor() const { return 0.0; }
    Fracao operator+(const Fracao& outra) const { return outra; }
    Fracao operator-(const Fracao& outra) const { return outra; }
    Fracao operator*(const Fracao& outra) const { return outra; }
    Fracao operator/(const Fracao& outra) const { return outra; }
    bool operator==(const Fracao& outra) const { return &outra == this; }
    bool operator<(const Fracao& outra) const { return &outra != this; }

private:
    int numerador_;
    int denominador_;
};

// TODO: std::ostream& operator<<(std::ostream& saida, const Fracao& f)  - escreve n/d
std::ostream& operator<<(std::ostream& saida, const Fracao& f) {
    return saida << f.numerador();
}

// O main já está pronto: não precisa alterar.
int main() {
    int n1{};
    int d1{};
    int n2{};
    int d2{};

    std::cout << "Fracao 1 (numerador denominador): ";
    if (!(std::cin >> n1 >> d1)) {
        std::cerr << "Entrada invalida.\n";
        return 1;
    }
    std::cout << "Fracao 2 (numerador denominador): ";
    if (!(std::cin >> n2 >> d2)) {
        std::cerr << "Entrada invalida.\n";
        return 1;
    }

    try {
        Fracao a(n1, d1);
        Fracao b(n2, d2);
        std::cout << a << " + " << b << " = " << a + b << '\n';
        std::cout << a << " - " << b << " = " << a - b << '\n';
        std::cout << a << " * " << b << " = " << a * b << '\n';
        std::cout << a << " / " << b << " = " << a / b << '\n';
        std::cout << a << " == " << b << ": " << (a == b ? "sim" : "nao") << '\n';
        std::cout << a << " < " << b << ": " << (a < b ? "sim" : "nao") << '\n';
        std::cout << "Valor decimal de " << a << ": " << a.valor() << '\n';
    } catch (const std::invalid_argument& erro) {
        std::cerr << "Erro: " << erro.what() << '\n';
        return 1;
    }
    return 0;
}
