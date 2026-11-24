// Atividade D1 - Projeto da unidade: Cadastro de alunos
//
// TODO: documente aqui (1) onde smart pointers seriam apropriados e onde valores diretos são mais simples
//       e (2) três testes de entrada inválida.
#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

namespace cadastro {

struct Aluno {
    std::string nome;
    int matricula;
    double nota;
};

// TODO: implemente todas as funções abaixo (hoje são apenas esqueletos que compilam)
bool validar(const Aluno& aluno, std::string& erro) {
    (void)aluno;
    erro.clear();
    return true;
}

bool adicionar(std::vector<Aluno>& turma, const Aluno& aluno, std::string& erro) {
    (void)turma;
    (void)aluno;
    (void)erro;
    return false;
}

void ordenarPorNome(std::vector<Aluno>& turma) { (void)turma; }
void ordenarPorNota(std::vector<Aluno>& turma) { (void)turma; }

std::vector<Aluno> aprovados(const std::vector<Aluno>& turma, double notaMinima) {
    (void)turma;
    (void)notaMinima;
    return {};
}

void listar(const std::vector<Aluno>& turma) { (void)turma; }

bool salvar(const std::vector<Aluno>& turma, const std::string& caminho) {
    (void)turma;
    (void)caminho;
    return false;
}

bool carregar(std::vector<Aluno>& turma, const std::string& caminho, std::string& erro) {
    (void)turma;
    (void)caminho;
    (void)erro;
    return false;
}

}  // namespace cadastro

// O main já está pronto: não precisa alterar.
int main() {
    std::vector<cadastro::Aluno> turma;
    std::string erro;

    std::cout << "== Turma vazia ==\n";
    cadastro::listar(turma);

    std::cout << "== Cadastro ==\n";
    const cadastro::Aluno entradas[]{{"Carla", 103, 6.0}, {"Ana", 101, 8.5}, {"Bruno", 102, 4.5}, {"Davi", 104, 9.5},
                                     {"", 105, 7.0},      {"Elisa", 101, 7.0}, {"Fabio", 106, 11.0}};
    for (const cadastro::Aluno& aluno : entradas) {
        if (cadastro::adicionar(turma, aluno, erro)) {
            std::cout << "Adicionado: " << aluno.nome << '\n';
        } else {
            std::cout << "Rejeitado: " << erro << '\n';
        }
    }

    std::cout << "== Por nome ==\n";
    cadastro::ordenarPorNome(turma);
    cadastro::listar(turma);

    std::cout << "== Por nota (maior primeiro) ==\n";
    cadastro::ordenarPorNota(turma);
    cadastro::listar(turma);

    std::cout << "== Aprovados (nota >= 6) ==\n";
    cadastro::listar(cadastro::aprovados(turma, 6.0));

    std::cout << "== Arquivo ==\n";
    if (cadastro::salvar(turma, "turma.txt")) {
        std::cout << "Salvo: turma.txt (" << turma.size() << " registro(s))\n";
    } else {
        std::cout << "Erro ao salvar\n";
    }
    std::vector<cadastro::Aluno> carregada;
    if (cadastro::carregar(carregada, "turma.txt", erro)) {
        std::cout << "Carregados: " << carregada.size() << " registro(s)\n";
        cadastro::listar(carregada);
    } else {
        std::cout << "Erro ao carregar: " << erro << '\n';
    }
    if (!cadastro::carregar(carregada, "nao_existe.txt", erro)) {
        std::cout << "Erro ao carregar: " << erro << '\n';
    }
    {
        std::ofstream ruim("ruim.txt");
        ruim << "Ana;abc;7\n";
    }
    if (!cadastro::carregar(carregada, "ruim.txt", erro)) {
        std::cout << "Erro ao carregar: " << erro << '\n';
    }
    return 0;
}
