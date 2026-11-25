// Atividade D1 - Projeto da unidade: Cadastro de alunos
//
// (1) Smart pointers vs valores diretos:
// - Valores diretos (std::vector<Aluno>) sao mais simples e eficientes aqui porque Aluno
//   e uma struct pequena, sem polimorfismo e com posse exclusiva pelo vetor; nao ha
//   necessidade de alocacao dinamica individual no heap.
// - Smart pointers (std::unique_ptr<Aluno> ou std::shared_ptr<Aluno>) seriam apropriados
//   se houvesse heranca polimorfica (ex.: AlunoGraduacao, AlunoPos) armazenada em um
//   unico vetor da base, ou se o mesmo objeto Aluno precisasse ser compartilhado entre
//   varias estruturas (como turma e historico) sem duplicacao.
//
// (2) Tres testes de entrada invalida alem dos do main:
// - Aluno{"Lucas", 0, 8.0} -> rejeitado com "Matricula invalida"
// - Aluno{"Lucas", 107, -1.5} -> rejeitado com "Nota fora de 0 a 10"
// - Arquivo com linha "Maria;108" (sem segundo ';') -> carregar falha com "Linha N invalida"

#include <algorithm>
#include <fstream>
#include <iostream>
#include <iterator>
#include <stdexcept>
#include <string>
#include <vector>

namespace cadastro {

struct Aluno {
    std::string nome;
    int matricula;
    double nota;
};

bool validar(const Aluno& aluno, std::string& erro) {
    if (aluno.nome.empty()) {
        erro = "Nome vazio";
        return false;
    }
    if (aluno.matricula <= 0) {
        erro = "Matricula invalida";
        return false;
    }
    if (aluno.nota < 0.0 || aluno.nota > 10.0) {
        erro = "Nota fora de 0 a 10";
        return false;
    }
    erro.clear();
    return true;
}

bool adicionar(std::vector<Aluno>& turma, const Aluno& aluno, std::string& erro) {
    if (!validar(aluno, erro)) {
        return false;
    }
    bool duplicada = std::any_of(turma.begin(), turma.end(), [&](const Aluno& a) {
        return a.matricula == aluno.matricula;
    });
    if (duplicada) {
        erro = "Matricula duplicada";
        return false;
    }
    turma.push_back(aluno);
    return true;
}

void ordenarPorNome(std::vector<Aluno>& turma) {
    std::sort(turma.begin(), turma.end(), [](const Aluno& a, const Aluno& b) {
        return a.nome < b.nome;
    });
}

void ordenarPorNota(std::vector<Aluno>& turma) {
    std::sort(turma.begin(), turma.end(), [](const Aluno& a, const Aluno& b) {
        return a.nota != b.nota ? a.nota > b.nota : a.nome < b.nome;
    });
}

std::vector<Aluno> aprovados(const std::vector<Aluno>& turma, double notaMinima) {
    std::vector<Aluno> resultado;
    std::copy_if(turma.begin(), turma.end(), std::back_inserter(resultado),
                 [notaMinima](const Aluno& a) { return a.nota >= notaMinima; });
    return resultado;
}

void listar(const std::vector<Aluno>& turma) {
    if (turma.empty()) {
        std::cout << "(lista vazia)\n";
        return;
    }
    for (const Aluno& a : turma) {
        std::cout << a.nome << " (mat " << a.matricula << "): " << a.nota << '\n';
    }
}

bool salvar(const std::vector<Aluno>& turma, const std::string& caminho) {
    std::ofstream saida(caminho);
    if (!saida) {
        return false;
    }
    for (const Aluno& a : turma) {
        saida << a.nome << ';' << a.matricula << ';' << a.nota << '\n';
    }
    return static_cast<bool>(saida);
}

bool carregar(std::vector<Aluno>& turma, const std::string& caminho, std::string& erro) {
    turma.clear();
    std::ifstream entrada(caminho);
    if (!entrada) {
        erro = "Arquivo nao encontrado";
        return false;
    }

    std::string linha;
    int numeroLinha{0};
    while (std::getline(entrada, linha)) {
        ++numeroLinha;
        if (!linha.empty() && linha.back() == '\r') {
            linha.pop_back();
        }

        std::size_t p1 = linha.find(';');
        if (p1 == std::string::npos) {
            erro = "Linha " + std::to_string(numeroLinha) + " invalida";
            return false;
        }
        std::size_t p2 = linha.find(';', p1 + 1);
        if (p2 == std::string::npos) {
            erro = "Linha " + std::to_string(numeroLinha) + " invalida";
            return false;
        }

        std::string nome = linha.substr(0, p1);
        std::string matTexto = linha.substr(p1 + 1, p2 - p1 - 1);
        std::string notaTexto = linha.substr(p2 + 1);

        try {
            std::size_t posMat{0};
            std::size_t posNota{0};
            int mat = std::stoi(matTexto, &posMat);
            double nota = std::stod(notaTexto, &posNota);
            if (posMat != matTexto.size() || posNota != notaTexto.size()) {
                erro = "Linha " + std::to_string(numeroLinha) + " invalida";
                return false;
            }
            Aluno aluno{nome, mat, nota};
            std::string erroValidacao;
            if (!validar(aluno, erroValidacao)) {
                erro = "Linha " + std::to_string(numeroLinha) + " invalida";
                return false;
            }
            turma.push_back(aluno);
        } catch (const std::exception&) {
            erro = "Linha " + std::to_string(numeroLinha) + " invalida";
            return false;
        }
    }

    erro.clear();
    return true;
}

}  // namespace cadastro

// O main ja esta pronto: nao precisa alterar.
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