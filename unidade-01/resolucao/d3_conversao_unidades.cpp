// Atividade D3 - Conversao encadeada de unidades

#include <iomanip>
#include <iostream>

int main() {
    double metros{1234.5};

    // Constantes nomeadas para os fatores de conversao
    constexpr double METROS_POR_KM{1000.0};
    constexpr double CM_POR_METRO{100.0};
    constexpr double MM_POR_METRO{1000.0};
    constexpr double METROS_POR_POLEGADA{0.0254};
    constexpr double METROS_POR_PE{0.3048};

    // Calculos
    double quilometros{metros / METROS_POR_KM};
    double centimetros{metros * CM_POR_METRO};
    double milimetros{metros * MM_POR_METRO};
    double polegadas{metros / METROS_POR_POLEGADA};
    double pes{metros / METROS_POR_PE};

    constexpr int LARGURA_ROTULO{14};
    constexpr int LARGURA_VALOR{14};

    std::cout << std::fixed << std::setprecision(4);
    std::cout << "Distancia: " << metros << " m\n";

    std::cout << std::left  << std::setw(LARGURA_ROTULO) << "Quilometros"
              << std::right << std::setw(LARGURA_VALOR)  << quilometros << "\n";
    std::cout << std::left  << std::setw(LARGURA_ROTULO) << "Centimetros"
              << std::right << std::setw(LARGURA_VALOR)  << centimetros << "\n";
    std::cout << std::left  << std::setw(LARGURA_ROTULO) << "Milimetros"
              << std::right << std::setw(LARGURA_VALOR)  << milimetros << "\n";
    std::cout << std::left  << std::setw(LARGURA_ROTULO) << "Polegadas"
              << std::right << std::setw(LARGURA_VALOR)  << polegadas << "\n";
    std::cout << std::left  << std::setw(LARGURA_ROTULO) << "Pes"
              << std::right << std::setw(LARGURA_VALOR)  << pes << "\n";

    // Por que usar constantes nomeadas em vez de numeros soltos ("numeros magicos")?
    // Constantes nomeadas tornam o codigo autoexplicativo, evitam erros de digitacao
    // quando o mesmo fator e usado em varios pontos e facilitam a manutencao,
    // ja que qualquer alteracao precisa ser feita em um unico lugar.

    return 0;
}