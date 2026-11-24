"use strict";
/*
 * config.js - A ÚNICA parte do front-end que a equipe precisa editar para mudar de tema.
 * O app.js lê o CONFIG abaixo e monta a tela (tabela, formulário, busca, botões) sozinho.
 *
 * Tipos de campo aceitos em "tipo":
 *   "texto"         linha de texto            (opções: max = tamanho máximo)
 *   "textarea"      texto longo               (opções: max = tamanho máximo)
 *   "numero"        número inteiro            (opções: min, max)
 *   "decimal"       número com casas decimais (opções: min, max, passo, formato: "moeda")
 *   "data"          data (AAAA-MM-DD)
 *   "select"        lista de opções           (opções: opcoes: [{valor, rotulo}]
 *                                              ou opcoesDe: {recurso, valor, rotulo} para buscar na API)
 *   "somenteLeitura" aparece na tabela, mas não no formulário (ex.: data de criação)
 * Opções comuns: obrigatorio (true/false), padrao (valor inicial), largo (ocupa a linha toda),
 *   rotuloTabela (título mais curto para a coluna da tabela, quando o rótulo do formulário é longo).
 *
 * Opções do CONFIG:
 *   semEditar: true / semExcluir: true   escondem os botões da tabela quando a API ainda não tem PUT / DELETE.
 *   classeLinha: (registro) => "linha-alerta"   devolve uma classe CSS para destacar a linha
 *                                               (prontas: "linha-alerta" e "linha-apagada"; veja o estilo.css).
 *   acoesExtras: [{ rotulo, caminho: (registro) => "/api/.../acao", metodo: "POST", mensagem, mostrarSe: (registro) => bool }]
 *                                               botões extras na linha que chamam uma rota da API.
 *   filtros: [{ nome: "status", rotulo: "Status", opcoes: [{valor, rotulo}] }  (ou opcoesDe: {recurso, valor, rotulo})]
 *                                               listas de filtro ao lado da busca; cada uma envia ?nome=valor à API.
 * No campo "decimal" use casas: N para escolher quantas casas decimais aparecem na tabela (padrão 2).
 *
 * Várias telas: copie index.html para outro arquivo (ex.: autores.html), troque nele o
 *   <script src="config.js"> por um novo arquivo de configuração (ex.: config-autores.js)
 * e use "menu" para ligar as páginas entre si.
 */

const CONFIG = {
  titulo: "Tarefas",
  recurso: "tarefas", // usa as rotas /api/tarefas
  campos: [
    { nome: "projeto_id", rotulo: "Projeto", tipo: "select", obrigatorio: true,
      opcoesDe: { recurso: "projetos", valor: "id", rotulo: "nome" } },
    { nome: "titulo", rotulo: "Título", tipo: "texto", obrigatorio: true, max: 100 },
    { nome: "status", rotulo: "Status", tipo: "select", padrao: "pendente",
      opcoes: [
        { valor: "pendente", rotulo: "Pendente" },
        { valor: "andamento", rotulo: "Em andamento" },
        { valor: "feito", rotulo: "Feito" },
      ] },
    { nome: "prioridade", rotulo: "Prioridade (1 = urgente, 5 = tranquila)", rotuloTabela: "Prioridade", tipo: "numero", min: 1, max: 5, padrao: 3 },
    { nome: "prazo", rotulo: "Prazo", tipo: "data" },
    { nome: "horas_estimadas", rotulo: "Horas estimadas", tipo: "decimal", min: 0, passo: 0.5, casas: 1 },
    { nome: "descricao", rotulo: "Descrição", tipo: "textarea", largo: true },
    { nome: "concluida_em", rotulo: "Concluída em", tipo: "somenteLeitura" },
  ],
  // Passo 5: listas de filtro ao lado da busca (a API filtra com ?status=...&projeto_id=...).
  filtros: [
    {
      nome: "status", rotulo: "Status",
      opcoes: [
        { valor: "pendente", rotulo: "Pendente" },
        { valor: "andamento", rotulo: "Em andamento" },
        { valor: "feito", rotulo: "Feito" },
      ],
    },
    { nome: "projeto_id", rotulo: "Projeto", opcoesDe: { recurso: "projetos", valor: "id", rotulo: "nome" } },
  ],
  // Passo 5: tarefa atrasada (não feita e com prazo vencido) fica vermelha; tarefa feita fica apagada.
  classeLinha: (tarefa) => {
    if (tarefa.status === "feito") return "linha-apagada";
    if (tarefa.prazo && tarefa.prazo < hoje()) return "linha-alerta";
    return null;
  },
  // Passo 5: botão "Concluir" na linha, que chama POST /api/tarefas/:id/concluir.
  acoesExtras: [
    {
      rotulo: "Concluir", metodo: "POST", mensagem: "Tarefa concluída.",
      caminho: (tarefa) => "/api/tarefas/" + tarefa.id + "/concluir",
      mostrarSe: (tarefa) => tarefa.status !== "feito",
    },
  ],
  menu: [
    { texto: "Tarefas", href: "index.html" },
    { texto: "Projetos", href: "projetos.html" },
    { texto: "Resumo", href: "resumo.html" },
  ],
};

// Data de hoje no formato AAAA-MM-DD (hora local), para comparar com o campo "prazo".
function hoje() {
  const agora = new Date();
  const dois = (n) => String(n).padStart(2, "0");
  return agora.getFullYear() + "-" + dois(agora.getMonth() + 1) + "-" + dois(agora.getDate());
}
