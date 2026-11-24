"use strict";
/*
 * app.js - Front-end de um CRUD completo (listar, buscar, criar, editar, excluir).
 *
 * Este arquivo é GENÉRICO: ele lê a variável CONFIG, definida em config.js (carregado antes
 * deste arquivo no HTML), e monta a tela a partir dela. Para o seu tema, edite o config.js.
 * Mexa neste arquivo só se precisar de um comportamento novo.
 */

const API = "/api/" + CONFIG.recurso;

const el = {
  titulo: document.getElementById("titulo-pagina"),
  tituloFormulario: document.getElementById("titulo-formulario"),
  formulario: document.getElementById("formulario"),
  formBusca: document.getElementById("form-busca"),
  busca: document.getElementById("busca"),
  limparBusca: document.getElementById("limpar-busca"),
  cabecalho: document.querySelector("#tabela thead"),
  corpo: document.querySelector("#tabela tbody"),
  vazio: document.getElementById("vazio"),
  aviso: document.getElementById("aviso"),
  menu: document.getElementById("menu"),
};

let editandoId = null; // null = criando; número = editando esse id
let termoBusca = "";
const opcoesDosSelects = {}; // nome do campo -> [{valor, rotulo}]
let temporizadorAviso = null;
let botaoSalvar = null;

/* ------------------------------------ acesso à API ------------------------------------ */

async function api(metodo, url, corpo) {
  const opcoes = { method: metodo, headers: {} };
  if (corpo !== undefined) {
    opcoes.headers["Content-Type"] = "application/json";
    opcoes.body = JSON.stringify(corpo);
  }

  let resposta;
  try {
    resposta = await fetch(url, opcoes);
  } catch (e) {
    throw new Error("Não foi possível falar com o servidor. Ele está rodando?");
  }

  if (resposta.status === 204) {
    return null; // sem conteúdo (ex.: DELETE)
  }

  let dados = null;
  try {
    dados = await resposta.json();
  } catch (e) {
    /* resposta sem JSON */
  }

  if (!resposta.ok) {
    let mensagem = (dados && dados.erro) || "Erro " + resposta.status;
    if (dados && Array.isArray(dados.detalhes)) {
      mensagem += ":\n- " + dados.detalhes.join("\n- ");
    }
    throw new Error(mensagem);
  }
  return dados;
}

/* ------------------------------------ mensagens ------------------------------------ */

function mostrarAviso(texto, tipo) {
  clearTimeout(temporizadorAviso);
  el.aviso.textContent = texto; // textContent: nunca interpreta HTML
  el.aviso.className = "aviso " + tipo;
  el.aviso.hidden = false;
  if (tipo === "ok") {
    temporizadorAviso = setTimeout(() => (el.aviso.hidden = true), 4000);
  }
}

/* ------------------------------------ formulário ------------------------------------ */

function camposEditaveis() {
  return CONFIG.campos.filter((c) => c.tipo !== "somenteLeitura");
}

function criarControle(campo) {
  let controle;
  if (campo.tipo === "textarea") {
    controle = document.createElement("textarea");
  } else if (campo.tipo === "select") {
    controle = document.createElement("select");
  } else {
    controle = document.createElement("input");
    controle.type = { texto: "text", numero: "number", decimal: "number", data: "date" }[campo.tipo] || "text";
  }
  controle.id = "campo-" + campo.nome;
  controle.name = campo.nome;

  if (campo.tipo === "numero") controle.step = "1";
  if (campo.tipo === "decimal") controle.step = campo.passo || "0.01";
  if (campo.min !== undefined) controle.min = campo.min;
  if (campo.max !== undefined) {
    if (campo.tipo === "texto" || campo.tipo === "textarea") controle.maxLength = campo.max;
    else controle.max = campo.max;
  }
  return controle;
}

function construirFormulario() {
  el.formulario.textContent = "";

  for (const campo of camposEditaveis()) {
    const grupo = document.createElement("div");
    grupo.className = "campo" + (campo.largo ? " largo" : "");

    const rotulo = document.createElement("label");
    rotulo.htmlFor = "campo-" + campo.nome;
    rotulo.textContent = campo.rotulo;
    if (campo.obrigatorio) {
      const marca = document.createElement("span");
      marca.className = "obrigatorio";
      marca.textContent = " *";
      rotulo.appendChild(marca);
    }

    grupo.append(rotulo, criarControle(campo));
    el.formulario.appendChild(grupo);
  }

  const acoes = document.createElement("div");
  acoes.className = "acoes";

  botaoSalvar = document.createElement("button");
  botaoSalvar.type = "submit";
  botaoSalvar.textContent = "Salvar";

  const cancelar = document.createElement("button");
  cancelar.type = "button";
  cancelar.className = "secundario";
  cancelar.textContent = "Cancelar";
  cancelar.addEventListener("click", reiniciarFormulario);

  acoes.append(botaoSalvar, cancelar);
  el.formulario.appendChild(acoes);
}

