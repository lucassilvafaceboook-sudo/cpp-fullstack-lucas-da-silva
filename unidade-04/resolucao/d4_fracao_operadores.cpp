// Atividade D4 - Classe Fracao com operadores sobrecarregados
#include <iostream>
#include <stdexcept>

class Fracao {
public:
    Fracao(int numerador = 0, int denominador = 1)
        : numerador_(numerador), denominador_(denominador) {
        if (denominador_ == 0) {
            throw std::invalid_argument("Denominador zero");
        }
        normalizar();
    }

    int numerador() const { return numerador_; }
    int denominador() const { return denominador_; }
    double valor() const { return static_cast<double>(numerador_) / denominador_; }

    Fracao operator+(const Fracao& outra) const {
        return Fracao(numerador_ * outra.denominador_ + outra.numerador_ * denominador_,
                      denominador_ * outra.denominador_);
    }

    Fracao operator-(const Fracao& outra) const {
        return Fracao(numerador_ * outra.denominador_ - outra.numerador_ * denominador_,
                      denominador_ * outra.denominador_);
    }

    Fracao operator*(const Fracao& outra) const {
        return Fracao(numerador_ * outra.numerador_, denominador_ * outra.denominador_);
    }

    Fracao operator/(const Fracao& outra) const {
        if (outra.numerador_ == 0) {
            throw std::invalid_argument("Divisao por fracao nula");
        }
        return Fracao(numerador_ * outra.denominador_, denominador_ * outra.numerador_);
    }

    bool operator==(const Fracao& outra) const {
        return numerador_ == outra.numerador_ && denominador_ == outra.denominador_;
    }

    bool operator<(const Fracao& outra) const {
        long long lhs = static_cast<long long>(numerador_) * outra.denominador_;
        long long rhs = static_cast<long long>(outra.numerador_) * denominador_;
        return lhs < rhs;
    }

private:
    int numerador_;
    int denominador_;

    static int mdc(int a, int b) {
        if (a < 0) a = -a;
        if (b < 0) b = -b;
        while (b != 0) {
            int r = a % b;
            a = b;
            b = r;
        }
        return a == 0 ? 1 : a;
    }

    void normalizar() {
        if (denominador_ < 0) {
            numerador_ = -numerador_;
            denominador_ = -denominador_;
        }
        if (numerador_ == 0) {
            denominador_ = 1;
            return;
        }
        int divisor = mdc(numerador_, denominador_);
        numerador_ /= divisor;
        denominador_ /= divisor;
    }
};

std::ostream& operator<<(std::ostream& saida, const Fracao& f) {
    return saida << f.numerador() << '/' << f.denominador();
}

// O main ja esta pronto: nao precisa alterar.
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