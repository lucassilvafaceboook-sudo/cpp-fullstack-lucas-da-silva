// Cadastro, login e controle de acesso.
// - Senhas: scrypt com sal aleatório (OpenSSL). No banco fica "sal:hash", nunca a senha.
// - Sessão: token aleatório entregue ao navegador; no banco fica só o SHA-256 dele.
// - Papéis: "cliente" (dono de pet, só vê os próprios pets) e "veterinario" (vê tudo).
#pragma once

#include <optional>
#include <string>

#include "httplib.h"
#include "validacao.hpp"  // tipo json

struct Usuario {
    long long id = 0;
    std::string nome;
    std::string email;
    std::string papel;   // "cliente" ou "veterinario"
    long long tutorId = 0; // só clientes têm (0 = nenhum)
    std::string token;   // token da sessão atual

    bool ehVet() const { return papel == "veterinario"; }
    json paraJson() const;
};

// Código que a clínica passa aos veterinários para eles conseguirem se cadastrar.
// Vem da variável de ambiente CODIGO_CLINICA (padrão de desenvolvimento: "vet-2026").
std::string codigoClinica();

std::string gerarHashSenha(const std::string& senha);
bool senhaConfere(const std::string& senha, const std::string& guardado);

std::string criarSessao(long long usuarioId);  // devolve o token
void encerrarSessao(const std::string& token);

// Lê o token do cabeçalho "Authorization: Bearer ..." e busca o usuário.
// Se não estiver logado, já responde 401 e devolve std::nullopt.
std::optional<Usuario> exigirLogin(const httplib::Request& req, httplib::Response& res);

// Igual a exigirLogin, mas também exige veterinário (senão responde 403)
std::optional<Usuario> exigirVet(const httplib::Request& req, httplib::Response& res);
