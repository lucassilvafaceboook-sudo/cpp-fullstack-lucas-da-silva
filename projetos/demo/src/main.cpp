// main.cpp - Ponto de entrada do servidor: monta as rotas e fica escutando requisições.
//
// Uso:  servidor.exe [porta]        (padrão: 8080, ou a variável de ambiente PORTA)
// Depois abra  http://localhost:8080  no navegador.

#include <cstdlib>
#include <exception>
#include <iostream>
#include <string>

#include <httplib.h>
#include <nlohmann/json.hpp>

#include "banco.hpp"
#include "config.hpp"
#include "http_util.hpp"
#include "rotas_projetos.hpp"
#include "rotas_tarefas.hpp"
// Quando criar as rotas do seu tema, inclua o cabeçalho aqui e registre abaixo.

int main(int argc, char* argv[]) {
    Config config = Config::doAmbiente();
    if (argc > 1) {
        char* fim = nullptr;
        long porta = std::strtol(argv[1], &fim, 10);
        if (fim != argv[1] && *fim == '\0' && porta > 0 && porta < 65536) {
            config.portaServidor = static_cast<int>(porta);
        } else {
            std::cerr << "Porta invalida: " << argv[1] << '\n';
            return 1;
        }
    }

    iniciarBiblioteca();

    // Teste rápido de conexão, só para avisar cedo se o banco não estiver no ar.
    // (O servidor sobe mesmo assim: as rotas abrem a própria conexão a cada requisição.)
    try {
        Conexao teste(config);
        std::cout << "Banco OK: " << config.usuario << "@" << config.host << ":" << config.porta << "/"
                  << config.banco << std::endl;
    } catch (const std::exception& erro) {
        std::cerr << "AVISO: " << erro.what() << '\n'
                  << "  -> O container do banco esta no ar? Rode: docker compose up -d --wait\n";
    }

    httplib::Server servidor;

    // Front-end: tudo que estiver em ./public vira acessível pelo navegador (index.html, estilo.css, app.js...).
    // Execute o servidor a partir da pasta do starter-kit para que "./public" seja encontrada.
    if (!servidor.set_mount_point("/", "./public")) {
        std::cerr << "AVISO: pasta ./public nao encontrada. Execute o servidor na pasta do projeto.\n";
    }

    // Rotas de saúde: úteis para testar rapidamente.
    servidor.Get("/api/saude", [](const httplib::Request&, httplib::Response& res) {
        util::enviarJson(res, {{"status", "ok"}});
    });
    servidor.Get("/api/saude/banco", [&config](const httplib::Request&, httplib::Response& res) {
        util::comBanco(config, res, [&](Conexao& banco) {
            banco.consultar("SELECT 1");
            util::enviarJson(res, {{"banco", "ok"}});
        });
    });

    // Rotas do demo: projetos (apoio) e tarefas (principal).
    registrarRotasProjetos(servidor, config);
    registrarRotasTarefas(servidor, config);

    // Qualquer exceção não tratada dentro de uma rota vira um 500 em JSON (e o servidor continua de pé).
    servidor.set_exception_handler(
        [](const httplib::Request&, httplib::Response& res, std::exception_ptr ep) {
            try {
                if (ep) {
                    std::rethrow_exception(ep);
                }
            } catch (const std::exception& erro) {
                std::cerr << "[excecao] " << erro.what() << '\n';
            } catch (...) {
                std::cerr << "[excecao desconhecida]\n";
            }
            util::enviarErro(res, 500, "Erro interno do servidor");
        });

    // Rota inexistente dentro de /api responde JSON; fora de /api, o padrão (404 em HTML).
    servidor.set_error_handler([](const httplib::Request& req, httplib::Response& res) {
        if (req.path.rfind("/api/", 0) == 0 && res.status == 404 && res.body.empty()) {
            util::enviarErro(res, 404, "Rota nao encontrada");
        }
    });

    // Escutamos só em 127.0.0.1: apenas este computador acessa. (Para a rede toda, use "0.0.0.0".)
    std::cout << "Servidor em http://localhost:" << config.portaServidor << "  (Ctrl+C para parar)" << std::endl;
    if (!servidor.listen("127.0.0.1", config.portaServidor)) {
        std::cerr << "ERRO: nao foi possivel usar a porta " << config.portaServidor
                  << ". Ja existe outro servidor rodando? Tente: servidor.exe 8081\n";
        return 1;
    }
    return 0;
}
