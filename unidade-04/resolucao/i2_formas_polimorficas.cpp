// Atividade I2 - Polimorfismo com Forma abstrata
#include <iomanip>
#include <iostream>
#include <string>

constexpr double PI{3.14159265358979323846};

class Forma {
public:
    virtual ~Forma() = default;
    virtual double area() const = 0;
    virtual std::string nome() const = 0;
};

class Retangulo : public Forma {
public:
    Retangulo(double largura, double altura) : largura_(largura), altura_(altura) {}
    double area() const override { return largura_ * altura_; }
    std::string nome() const override { return "Retangulo"; }

private:
    double largura_;
    double altura_;
};

class Circulo : public Forma {
public:
    explicit Circulo(double raio) : raio_(raio) {}
    double area() const override { return PI * raio_ * raio_; }
    std::string nome() const override { return "Circulo"; }

private:
    double raio_;
};

class Triangulo : public Forma {
public:
    Triangulo(double base, double altura) : base_(base), altura_(altura) {}
    double area() const override { return (base_ * altura_) / 2.0; }
    std::string nome() const override { return "Triangulo"; }

private:
    double base_;
    double altura_;
};

// Nao e possivel criar "Forma f;" porque Forma possui metodos virtuais puros (= 0),
// tornando-a uma classe abstrata que serve apenas como interface/contrato para derivadas.
// O destrutor precisa ser virtual para garantir que, ao deletar um objeto derivado via
// ponteiro Forma*, o destrutor da classe derivada tambem seja executado corretamente.

// O main ja esta pronto: nao precisa alterar.
void mostrar(const Forma& forma) {
    std::cout << std::fixed << std::setprecision(2);
    std::cout << forma.nome() << ": area = " << forma.area() << '\n';
}

int main() {
    Retangulo retangulo(4.0, 5.0);
    Circulo circulo(3.0);
    Triangulo triangulo(6.0, 4.0);

    mostrar(retangulo);
    mostrar(circulo);
    mostrar(triangulo);

    const Forma* formas[]{&retangulo, &circulo, &triangulo};
    double total{0.0};
    for (const Forma* forma : formas) {
        total += forma->area();
    }
    std::cout << "Soma das areas: " << total << '\n';
    return 0;
}