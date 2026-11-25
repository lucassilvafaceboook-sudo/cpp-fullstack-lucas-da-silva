// Atividade F3 - Organizando funcoes em namespaces
#include <iomanip>
#include <iostream>

constexpr double PI{3.14159265358979323846};

namespace geometria {
double areaRetangulo(double largura, double altura) { return largura * altura; }
double areaCirculo(double raio) { return PI * raio * raio; }
double calcular(double a, double b) { return a * b; }
}  // namespace geometria

namespace financas {
double jurosSimples(double capital, double taxaPercentual, int meses) {
    return capital * (taxaPercentual / 100.0) * meses;
}
double desconto(double valor, double percentual) {
    return valor * (1.0 - percentual / 100.0);
}
double calcular(double capital, double taxaPercentual) {
    return capital * (1.0 + taxaPercentual / 100.0);
}
}  // namespace financas

// Os dois "calcular" nao colidem porque pertencem a escopos (namespaces) distintos.
// Ao usar o nome qualificado com :: (geometria::calcular e financas::calcular),
// o compilador sabe exatamente qual funcao chamar sem ambiguidade.

// O main ja esta pronto: nao precisa alterar.
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