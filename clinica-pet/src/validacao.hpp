// Regras de validação de Tutor, Pet, cadastro de usuário e pedido de atendimento.
// Cada função recebe o JSON do corpo da requisição e devolve:
//   - dados: os campos já limpos (sem espaços nas pontas), como texto
//   - erros: campo -> mensagem (vazio quando está tudo certo)
#pragma once

#include <map>
#include <string>

#include "json.hpp"

// ordered_json mantém os campos na ordem em que foram escritos (id, nome, ...)
using json = nlohmann::ordered_json;

using Dados = std::map<std::string, std::string>;
using Erros = std::map<std::string, std::string>;

struct Validacao {
    Dados dados;
    Erros erros;
    bool ok() const { return erros.empty(); }
};

// Lê um campo do JSON como texto (número vira "28.4", null/ausente vira "")
std::string campoTexto(const json& corpo, const std::string& campo);

Validacao validarTutor(const json& corpo);
Validacao validarPet(const json& corpo);
Validacao validarRegistro(const json& corpo);
Validacao validarAtendimento(const json& corpo);

// Idade em anos e meses a partir do mês/ano de nascimento.
// Devolve null quando não há ano; sem o mês, só os anos.
json calcularIdade(int anoNascimento, int mesNascimento);

// Utilidades usadas também pelas rotas
std::string aparar(const std::string& s);  // tira espaços das pontas
size_t tamanho(const std::string& s);      // quantidade de letras (UTF-8), não de bytes
bool somenteDigitos(const std::string& s);
std::string minusculas(std::string s);
