// Atividade D5 - Analisador de arquivo de log
// O arquivo servidor.log esta na mesma pasta deste arquivo.
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
    if (!arquivo) {
        std::cerr << "Arquivo servidor.log nao encontrado\n";
        return 1;
    }

    std::map<std::string, int> niveis;
    std::vector<Evento> erros;
    int validas{0};
    int ignoradas{0};

    std::string linha;
    int numeroLinha{0};
    while (std::getline(arquivo, linha)) {
        ++numeroLinha;
        if (!linha.empty() && linha.back() == '\r') {
            linha.pop_back();
        }

        std::istringstream fluxo(linha);
        std::string data;
        std::string hora;
        std::string nivel;
        std::string modulo;
        std::string mensagem;

        bool lido = static_cast<bool>(fluxo >> data >> hora >> nivel >> modulo);
        if (lido) {
            std::getline(fluxo, mensagem);
            if (!mensagem.empty() && mensagem[0] == ' ') {
                mensagem = mensagem.substr(1);
            }
        }

        bool dataOk = (data.size() == 10 && data[4] == '-' && data[7] == '-');
        bool horaOk = (hora.size() == 8 && hora[2] == ':' && hora[5] == ':');
        bool nivelOk = (nivel == "INFO" || nivel == "WARN" || nivel == "ERROR");
        bool moduloOk = (!modulo.empty() && modulo.back() == ':');

        if (!lido || !dataOk || !horaOk || !nivelOk || !moduloOk) {
            std::cout << "Linha " << numeroLinha << " ignorada (formato invalido)\n";
            ++ignoradas;
            continue;
        }

        ++validas;
        ++niveis[nivel];

        if (nivel == "ERROR") {
            erros.push_back(Evento{data + " " + hora, modulo.substr(0, modulo.size() - 1), mensagem});
        }
    }

    std::cout << "Linhas validas: " << validas << '\n';
    std::cout << "Linhas ignoradas: " << ignoradas << '\n';
    std::cout << "INFO: " << niveis["INFO"] << '\n';
    std::cout << "WARN: " << niveis["WARN"] << '\n';
    std::cout << "ERROR: " << niveis["ERROR"] << '\n';

    std::sort(erros.begin(), erros.end(), [](const Evento& a, const Evento& b) {
        return a.quando < b.quando;
    });

    std::cout << "Erros em ordem de horario:\n";
    for (const Evento& e : erros) {
        std::cout << e.quando.substr(11) << " [" << e.modulo << "] " << e.mensagem << '\n';
    }

    {
        std::ofstream resumo("resumo.txt");
        if (!resumo) {
            std::cerr << "Erro ao abrir resumo.txt para escrita.\n";
            return 1;
        }
        resumo << "Total=" << validas
               << " INFO=" << niveis["INFO"]
               << " WARN=" << niveis["WARN"]
               << " ERROR=" << niveis["ERROR"] << '\n';
        if (!resumo) {
            std::cerr << "Erro ao gravar resumo.txt.\n";
            return 1;
        }
    }
    std::cout << "Resumo gravado em resumo.txt\n";

    std::ifstream leitura("resumo.txt");
    if (!leitura) {
        std::cerr << "Erro ao abrir resumo.txt para leitura.\n";
        return 1;
    }
    std::string primeiraLinha;
    if (std::getline(leitura, primeiraLinha)) {
        std::cout << "Primeira linha do resumo: " << primeiraLinha << '\n';
    }
    return 0;
}