// Atividade D5 - Relógio: segundos para dias, horas, minutos e segundos
#include <iomanip>
#include <iostream>

int main() {
    long long totalSegundos{};

    std::cout << "Total de segundos: ";
    // TODO: leia e valide totalSegundos (>= 0)

    // TODO: calcule dias, horas, minutos e segundos usando / e %
    // TODO: exiba no formato "93784 segundos = 1 dia(s) 02:03:04"

    int h{};
    int m{};
    int s{};
    std::cout << "Horario (h m s): ";
    // TODO: leia h, m, s e valide (h >= 0, 0 <= m < 60, 0 <= s < 60)
    // TODO: converta para segundos e exiba no formato "02:03:04 = 7384 segundos"

    std::cout << std::setw(2) << std::setfill('0') << h << m << s << '\n';
    return 0;
}
