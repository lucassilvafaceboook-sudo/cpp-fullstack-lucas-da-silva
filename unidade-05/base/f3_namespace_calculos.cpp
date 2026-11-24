// Atividade F3 - Organizando funções em namespaces
#include <iomanip>
#include <iostream>

constexpr double PI{3.14159265358979323846};

// TODO: namespace geometria { areaRetangulo, areaCirculo, calcular }
namespace geometria {
double areaRetangulo(double largura, double altura) { (void)largura; (void)altura; return 0.0; }
double areaCirculo(double raio) { (void)raio; return PI * 0.0; }
double calcular(double a, double b) { (void)a; (void)b; return 0.0; }
}  // namespace geometria

// TODO: namespace financas { jurosSimples, desconto, calcular }
namespace financas {
double jurosSimples(double capital, double taxaPercentual, int meses) { (void)capital; (void)taxaPercentual; (void)meses; return 0.0; }
double desconto(double valor, double percentual) { (void)valor; (void)percentual; return 0.0; }
double calcular(double capital, double taxaPercentual) { (void)capital; (void)taxaPercentual; return 0.0; }
}  // namespace financas

// TODO (comentário): por que os dois "calcular" não colidem?

// O main já está pronto: não precisa alterar.
int main() {
    std::cout << std::fixed << std::setprecision(2);
    std::cout << "Area do retangulo 3 x 4: " << geometria::areaRetangulo(3.0, 4.0) << '\n';
    std::cout << "Area do circulo r=2: " << geometria::areaCirculo(2.0) << '\n';
    std::cout << "Juros simples (1000, 2%, 6 meses): " << financas::jurosSimples(1000.0, 2.0, 6) << '\n';
    std::cout << "Desconto (200, 15%): " << financas::desconto(200.0, 15.0) << '\n';
    std::cout << "geometria::calcular(3, 4) = " << geometria::calcular(3.0, 4.0) << '\n';
    std::cout << "financas::calcular(1000, 5) = " << financas::calcular(1000.0, 5.0) << '\n';
    return 0;
}
