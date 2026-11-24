// Atividade I3 - Cadastro rapido: o bug do getline

#include <iostream>
#include <limits>
#include <string>

int main() {
    int idade{};
    std::string nome;

    std::cout << "Idade: ";
    if (!(std::cin >> idade)) {
        std::cerr << "Entrada invalida.\n";
        return 1;
    }

    // O que sobrou no buffer de entrada depois de `std::cin >> idade`:
    // O operador >> le apenas os digitos do numero e para antes da quebra de linha ('\n')
    // gerada quando o usuario aperta Enter. Esse '\n' permanece no buffer; sem limpa-lo,
    // o std::getline le imediatamente esse '\n' e devolve uma string vazia.

    // Correcao 1 (ativa): limpa todo o restante da linha ate o '\n'
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    std::cout << "Nome completo: ";
    std::getline(std::cin, nome);

    // Correcao 2 (alternativa comentada): descarta espacos em branco iniciais
    // std::cout << "Nome completo: ";
    // std::getline(std::cin >> std::ws, nome);

    // Efeito colateral de std::ws e quando a primeira opcao e mais segura:
    // std::ws consome todos os caracteres de espaco em branco (espacos, tabulacoes e '\n')
    // antes do texto, o que tambem remove espacos iniciais intencionais e pode travar
    // esperando entrada se o usuario apenas apertar Enter (linha vazia).
    // A primeira opcao (std::cin.ignore) e mais segura porque descarta exatamente o que
    // restou da linha anterior (inclusive texto extra digitado apos o numero) sem alterar
    // a leitura da linha seguinte.

    std::cout << "Aluno: " << nome << " (" << idade << " anos)\n";

    return 0;
}