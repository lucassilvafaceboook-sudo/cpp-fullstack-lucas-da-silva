// Atividade D5 - Relogio: segundos para dias, horas, minutos e segundos

#include <iomanip>
#include <iostream>

int main() {
    constexpr long long SEGUNDOS_POR_DIA{86400LL};
    constexpr long long SEGUNDOS_POR_HORA{3600LL};
    constexpr long long SEGUNDOS_POR_MINUTO{60LL};

    long long totalSegundos{};
    std::cout << "Total de segundos: ";
    if (!(std::cin >> totalSegundos) || totalSegundos < 0) {
        std::cerr << "Entrada invalida.\n";
        return 1;
    }

    long long dias{totalSegundos / SEGUNDOS_POR_DIA};
    long long resto{totalSegundos % SEGUNDOS_POR_DIA};
    long long horas{resto / SEGUNDOS_POR_HORA};
    resto %= SEGUNDOS_POR_HORA;
    long long minutos{resto / SEGUNDOS_POR_MINUTO};
    long long segundos{resto % SEGUNDOS_POR_MINUTO};

    std::cout << totalSegundos << " segundos = " << dias << " dia(s) "
              << std::setfill('0')
              << std::setw(2) << horas << ":"
              << std::setw(2) << minutos << ":"
              << std::setw(2) << segundos
              << std::setfill(' ') << "\n";

    int h{};
    int m{};
    int s{};
    std::cout << "Horario (h m s): ";
    if (!(std::cin >> h >> m >> s) || h < 0 || m < 0 || m >= 60 || s < 0 || s >= 60) {
        std::cerr << "Entrada invalida.\n";
        return 1;
    }

    long long segundosConvertidos{h * SEGUNDOS_POR_HORA + m * SEGUNDOS_POR_MINUTO + s};

    std::cout << std::setfill('0')
              << std::setw(2) << h << ":"
              << std::setw(2) << m << ":"
              << std::setw(2) << s
              << std::setfill(' ')
              << " = " << segundosConvertidos << " segundos\n";

    return 0;
}