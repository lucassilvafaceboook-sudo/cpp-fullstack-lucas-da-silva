"use strict";
/*
 * resumo.js - Página de resumo: busca GET /api/tarefas/resumo e desenha indicadores e barras de progresso.
 *
 * Passo a passo (o mesmo de qualquer página que consome uma rota da API):
 *   1) fetch na rota        2) converter a resposta para JSON        3) criar elementos e preencher com textContent
 */

const elementos = {
  aviso: document.getElementById("aviso"),
  indicadores: document.getElementById("indicadores"),
  projetos: document.getElementById("projetos"),
};

function mostrarErro(texto) {
  elementos.aviso.textContent = texto; // textContent: nunca interpreta HTML
  elementos.aviso.className = "aviso erro";
  elementos.aviso.hidden = false;
}

// Cria <div class="indicador"><span class="valor">12</span><span class="rotulo">Tarefas</span></div>
function criarIndicador(valor, rotulo, classeExtra) {
  const caixa = document.createElement("div");
  caixa.className = "indicador" + (classeExtra ? " " + classeExtra : "");
  const numero = document.createElement("span");
  numero.className = "valor";
  numero.textContent = valor;
  const legenda = document.createElement("span");
  legenda.className = "rotulo";
  legenda.textContent = rotulo;
  caixa.append(numero, legenda);
  return caixa;
}

function desenharIndicadores(resumo) {
  const horas = Number(resumo.horas_restantes).toLocaleString("pt-BR", { maximumFractionDigits: 1 });
  elementos.indicadores.append(
    criarIndicador(resumo.total, "Tarefas no total"),
    criarIndicador(resumo.pendentes, "Pendentes"),
    criarIndicador(resumo.em_andamento, "Em andamento"),
    criarIndicador(resumo.feitas, "Feitas"),
    criarIndicador(resumo.atrasadas, "Atrasadas", resumo.atrasadas > 0 ? "alerta" : ""),
    criarIndicador(horas + " h", "Horas restantes")
  );
}

function desenharProjetos(lista) {
  if (lista.length === 0) {
    elementos.projetos.textContent = "Nenhum projeto cadastrado.";
    return;
  }
  for (const projeto of lista) {
    const percentual = projeto.total === 0 ? 0 : Math.round((projeto.feitas / projeto.total) * 100);

    const linha = document.createElement("div");
    linha.className = "projeto-resumo";

    const titulo = document.createElement("div");
    titulo.className = "projeto-titulo";
    const nome = document.createElement("strong");
    nome.textContent = projeto.projeto;
    const contagem = document.createElement("span");
    contagem.textContent = projeto.feitas + " de " + projeto.total + " feitas (" + percentual + "%)";
    titulo.append(nome, contagem);

    const trilho = document.createElement("div");
    trilho.className = "progresso";
    trilho.setAttribute("role", "progressbar");
    trilho.setAttribute("aria-valuemin", "0");
    trilho.setAttribute("aria-valuemax", "100");
    trilho.setAttribute("aria-valuenow", String(percentual));
    const preenchido = document.createElement("div");
    preenchido.className = "progresso-preenchido";
    preenchido.style.width = percentual + "%";
    trilho.appendChild(preenchido);

    linha.append(titulo, trilho);
    elementos.projetos.appendChild(linha);
  }
}

async function iniciar() {
  try {
    const resposta = await fetch("/api/tarefas/resumo");
    const resumo = await resposta.json();
    if (!resposta.ok) {
      throw new Error(resumo.erro || "Erro " + resposta.status);
    }
    desenharIndicadores(resumo);
    desenharProjetos(resumo.por_projeto);
  } catch (erro) {
    mostrarErro("Não foi possível carregar o resumo: " + erro.message);
  }
}

iniciar();
