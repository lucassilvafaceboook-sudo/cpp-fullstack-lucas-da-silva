// Atividade I5 - Tamanhos e limites dos tipos

#include <iostream>
#include <limits>

int main() {
    std::cout << "short: " << sizeof(short) << " bytes"
              << ", min=" << std::numeric_limits<short>::min()
              << ", max=" << std::numeric_limits<short>::max() << '\n';

    std::cout << "int: " << sizeof(int) << " bytes"
              << ", min=" << std::numeric_limits<int>::min()
              << ", max=" << std::numeric_limits<int>::max() << '\n';

    std::cout << "long long: " << sizeof(long long) << " bytes"
              << ", min=" << std::numeric_limits<long long>::min()
              << ", max=" << std::numeric_limits<long long>::max() << '\n';

    std::cout << "unsigned int: " << sizeof(unsigned int) << " bytes"
              << ", min=" << std::numeric_limits<unsigned int>::min()
              << ", max=" << std::numeric_limits<unsigned int>::max() << '\n';

    std::cout << "double: " << sizeof(double) << " bytes"
              << ", min=" << std::numeric_limits<double>::min()
              << ", max=" << std::numeric_limits<double>::max() << '\n';

    unsigned int maxUnsigned{std::numeric_limits<unsigned int>::max()};
    unsigned int resultado{maxUnsigned + 1U};
    std::cout << "unsigned int maximo + 1 = " << resultado << '\n';

    // Por que nao presumir o tamanho dos tipos e diferenca no estouro (overflow):
    // O padrao C++ define apenas tamanhos minimos para os tipos fundamentais, mas o
    // tamanho exato pode variar entre arquiteturas e compiladores (por exemplo, sistemas
    // de 32 ou 64 bits). Por isso, para garantir portabilidade, devemos usar sizeof e
    // std::numeric_limits em vez de valores fixos.
    // Quanto ao estouro: para inteiros sem sinal (unsigned), o padrao define aritmetica
    // modular, entao somar 1 ao valor maximo sempre volta de forma previsivel para 0.
    // Ja para inteiros com sinal (como int), o overflow gera comportamento indefinido
    // (undefined behavior), o que significa que o compilador pode otimizar o codigo de
    // formas inesperadas ou produzir resultados imprevisiveis.

    return 0;
}