function preencherSelect(campo) {
  const select = document.getElementById("campo-" + campo.nome);
  select.textContent = "";
  const vazio = document.createElement("option");
  vazio.value = "";
  vazio.textContent = "Selecione...";
  select.appendChild(vazio);
  for (const opcao of opcoesDosSelects[campo.nome] || []) {
    const item = document.createElement("option");
    item.value = String(opcao.valor);
    item.textContent = opcao.rotulo;
    select.appendChild(item);
  }
}

/* ------------------------------------ filtros ------------------------------------ */

// Se o config.js tiver "filtros", cria uma lista de escolha para cada um, ao lado da busca.
function construirFiltros() {
  for (const filtro of CONFIG.filtros || []) {
    const select = document.createElement("select");
    select.id = "filtro-" + filtro.nome;
    select.setAttribute("aria-label", "Filtrar por " + filtro.rotulo);
    select.addEventListener("change", carregar);
    el.formBusca.insertBefore(select, el.busca);
    preencherFiltro(filtro, []);
  }
}

function preencherFiltro(filtro, opcoes) {
  const select = document.getElementById("filtro-" + filtro.nome);
  select.textContent = "";
  const todos = document.createElement("option");
  todos.value = "";
  todos.textContent = filtro.rotulo + ": todos";
  select.appendChild(todos);
  for (const opcao of opcoes) {
    const item = document.createElement("option");
    item.value = String(opcao.valor);
    item.textContent = opcao.rotulo;
    select.appendChild(item);
  }
}

async function carregarFiltros() {
  for (const filtro of CONFIG.filtros || []) {
    let opcoes = filtro.opcoes || [];
    if (filtro.opcoesDe) {
      const origem = filtro.opcoesDe;
      const itens = await api("GET", "/api/" + origem.recurso);
      opcoes = itens.map((item) => ({ valor: item[origem.valor || "id"], rotulo: String(item[origem.rotulo]) }));
    }
    preencherFiltro(filtro, opcoes);
  }
}

async function carregarOpcoes() {
  for (const campo of CONFIG.campos.filter((c) => c.tipo === "select")) {
    if (campo.opcoes) {
      opcoesDosSelects[campo.nome] = campo.opcoes;
    } else if (campo.opcoesDe) {
      const origem = campo.opcoesDe;
      const itens = await api("GET", "/api/" + origem.recurso);
      opcoesDosSelects[campo.nome] = itens.map((item) => ({
        valor: item[origem.valor || "id"],
        rotulo: String(item[origem.rotulo]),
      }));
    }
    if (campo.tipo === "select" && document.getElementById("campo-" + campo.nome)) {
      preencherSelect(campo);
    }
  }
}

function valorInicial(campo) {
  return campo.padrao !== undefined ? String(campo.padrao) : "";
}

function reiniciarFormulario() {
  editandoId = null;
  el.tituloFormulario.textContent = "Novo registro";
  for (const campo of camposEditaveis()) {
    document.getElementById("campo-" + campo.nome).value = valorInicial(campo);
  }
}

function preencherFormulario(registro) {
  for (const campo of camposEditaveis()) {
    const controle = document.getElementById("campo-" + campo.nome);
    const valor = registro[campo.nome];
    if (valor === null || valor === undefined) {
      controle.value = "";
    } else if (campo.tipo === "data") {
      controle.value = String(valor).slice(0, 10);
    } else {
      controle.value = String(valor);
    }
  }
}

// Lê os campos e monta o objeto que será enviado como JSON.
function lerFormulario() {
  const dados = {};
  for (const campo of camposEditaveis()) {
    const bruto = document.getElementById("campo-" + campo.nome).value.trim();
    if (campo.tipo === "numero" || campo.tipo === "decimal") {
      dados[campo.nome] = bruto === "" ? null : Number(bruto);
    } else if (campo.tipo === "select") {
      const opcao = (opcoesDosSelects[campo.nome] || []).find((o) => String(o.valor) === bruto);
      dados[campo.nome] = opcao ? opcao.valor : null; // devolve o valor original (número ou texto)
    } else if (campo.tipo === "data") {
      dados[campo.nome] = bruto === "" ? null : bruto;
    } else {
      dados[campo.nome] = bruto;
    }
  }
  return dados;
}

