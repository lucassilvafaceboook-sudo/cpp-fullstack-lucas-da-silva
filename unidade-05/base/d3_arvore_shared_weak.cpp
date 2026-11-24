// Atividade D3 - Árvore de tarefas: shared_ptr e weak_ptr sem ciclos
#include <iostream>
#include <memory>
#include <string>
#include <vector>

// TODO: complete a classe Tarefa (construtor e destrutor com mensagens, definirPai, adicionarFilha, caminho)
class Tarefa {
public:
    explicit Tarefa(const std::string& nome) : nome_(nome) {}
    void definirPai(const std::shared_ptr<Tarefa>& pai) { (void)pai; }
    void adicionarFilha(const std::shared_ptr<Tarefa>& filha) { (void)filha; }
    std::string caminho() const { return nome_; }

private:
    std::string nome_;
    std::weak_ptr<Tarefa> pai_;
    std::vector<std::shared_ptr<Tarefa>> filhas_;
};

// TODO: ligar(pai, filha): adicionarFilha no pai e definirPai na filha
void ligar(const std::shared_ptr<Tarefa>& pai, const std::shared_ptr<Tarefa>& filha) {
    (void)pai;
    (void)filha;
}

// TODO (comentário): (a) por que use_count da raiz é 1 e o da etapa é 2?  (b) e se pai_ fosse shared_ptr?

// O main já está pronto: não precisa alterar.
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
