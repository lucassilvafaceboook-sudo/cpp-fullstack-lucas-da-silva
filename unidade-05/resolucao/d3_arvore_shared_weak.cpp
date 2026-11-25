// Atividade D3 - Arvore de tarefas: shared_ptr e weak_ptr sem ciclos
#include <iostream>
#include <memory>
#include <string>
#include <vector>

class Tarefa {
public:
    explicit Tarefa(const std::string& nome) : nome_(nome) {
        std::cout << "Criando " << nome_ << '\n';
    }
    ~Tarefa() {
        std::cout << "Destruindo " << nome_ << '\n';
    }

    void definirPai(const std::shared_ptr<Tarefa>& pai) { pai_ = pai; }
    void adicionarFilha(const std::shared_ptr<Tarefa>& filha) { filhas_.push_back(filha); }

    std::string caminho() const {
        if (auto p = pai_.lock()) {
            return p->caminho() + "/" + nome_;
        }
        return nome_;
    }

private:
    std::string nome_;
    std::weak_ptr<Tarefa> pai_;
    std::vector<std::shared_ptr<Tarefa>> filhas_;
};

void ligar(const std::shared_ptr<Tarefa>& pai, const std::shared_ptr<Tarefa>& filha) {
    pai->adicionarFilha(filha);
    filha->definirPai(pai);
}

// (a) A raiz tem use_count = 1 porque apenas a variavel local 'raiz' possui posse forte
//     sobre ela (o pai_ da etapa e weak_ptr e nao incrementa a contagem). Ja 'etapa' tem
//     use_count = 2 porque tem dois donos fortes: a variavel local 'etapa' e o vetor
//     filhas_ da raiz.
// (b) Se pai_ fosse shared_ptr, raiz apontaria para etapa e etapa apontaria para raiz
//     (ciclo de referencias). Ao fim do bloco, as contagens nunca chegariam a zero e
//     nenhuma tarefa seria destruida (vazamento de memoria).

// O main ja esta pronto: nao precisa alterar.
int main() {
    {
        auto raiz = std::make_shared<Tarefa>("Projeto");
        auto etapa = std::make_shared<Tarefa>("Etapa1");
        auto passo = std::make_shared<Tarefa>("Passo1");
        ligar(raiz, etapa);
        ligar(etapa, passo);

        std::cout << "Caminho: " << passo->caminho() << '\n';
        std::cout << "use_count raiz: " << raiz.use_count() << '\n';
        std::cout << "use_count etapa: " << etapa.use_count() << '\n';
        std::cout << "use_count passo: " << passo.use_count() << '\n';

        std::weak_ptr<Tarefa> observador = passo;
        passo.reset();
        std::cout << "Passo ainda vivo: " << (observador.expired() ? "nao" : "sim") << '\n';
    }
    std::cout << "Fim do bloco\n";
    return 0;
}