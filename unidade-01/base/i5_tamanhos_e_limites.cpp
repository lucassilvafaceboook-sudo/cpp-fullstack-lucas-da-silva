// Atividade I5 - Tamanhos e limites dos tipos
#include <iostream>
#include <limits>

int main() {
    std::cout << "short: " << sizeof(short) << " bytes"
              << ", min=" << std::numeric_limits<short>::min()
              << ", max=" << std::numeric_limits<short>::max() << '\n';

    // TODO: faça o mesmo para int, long long e unsigned int
    // TODO: mostre os limites de double (min() e max())
    // TODO: mostre o maior unsigned int e o resultado de somar 1 a ele
    // TODO (comentário): portabilidade dos tamanhos e estouro de int com sinal
    return 0;
}
