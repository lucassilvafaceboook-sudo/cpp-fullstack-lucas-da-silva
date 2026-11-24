"use strict";
/*
 * config-projetos.js - Configuração da tela de PROJETOS (entidade de apoio do demo).
 * É a mesma ideia do config.js (veja a documentação de todas as opções lá): outro CONFIG, o mesmo app.js.
 * A página é projetos.html, que é uma cópia do index.html apontando para ESTE arquivo.
 */

const CONFIG = {
  titulo: "Projetos",
  recurso: "projetos", // usa as rotas /api/projetos
  semEditar: true, // a API de projetos não tem PUT (de propósito: é só a entidade de apoio)
  campos: [
    { nome: "nome", rotulo: "Nome", tipo: "texto", obrigatorio: true, max: 80 },
    { nome: "descricao", rotulo: "Descrição", tipo: "textarea", max: 255, largo: true },
    { nome: "total_tarefas", rotulo: "Tarefas", tipo: "somenteLeitura" },
  ],
  menu: [
    { texto: "Tarefas", href: "index.html" },
    { texto: "Projetos", href: "projetos.html" },
    { texto: "Resumo", href: "resumo.html" },
  ],
};