// Validação mínima no navegador. A validação "de verdade" é a da API (resposta 422).
function validar(dados) {
  const problemas = [];
  for (const campo of camposEditaveis()) {
    const valor = dados[campo.nome];
    const vazio = valor === null || valor === "";
    if (campo.obrigatorio && vazio) {
      problemas.push(campo.rotulo + " é obrigatório");
    }
    if (typeof valor === "number" && Number.isNaN(valor)) {
      problemas.push(campo.rotulo + " deve ser um número");
    }
  }
  return problemas;
}

async function aoEnviar(evento) {
  evento.preventDefault();
  const dados = lerFormulario();
  const problemas = validar(dados);
  if (problemas.length > 0) {
    mostrarAviso("Corrija antes de salvar:\n- " + problemas.join("\n- "), "erro");
    return;
  }

  botaoSalvar.disabled = true;
  try {
    if (editandoId === null) {
      await api("POST", API, dados);
      mostrarAviso("Registro criado.", "ok");
    } else {
      await api("PUT", API + "/" + editandoId, dados);
      mostrarAviso("Registro atualizado.", "ok");
    }
    reiniciarFormulario();
    await carregar();
  } catch (erro) {
    mostrarAviso(erro.message, "erro");
  } finally {
    botaoSalvar.disabled = false;
  }
}

/* ------------------------------------ tabela ------------------------------------ */

function formatar(campo, valor) {
  if (valor === null || valor === undefined || valor === "") return "—";
  if (campo.tipo === "select") {
    const opcao = (opcoesDosSelects[campo.nome] || []).find((o) => o.valor === valor);
    return opcao ? opcao.rotulo : String(valor);
  }
  if (campo.tipo === "decimal") {
    const numero = Number(valor);
    const opcoes =
      campo.formato === "moeda"
        ? { style: "currency", currency: "BRL" }
        : { minimumFractionDigits: campo.casas ?? 2, maximumFractionDigits: campo.casas ?? 2 };
    return numero.toLocaleString("pt-BR", opcoes);
  }
  if (campo.tipo === "data") {
    const [ano, mes, dia] = String(valor).slice(0, 10).split("-");
    return dia + "/" + mes + "/" + ano;
  }
  // Data e hora que vêm do banco ("2026-11-20 14:42:50"), por exemplo em criado_em: mostra "20/11/2026 14:42".
  const dataHora = /^(\d{4})-(\d{2})-(\d{2}) (\d{2}:\d{2})(:\d{2})?$/.exec(String(valor));
  if (dataHora) {
    return dataHora[3] + "/" + dataHora[2] + "/" + dataHora[1] + " " + dataHora[4];
  }
  return String(valor);
}

function construirCabecalho() {
  const linha = document.createElement("tr");
  // rotuloTabela (opcional) é um título mais curto para a coluna, quando o rótulo do formulário é longo.
  const colunas = ["ID", ...CONFIG.campos.map((c) => c.rotuloTabela || c.rotulo), "Ações"];
  for (const texto of colunas) {
    const th = document.createElement("th");
    th.textContent = texto;
    linha.appendChild(th);
  }
  el.cabecalho.textContent = "";
  el.cabecalho.appendChild(linha);
}

function desenharTabela(registros) {
  el.corpo.textContent = "";
  el.vazio.hidden = registros.length > 0;

  for (const registro of registros) {
    const linha = document.createElement("tr");
    // classeLinha(registro) (no config.js) pode devolver uma classe CSS, ex.: "linha-alerta" ou "linha-apagada".
    if (typeof CONFIG.classeLinha === "function") {
      const classe = CONFIG.classeLinha(registro);
      if (classe) linha.className = classe;
    }

    const celulaId = document.createElement("td");
    celulaId.textContent = registro.id;
    linha.appendChild(celulaId);

    for (const campo of CONFIG.campos) {
      const celula = document.createElement("td");
      if (campo.tipo === "numero" || campo.tipo === "decimal") celula.className = "num";
      celula.textContent = formatar(campo, registro[campo.nome]); // textContent evita XSS
      linha.appendChild(celula);
    }

    const celulaAcoes = document.createElement("td");
    celulaAcoes.className = "acoes-linha";

    const editar = document.createElement("button");
    editar.type = "button";
    editar.className = "secundario";
    editar.textContent = "Editar";
    editar.addEventListener("click", () => iniciarEdicao(registro));

    const excluir = document.createElement("button");
    excluir.type = "button";
    excluir.className = "perigo";
    excluir.textContent = "Excluir";
    excluir.addEventListener("click", () => excluirRegistro(registro));

    // acoesExtras (no config.js): botões a mais na linha, que chamam uma rota da API (ex.: "Concluir").
    for (const acao of CONFIG.acoesExtras || []) {
      if (typeof acao.mostrarSe === "function" && !acao.mostrarSe(registro)) continue;
      const botao = document.createElement("button");
      botao.type = "button";
      botao.textContent = acao.rotulo;
      botao.addEventListener("click", () => executarAcaoExtra(acao, registro));
      celulaAcoes.appendChild(botao);
    }

    // semEditar / semExcluir (no config.js) escondem os botões quando a API não tem essas rotas.
    if (!CONFIG.semEditar) celulaAcoes.appendChild(editar);
    if (!CONFIG.semExcluir) celulaAcoes.appendChild(excluir);
    linha.appendChild(celulaAcoes);
    el.corpo.appendChild(linha);
  }
}

