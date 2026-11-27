// Lista de espécies aceitas. É a fonte única: a API valida por ela, a tela monta
// a lista de seleção a partir de GET /api/especies, e o CHECK do banco
// (schema.sql) tem os mesmos códigos.
// "codigo" é o que fica gravado no banco (sem acento, até 20 letras).
#pragma once

#include <string>
#include <vector>

struct Especie {
    std::string codigo;
    std::string nome;
    std::string grupo;
};

inline const std::vector<Especie>& listaEspecies() {
    static const std::vector<Especie> lista = {
        {"cachorro", "Cachorro", "Cães e gatos"},
        {"gato", "Gato", "Cães e gatos"},

        {"coelho", "Coelho", "Pequenos mamíferos"},
        {"hamster", "Hamster", "Pequenos mamíferos"},
        {"porquinho_india", "Porquinho-da-índia", "Pequenos mamíferos"},
        {"chinchila", "Chinchila", "Pequenos mamíferos"},
        {"furao", "Furão", "Pequenos mamíferos"},
        {"rato", "Rato", "Pequenos mamíferos"},
        {"camundongo", "Camundongo", "Pequenos mamíferos"},
        {"gerbil", "Gerbil", "Pequenos mamíferos"},
        {"ourico", "Ouriço-pigmeu", "Pequenos mamíferos"},
        {"petauro", "Petauro-do-açúcar", "Pequenos mamíferos"},

        {"calopsita", "Calopsita", "Aves"},
        {"periquito", "Periquito", "Aves"},
        {"papagaio", "Papagaio", "Aves"},
        {"arara", "Arara", "Aves"},
        {"canario", "Canário", "Aves"},
        {"galinha", "Galinha", "Aves"},
        {"pato", "Pato", "Aves"},
        {"ave", "Outra ave", "Aves"},

        {"cobra", "Cobra", "Répteis"},
        {"lagarto", "Lagarto", "Répteis"},
        {"jabuti", "Jabuti", "Répteis"},
        {"tartaruga", "Tartaruga", "Répteis"},

        {"sapo", "Sapo / rã", "Anfíbios"},
        {"axolote", "Axolote", "Anfíbios"},

        {"peixe", "Peixe", "Peixes"},

        {"aranha", "Aranha", "Aracnídeos e insetos"},
        {"escorpiao", "Escorpião", "Aracnídeos e insetos"},
        {"inseto", "Inseto", "Aracnídeos e insetos"},

        {"cavalo", "Cavalo", "Animais de fazenda"},
        {"burro", "Burro / mula", "Animais de fazenda"},
        {"boi", "Boi / vaca", "Animais de fazenda"},
        {"porco", "Porco", "Animais de fazenda"},
        {"cabra", "Cabra", "Animais de fazenda"},
        {"ovelha", "Ovelha", "Animais de fazenda"},

        {"macaco", "Macaco / sagui", "Silvestres e exóticos"},
        {"capivara", "Capivara", "Silvestres e exóticos"},
        {"gamba", "Gambá", "Silvestres e exóticos"},
        {"silvestre", "Outro animal silvestre", "Silvestres e exóticos"},

        {"outro", "Outro", "Outros"},
    };
    return lista;
}

inline bool especieValida(const std::string& codigo) {
    for (const auto& e : listaEspecies())
        if (e.codigo == codigo) return true;
    return false;
}
