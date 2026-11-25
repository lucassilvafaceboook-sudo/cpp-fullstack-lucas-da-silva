// Atividade F4 - Classe Retangulo com metodos const
#include <iomanip>
#include <iostream>
#include <stdexcept>

class Retangulo {
public:
    Retangulo(double largura, double altura) : largura_(largura), altura_(altura) {
        if (largura <= 0.0 || altura <= 0.0) {
            throw std::invalid_argument("Dimensoes devem ser positivas");
        }
    }

    double area() const { return largura_ * altura_; }
    double perimetro() const { return 2.0 * (largura_ + altura_); }
    bool ehQuadrado() const { return largura_ == altura_; }

private:
    double largura_;
    double altura_;
};

int main() {
    double largura{};
    double altura{};

    std::cout << "Largura e altura: ";
    if (!(std::cin >> largura >> altura)) {
        std::cerr << "Entrada invalida.\n";
        return 1;
    }

    std::cout << std::fixed << std::setprecision(2);
    try {
        Retangulo r(largura, altura);
        std::cout << "Area: " << r.area() << '\n';
        std::cout << "Perimetro: " << r.perimetro() << '\n';
        std::cout << "Quadrado: " << (r.ehQuadrado() ? "sim" : "nao") << '\n';
    } catch (const std::invalid_argument& erro) {
        std::cerr << "Erro: " << erro.what() << '\n';
        return 1;
    }

    return 0;
}