async function carregar() {
  try {
    // Monta a consulta: ?busca=texto&status=feito (cada filtro escolhido vira um parâmetro; "todos" não envia nada).
    const parametros = new URLSearchParams();
    if (termoBusca) parametros.set("busca", termoBusca);
    for (const filtro of CONFIG.filtros || []) {
      const valor = document.getElementById("filtro-" + filtro.nome).value;
      if (valor) parametros.set(filtro.nome, valor);
    }
    const consulta = parametros.toString();
    desenharTabela(await api("GET", consulta ? API + "?" + consulta : API));
  } catch (erro) {
    mostrarAviso(erro.message, "erro");
  }
}

function iniciarEdicao(registro) {
  editandoId = registro.id;
  el.tituloFormulario.textContent = "Editar registro #" + registro.id;
  preencherFormulario(registro);
  el.formulario.scrollIntoView({ behavior: "smooth", block: "center" });
  const primeiro = camposEditaveis()[0];
  if (primeiro) document.getElementById("campo-" + primeiro.nome).focus();
}

async function executarAcaoExtra(acao, registro) {
  try {
    await api(acao.metodo || "POST", acao.caminho(registro));
    mostrarAviso(acao.mensagem || "Ação executada.", "ok");
    await carregar();
  } catch (erro) {
    mostrarAviso(erro.message, "erro");
  }
}

async function excluirRegistro(registro) {
  if (!window.confirm("Excluir o registro #" + registro.id + "?")) return;
  try {
    await api("DELETE", API + "/" + registro.id);
    if (editandoId === registro.id) reiniciarFormulario();
    mostrarAviso("Registro excluído.", "ok");
    await carregar();
  } catch (erro) {
    mostrarAviso(erro.message, "erro");
  }
}

/* ------------------------------------ menu ------------------------------------ */

// Se o config.js tiver "menu", mostra os links de navegação entre as telas.
function construirMenu() {
  if (!Array.isArray(CONFIG.menu) || CONFIG.menu.length === 0) return;
  const paginaAtual = location.pathname.split("/").pop() || "index.html";
  for (const item of CONFIG.menu) {
    const link = document.createElement("a");
    link.href = item.href;
    link.textContent = item.texto;
    if (item.href === paginaAtual) link.setAttribute("aria-current", "page");
    el.menu.appendChild(link);
  }
  el.menu.hidden = false;
}

/* ------------------------------------ início ------------------------------------ */

async function iniciar() {
  document.title = CONFIG.titulo + " - Projeto ITEAM";
  el.titulo.textContent = CONFIG.titulo;

  construirMenu();
  construirFormulario();
  construirFiltros();
  construirCabecalho();
  reiniciarFormulario();

  el.formulario.addEventListener("submit", aoEnviar);
  el.formBusca.addEventListener("submit", (evento) => {
    evento.preventDefault();
    termoBusca = el.busca.value.trim();
    carregar();
  });
  el.limparBusca.addEventListener("click", () => {
    el.busca.value = "";
    termoBusca = "";
    for (const filtro of CONFIG.filtros || []) {
      document.getElementById("filtro-" + filtro.nome).value = "";
    }
    carregar();
  });

  try {
    await carregarOpcoes();
    await carregarFiltros();
  } catch (erro) {
    mostrarAviso("Não foi possível carregar as opções das listas: " + erro.message, "erro");
  }
  reiniciarFormulario(); // de novo: agora que as listas têm opções, aplica o "padrao" dos campos select
  await carregar();
}

iniciar();
