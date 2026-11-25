// Atividade F4 - Funcoes com retorno e funcoes void
#include <iomanip>
#include <iostream>

int maiorDeTres(int a, int b, int c) {
    int maior{a};
    if (b > maior) maior = b;
    if (c > maior) maior = c;
    return maior;
}

bool ehPar(int n) {
    return (n % 2 == 0);
}

double mediaDeTres(int a, int b, int c) {
    return (a + b + c) / 3.0;
}

void exibirRelatorio(int maior, bool par, double media) {
    std::cout << "Maior: " << maior << (par ? " (par)" : " (impar)") << '\n';
    std::cout << std::fixed << std::setprecision(2);
    std::cout << "Media: " << media << '\n';
}

int main() {
    int a{};
    int b{};
    int c{};

    std::cout << "Tres inteiros: ";
    if (!(std::cin >> a >> b >> c)) {
        std::cerr << "Entrada invalida.\n";
        return 1;
    }

    int maior{maiorDeTres(a, b, c)};
    bool par{ehPar(maior)};
    double media{mediaDeTres(a, b, c)};

    exibirRelatorio(maior, par, media);
    return 0;
}