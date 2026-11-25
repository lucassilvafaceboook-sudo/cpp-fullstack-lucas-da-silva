// Atividade F5 - Sobrecarga de operadores: Vetor2D
#include <iostream>

class Vetor2D {
public:
    Vetor2D(double x = 0.0, double y = 0.0) : x_(x), y_(y) {}

    double x() const { return x_; }
    double y() const { return y_; }

    Vetor2D operator+(const Vetor2D& outro) const {
        return Vetor2D(x_ + outro.x_, y_ + outro.y_);
    }

    Vetor2D operator-(const Vetor2D& outro) const {
        return Vetor2D(x_ - outro.x_, y_ - outro.y_);
    }

    bool operator==(const Vetor2D& outro) const {
        return x_ == outro.x_ && y_ == outro.y_;
    }

private:
    double x_;
    double y_;
};

void mostrar(const char* rotulo, double x, double y) {
    std::cout << rotulo << ": (" << x << ", " << y << ")\n";
}

int main() {
    double x1{};
    double y1{};
    double x2{};
    double y2{};

    std::cout << "Dois vetores (x1 y1 x2 y2): ";
    if (!(std::cin >> x1 >> y1 >> x2 >> y2)) {
        std::cerr << "Entrada invalida.\n";
        return 1;
    }

    Vetor2D a(x1, y1);
    Vetor2D b(x2, y2);
    Vetor2D soma = a + b;
    Vetor2D diff = a - b;

    mostrar("Soma", soma.x(), soma.y());
    mostrar("Diferenca", diff.x(), diff.y());
    std::cout << "Iguais: " << (a == b ? "sim" : "nao") << '\n';
    return 0;
}