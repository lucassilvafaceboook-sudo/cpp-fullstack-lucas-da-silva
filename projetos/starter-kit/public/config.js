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
  titulo: "Recados",
  recurso: "recados", // usa as rotas /api/recados
  campos: [
    { nome: "titulo", rotulo: "Título", tipo: "texto", obrigatorio: true, max: 100 },
    { nome: "prioridade", rotulo: "Prioridade (1 a 5)", tipo: "numero", min: 1, max: 5, padrao: 1 },
    { nome: "mensagem", rotulo: "Mensagem", tipo: "textarea", largo: true },
    { nome: "criado_em", rotulo: "Criado em", tipo: "somenteLeitura" },
  ],
  // Opcional: links de navegação entre as telas do sistema.
  // menu: [
  //   { texto: "Recados", href: "index.html" },
  //   { texto: "Outra tela", href: "outra.html" },
  // ],
};
