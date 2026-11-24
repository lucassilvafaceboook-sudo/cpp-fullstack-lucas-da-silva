// Atividade I2 - Polimorfismo com Forma abstrata
#include <iomanip>
#include <iostream>
#include <string>

constexpr double PI{3.14159265358979323846};

// TODO: class Forma (abstrata): destrutor virtual, area() e nome() virtuais puros
class Forma {
public:
    virtual ~Forma() = default;
    virtual double area() const { return 0.0; }
    virtual std::string nome() const { return ""; }
};

// TODO: class Retangulo : public Forma  (largura, altura)
class Retangulo : public Forma {
public:
    Retangulo(double largura, double altura) { (void)largura; (void)altura; }
};

// TODO: class Circulo : public Forma  (raio)
class Circulo : public Forma {
public:
    explicit Circulo(double raio) { (void)raio; }
};

// TODO: class Triangulo : public Forma  (base, altura)
class Triangulo : public Forma {
public:
    Triangulo(double base, double altura) { (void)base; (void)altura; }
};

// TODO (comentário): por que não se pode criar "Forma f;" e por que o destrutor é virtual?

// O main já está pronto: não precisa alterar.
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
