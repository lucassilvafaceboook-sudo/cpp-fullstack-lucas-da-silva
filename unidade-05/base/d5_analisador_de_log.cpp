// Atividade D5 - Analisador de arquivo de log
// O arquivo servidor.log está na mesma pasta deste arquivo.
#include <algorithm>
#include <fstream>
#include <iostream>
#include <map>
#include <sstream>
#include <string>
#include <vector>

struct Evento {
    std::string quando;  // "AAAA-MM-DD HH:MM:SS"
    std::string modulo;  // sem o ':'
    std::string mensagem;
};

int main() {
    std::ifstream arquivo("servidor.log");
    // TODO: verifique a abertura ("Arquivo servidor.log nao encontrado" em cerr, return 1)

    std::map<std::string, int> niveis;
    std::vector<Evento> erros;
    int validas{0};
    int ignoradas{0};

    std::string linha;
    int numeroLinha{0};
    // TODO: while (std::getline(arquivo, linha)) { ++numeroLinha; ... }
    //   - remova '\r' do fim; extraia data, hora, nivel, modulo e mensagem com istringstream
    //   - valide os quatro campos; linha inválida: "Linha N ignorada (formato invalido)"
    //   - conte o nível; guarde os ERROR em 'erros'

    std::cout << "Linhas validas: " << validas << '\n';
    std::cout << "Linhas ignoradas: " << ignoradas << '\n';
    // TODO: mostre INFO, WARN e ERROR (0 se ausente)
    // TODO: ordene 'erros' por 'quando' (std::sort + lambda) e mostre "Erros em ordem de horario:" e as linhas
    // TODO: grave resumo.txt ("Total=N INFO=A WARN=B ERROR=C"), verificando a escrita; leia de volta e mostre
    //       "Resumo gravado em resumo.txt" e "Primeira linha do resumo: ..."
    return 0;
}
