// ---------- utilidades ----------
const $ = (sel) => document.querySelector(sel);

// Nome de cada espécie (código -> nome), preenchido com GET /api/especies ao abrir a página
const ROTULO_ESPECIE = {};
const ROTULO_TIPO = { consulta: "🩺 Consulta", vacina: "💉 Vacinação" };
const ROTULO_STATUS = { aguardando: "Aguardando", concluido: "Concluído" };

function esc(v) {
  return String(v ?? "").replace(/[&<>"']/g, (c) =>
    ({ "&": "&amp;", "<": "&lt;", ">": "&gt;", '"': "&quot;", "'": "&#39;" })[c]);
}

// '2021-03-15' -> '15/03/2021'
const formatarData = (iso) => (iso ? iso.slice(0, 10).split("-").reverse().join("/") : "—");
// '2026-11-25 14:03:00' -> '25/11/2026 14:03'
const formatarDataHora = (s) => (s ? `${formatarData(s)} ${s.slice(11, 16)}` : "—");
// mês 3, ano 2021 -> '03/2021'; só o ano -> '2021'
const formatarNascimento = (mes, ano) =>
  !ano ? "—" : mes ? `${String(mes).padStart(2, "0")}/${ano}` : String(ano);
const formatarPeso = (kg) => (kg == null ? "—" : `${kg.toLocaleString("pt-BR")} kg`);

// ---------- imagens de pets (referência Stitch + fallback SVG offline) ----------
function svgAvatarPet(corFundo, corDetalhe, emoji, rotulo) {
  const svg = `<svg xmlns="http://www.w3.org/2000/svg" viewBox="0 0 160 160">
    <rect width="160" height="160" rx="28" fill="${corFundo}"/>
    <circle cx="80" cy="72" r="44" fill="${corDetalhe}" opacity="0.22"/>
    <text x="80" y="86" font-size="52" text-anchor="middle">${emoji}</text>
    <text x="80" y="136" font-family="sans-serif" font-size="14" font-weight="700" fill="#ffffff" text-anchor="middle">${rotulo}</text>
  </svg>`;
  return `data:image/svg+xml;utf8,${encodeURIComponent(svg)}`;
}

const FOTOS_PETS = {
  beagle: {
    url: "https://lh3.googleusercontent.com/aida-public/AB6AXuB0fg2CFqcNuZXNSKgKun0VhsFDydFOd-n8u7dVyLgw8IfgGx5lJ3AKc2s4AQMQZaWII0h7YaJe1r_Sw03Y_5i_tJZaOyUMCCKunn74RJvC58AEfOERS8KpEQgddHDV898gi3Pq--UE5qYCjg1BslcXEYBW3WQTq-fhRqLVL8-JhckBexgK5Z_a7u-pFQJ3Zp8H3Gk93qezctZ3qxy7fhOhNA8JCl_dBFPCGLABzDdp",
    fallback: svgAvatarPet("#16382c", "#f39223", "🐶", "Cão"),
  },
  gato: {
    url: "https://lh3.googleusercontent.com/aida-public/AB6AXuCFpsnrYRe5h6c2l2-4wsAQ_4mfE4v2CG4g-e8t1NkjarUvxeuJcJR49oQG-myhOYxfhxnUnRN-qd8uER4WgNBr9BCcadkTixOCGOMN3SttO8K52BEGqr5n8v-XTuDBJBQb-yFGxx0HCz48-OYnOYyi_buXcqbWYEcjKkzaPkwG9aLCoKJoCjXmu7GqpEN4cmIosoL5Kzrx4Wf7mH62T6qYEL7aW5SIj4CWJHHrL07-",
    fallback: svgAvatarPet("#1f4e3d", "#acf1d1", "🐱", "Gato"),
  },
  dupla: {
    url: "https://lh3.googleusercontent.com/aida-public/AB6AXuAGzdWypOIz-QMd5D4n8VUDfSBABv7bCmN6NyipcJAEdoYT-VkP5HGOj2JMvQCBtTDaJSd9mGyolVXosA00MecftgNitYoNW94dQySu0-ocLTLlmM2qEff7AVmDVLxvM3g9OEmkFcEduKZQXJ4SQjfgoZU60zLd9BXqf6K7C2MZk6Mtatzx14jB0Git4v16rrHqXt5SlvVvbUvy5ort4LJpkKBKWBJNPZ1zJlg00x6M",
    fallback: svgAvatarPet("#16382c", "#ffdcc0", "🐾", "Clínica Pet"),
  },
  exotico: {
    url: svgAvatarPet("#f39223", "#16382c", "🐰", "Pet"),
    fallback: svgAvatarPet("#f39223", "#16382c", "🐰", "Pet"),
  },
};

function configurarImagemComFallback(img, chave) {
  const item = FOTOS_PETS[chave] || FOTOS_PETS.beagle;
  img.onerror = () => {
    img.onerror = null;
    img.src = item.fallback;
  };
  img.src = item.url;
}

// Preenche miniaturas do seletor de avaliação e fallback da imagem hero
document.querySelectorAll("[data-pet-thumb]").forEach((img) => {
  configurarImagemComFallback(img, img.dataset.petThumb);
});
const heroImg = $("#img-hero-auth");
if (heroImg) {
  heroImg.addEventListener("error", () => {
    heroImg.src = FOTOS_PETS.dupla.fallback;
  }, { once: true });
}

// ---------- sessão ----------
const CHAVE_TOKEN = "clinicaPetToken";
let usuario = null;

function lerToken() {
  try { return localStorage.getItem(CHAVE_TOKEN) || ""; } catch { return ""; }
}
function guardarToken(t) {
  try { t ? localStorage.setItem(CHAVE_TOKEN, t) : localStorage.removeItem(CHAVE_TOKEN); } catch { /* sem storage */ }
}
const ehVet = () => usuario?.papel === "veterinario";

async function api(metodo, url, corpo) {
  const headers = {};
  if (corpo) headers["Content-Type"] = "application/json";
  const token = lerToken();
  if (token) headers.Authorization = `Bearer ${token}`;
  const resp = await fetch(url, { method: metodo, headers, body: corpo ? JSON.stringify(corpo) : undefined });
  const dados = resp.status === 204 ? null : await resp.json().catch(() => null);
  if (resp.status === 401 && !url.startsWith("/api/auth/login")) {
    sair(false);
    throw Object.assign(new Error(dados?.erro || "Faça login."), { status: 401, dados });
  }
  if (!resp.ok) throw Object.assign(new Error(dados?.erro || "Erro"), { status: resp.status, dados });
  return dados;
}

let timerAviso;
function avisar(msg, erro = false) {
  const el = $("#aviso");
  el.textContent = msg;
  el.className = erro ? "aviso erro" : "aviso";
  el.hidden = false;
  clearTimeout(timerAviso);
  timerAviso = setTimeout(() => (el.hidden = true), 3500);
}

function limparErros(form) {
  form.querySelectorAll(".msg-campo").forEach((e) => e.remove());
  form.querySelectorAll(".invalido").forEach((e) => e.classList.remove("invalido"));
  form.querySelector(".erro-geral").hidden = true;
}

function mostrarErros(form, err) {
  const campos = err.dados?.campos || {};
  let algumNoForm = false;
  for (const [nome, msg] of Object.entries(campos)) {
    const input = form.elements[nome];
    if (!input || input.closest("[hidden]")) continue;
    algumNoForm = true;
    input.classList.add("invalido");
    const p = document.createElement("span");
    p.className = "msg-campo";
    p.textContent = msg;
    input.closest("label").append(p);
  }
  if (!algumNoForm) {
    const geral = form.querySelector(".erro-geral");
    geral.textContent = Object.values(campos)[0] || err.message;
    geral.hidden = false;
  }
}

const dadosDoForm = (form) => Object.fromEntries(new FormData(form).entries());

// Sintomas: obrigatório só quando é consulta
function ligarCampoSintomas(form) {
  const atualizar = () => {
    const consulta = form.elements.tipo.value === "consulta";
    const label = form.querySelector(".campo-sintomas");
    label.firstChild.textContent = consulta ? "Sintomas* " : "Observação (opcional) ";
    form.elements.sintomas.placeholder = consulta
      ? "Ex.: está sem comer há 2 dias, vomitou ontem…"
      : "Ex.: vacina V10 / antirrábica";
  };
  form.elements.tipo.addEventListener("change", atualizar);
  atualizar();
  return atualizar;
}
const atualizarSintomasPet = ligarCampoSintomas($("#form-pet"));
const atualizarSintomasAtend = ligarCampoSintomas($("#form-atendimento"));

// ---------- raça: autocompletar + "não sei" ----------
// Compara sem acento e sem maiúsculas: "pastor alemao" encontra "Pastor Alemão".
const normalizar = (t) => t.normalize("NFD").replace(/[̀-ͯ]/g, "").toLowerCase().trim();

const campoRaca = $("#form-pet").elements.raca;
const listaRaca = $("#sugestoes-raca");
let sugestoes = [];
let destacada = -1;

function racasDaEspecie() {
  const especie = $("#form-pet").elements.especie.value;
  return especie ? RACAS[especie] || [] : Object.values(RACAS).flat();
}

function mostrarSugestoes() {
  const busca = normalizar(campoRaca.value);
  const todas = racasDaEspecie();
  // primeiro as que começam com o que foi digitado, depois as que contêm
  const comeca = [], contem = [];
  for (const r of todas) {
    const n = normalizar(r);
    if (!busca || n.startsWith(busca) || n.split(/[\s(-]+/).some((p) => p.startsWith(busca))) comeca.push(r);
    else if (n.includes(busca)) contem.push(r);
  }
  sugestoes = [...comeca, ...contem].slice(0, 8);
  // não mostra a lista se o que foi digitado já é exatamente uma raça
  if (sugestoes.length === 1 && normalizar(sugestoes[0]) === busca) sugestoes = [];
  destacada = -1;
  listaRaca.innerHTML = sugestoes.map((r, i) =>
    `<li role="option" id="sug-raca-${i}" data-indice="${i}">${realcar(r, busca)}</li>`).join("");
  const aberta = sugestoes.length > 0 && !campoRaca.disabled;
  listaRaca.hidden = !aberta;
  campoRaca.setAttribute("aria-expanded", String(aberta));
}

// Deixa em negrito o pedaço que bate com a busca
function realcar(raca, busca) {
  if (!busca) return esc(raca);
  const i = normalizar(raca).indexOf(busca);
  if (i < 0) return esc(raca);
  return esc(raca.slice(0, i)) + "<b>" + esc(raca.slice(i, i + busca.length)) + "</b>" + esc(raca.slice(i + busca.length));
}

function fecharSugestoes() {
  listaRaca.hidden = true;
  campoRaca.setAttribute("aria-expanded", "false");
  destacada = -1;
}

function escolherRaca(i) {
  campoRaca.value = sugestoes[i];
  fecharSugestoes();
}

function destacar(i) {
  destacada = (i + sugestoes.length) % sugestoes.length;
  listaRaca.querySelectorAll("li").forEach((li, j) => li.classList.toggle("ativa", j === destacada));
  campoRaca.setAttribute("aria-activedescendant", `sug-raca-${destacada}`);
  listaRaca.children[destacada]?.scrollIntoView({ block: "nearest" });
}

campoRaca.addEventListener("input", mostrarSugestoes);
campoRaca.addEventListener("focus", mostrarSugestoes);
campoRaca.addEventListener("blur", () => setTimeout(fecharSugestoes, 100));
campoRaca.addEventListener("keydown", (ev) => {
  if (listaRaca.hidden) {
    if (ev.key === "ArrowDown") { mostrarSugestoes(); ev.preventDefault(); }
    return;
  }
  if (ev.key === "ArrowDown") { destacar(destacada + 1); ev.preventDefault(); }
  else if (ev.key === "ArrowUp") { destacar(destacada - 1); ev.preventDefault(); }
  else if (ev.key === "Enter" && destacada >= 0) { escolherRaca(destacada); ev.preventDefault(); }
  else if (ev.key === "Escape") { fecharSugestoes(); ev.preventDefault(); ev.stopPropagation(); }
  else if (ev.key === "Tab" && destacada >= 0) escolherRaca(destacada);
});
// mousedown (e não click) para escolher antes do campo perder o foco
listaRaca.addEventListener("mousedown", (ev) => {
  const li = ev.target.closest("li");
  if (!li) return;
  ev.preventDefault();
  escolherRaca(Number(li.dataset.indice));
});
// Trocou a espécie: as sugestões mudam
$("#form-pet").elements.especie.addEventListener("change", () => {
  if (document.activeElement === campoRaca) mostrarSugestoes();
});

// "Não sei a raça": limpa e trava o campo; a raça vai vazia (NULL no banco)
function marcarNaoSeiRaca(marcado) {
  $("#raca-nao-sei").checked = marcado;
  campoRaca.disabled = marcado;
  if (marcado) { campoRaca.value = ""; fecharSugestoes(); }
  campoRaca.placeholder = marcado ? "Raça não informada" : "Comece a digitar…";
}
$("#raca-nao-sei").addEventListener("change", (ev) => {
  marcarNaoSeiRaca(ev.target.checked);
  if (!ev.target.checked) campoRaca.focus();
});

// ---------- estado ----------
let tutores = [];
let pets = [];
let atendimentos = [];

// Preenche um <select> a partir de um recurso da API
function preencherSelect(select, itens, { valor, rotulo, vazio }) {
  const atual = select.value;
  select.innerHTML =
    (vazio !== undefined ? `<option value="">${esc(vazio)}</option>` : "") +
    itens.map((i) => `<option value="${esc(i[valor])}">${esc(i[rotulo])}</option>`).join("");
  if ([...select.options].some((o) => o.value === atual)) select.value = atual;
}

// Lista de espécies separada por grupo (Aves, Répteis...) com <optgroup>
function preencherEspecies(select, especies, vazio) {
  const grupos = new Map();
  for (const e of especies) {
    if (!grupos.has(e.grupo)) grupos.set(e.grupo, []);
    grupos.get(e.grupo).push(e);
  }
  select.innerHTML = `<option value="">${esc(vazio)}</option>` +
    [...grupos].map(([grupo, itens]) => `<optgroup label="${esc(grupo)}">` +
      itens.map((e) => `<option value="${esc(e.codigo)}">${esc(e.nome)}</option>`).join("") +
      "</optgroup>").join("");
}

async function carregarTutores() {
  if (!ehVet()) return;
  tutores = await api("GET", "/api/tutores");
  preencherSelect($("#filtro-tutor"), tutores, { valor: "id", rotulo: "nome", vazio: "Todos os tutores" });
  preencherSelect($("#form-pet").elements.tutor_id, tutores, { valor: "id", rotulo: "nome", vazio: "Selecione…" });
  renderizarTutores();
}

// Atualiza indicadores resumidos apenas na visão do tutor
async function atualizarPainelTutor() {
  if (!usuario || ehVet()) return;
  $("#nome-tutor-painel").textContent = usuario.nome.split(" ")[0] || usuario.nome;
  try {
    const [meusPets, todosAtend] = await Promise.all([
      api("GET", "/api/pets"),
      api("GET", "/api/atendimentos"),
    ]);
    $("#tutor-total-pets").textContent = meusPets.length;
    $("#tutor-total-aguardando").textContent = todosAtend.filter((a) => a.status === "aguardando").length;
    $("#tutor-total-concluidos").textContent = todosAtend.filter((a) => a.status === "concluido").length;
    atualizarPetsNaAvaliacao(meusPets);
  } catch {
    // silencioso: os carregamentos principais já tratam falhas
  }
}

// ---------- pets ----------
async function carregarPets() {
  const qs = new URLSearchParams();
  if ($("#busca").value.trim()) qs.set("busca", $("#busca").value.trim());
  if ($("#filtro-especie").value) qs.set("especie", $("#filtro-especie").value);
  if (ehVet() && $("#filtro-tutor").value) qs.set("tutor_id", $("#filtro-tutor").value);
  pets = await api("GET", `/api/pets?${qs}`);

  $("#lista-pets").innerHTML = pets.map((p) => `
    <tr>
      <td><b>${esc(p.nome)}</b></td>
      <td><span class="selo">${esc(ROTULO_ESPECIE[p.especie] || p.especie)}</span></td>
      <td>${p.raca ? esc(p.raca) : '<span class="sub">Não sei</span>'}</td>
      <td>${formatarNascimento(p.mes_nascimento, p.ano_nascimento)}</td>
      <td>${esc(p.idade?.texto || "—")}</td>
      <td>${formatarPeso(p.peso_kg)}</td>
      <td class="so-vet">${esc(p.tutor_nome)}<span class="sub">${esc(p.tutor_telefone)}</span></td>
      <td class="acoes-linha">
        <button type="button" class="pequeno ${ehVet() ? "" : "btn-laranja"}" data-atend-pet="${p.id}">${ehVet() ? "Atendimentos" : "Pedir atendimento"}</button>
        <button type="button" class="pequeno" data-editar-pet="${p.id}">Editar</button>
        <button type="button" class="pequeno perigo" data-excluir-pet="${p.id}" data-nome="${esc(p.nome)}">Excluir</button>
      </td>
    </tr>`).join("");
  $("#vazio-pets").textContent = ehVet() || qs.toString()
    ? "Nenhum pet encontrado."
    : "Você ainda não cadastrou nenhum pet. Clique em “+ Novo pet”.";
  $("#vazio-pets").hidden = pets.length > 0;
  if (ehVet()) carregarResumo();
  else if (!qs.toString()) atualizarPetsNaAvaliacao(pets);
}

async function carregarResumo() {
  const r = await api("GET", "/api/pets/resumo");
  const cards = [`<div class="card"><b>${r.total}</b><span>pets no total</span></div>`];
  for (const e of r.por_especie) {
    cards.push(`<div class="card"><b>${e.quantidade}</b><span>${esc(ROTULO_ESPECIE[e.especie] || e.especie)}` +
      `${e.peso_medio != null ? ` · média ${formatarPeso(e.peso_medio)}` : ""}</span></div>`);
  }
  $("#resumo").innerHTML = cards.join("");
}

async function abrirPet(id) {
  const form = $("#form-pet");
  form.reset();
  limparErros(form);
  form.dataset.id = id || "";
  $("#titulo-pet").textContent = id ? "Editar pet" : "Novo pet";
  $("#motivo-pet").hidden = Boolean(id); // o motivo só é pedido ao cadastrar
  form.elements.ano_nascimento.max = new Date().getFullYear();
  if (id) {
    const p = await api("GET", `/api/pets/${id}`);
    for (const campo of ["nome", "especie", "raca", "mes_nascimento", "ano_nascimento", "peso_kg", "tutor_id"])
      form.elements[campo].value = p[campo] ?? "";
  }
  marcarNaoSeiRaca(Boolean(id) && !form.elements.raca.value);
  atualizarSintomasPet();
  $("#dlg-pet").showModal();
}

$("#form-pet").addEventListener("submit", async (ev) => {
  ev.preventDefault();
  const form = ev.target;
  limparErros(form);
  const id = form.dataset.id;
  const dados = dadosDoForm(form);
  if (id) { delete dados.tipo; delete dados.sintomas; }
  try {
    await api(id ? "PUT" : "POST", id ? `/api/pets/${id}` : "/api/pets", dados);
    $("#dlg-pet").close();
    avisar(id ? "Pet atualizado!" : (dados.tipo ? "Pet cadastrado e pedido de atendimento enviado!" : "Pet cadastrado!"));
    await Promise.all([carregarPets(), carregarTutores(), carregarAtendimentos(), atualizarPainelTutor()]);
  } catch (err) {
    mostrarErros(form, err);
  }
});

// ---------- atendimentos ----------
async function carregarAtendimentos() {
  const qs = new URLSearchParams();
  if ($("#filtro-status").value) qs.set("status", $("#filtro-status").value);
  const lista = await api("GET", `/api/atendimentos?${qs}`);
  const vet = ehVet();
  $("#lista-atendimentos").innerHTML = lista.map((a) => `
    <article class="atend ${a.status}">
      <header>
        <b>${esc(a.pet_nome)}</b>
        <span class="selo">${esc(ROTULO_TIPO[a.tipo] || a.tipo)}</span>
        <span class="status ${a.status}">${esc(ROTULO_STATUS[a.status] || a.status)}</span>
        <span class="sub data">${formatarDataHora(a.criado_em)}</span>
      </header>
      ${vet ? `<p class="sub">Tutor: ${esc(a.tutor_nome)} · ${esc(a.tutor_telefone)}</p>` : ""}
      ${a.sintomas ? `<p><span class="rotulo">${a.tipo === "consulta" ? "Sintomas" : "Observação"}:</span> ${esc(a.sintomas)}</p>` : ""}
      ${a.observacoes ? `<p class="obs"><span class="rotulo">Veterinário:</span> ${esc(a.observacoes)}</p>` : ""}
      ${vet ? `<div class="acoes-linha"><button type="button" class="pequeno primario" data-concluir="${a.id}">Registrar atendimento</button></div>` : ""}
    </article>`).join("");
  $("#vazio-atendimentos").hidden = lista.length > 0;
  atendimentos = lista;
}

async function abrirPedido(petId) {
  if (!pets.length) await carregarPets();
  if (!pets.length) return avisar("Cadastre um pet primeiro.", true);
  const form = $("#form-atendimento");
  form.reset();
  limparErros(form);
  preencherSelect(form.elements.pet_id, pets, { valor: "id", rotulo: "nome", vazio: "Selecione…" });
  if (petId) form.elements.pet_id.value = petId;
  atualizarSintomasAtend();
  $("#dlg-atendimento").showModal();
}

$("#form-atendimento").addEventListener("submit", async (ev) => {
  ev.preventDefault();
  const form = ev.target;
  limparErros(form);
  try {
    await api("POST", "/api/atendimentos", dadosDoForm(form));
    $("#dlg-atendimento").close();
    avisar("Pedido enviado para a clínica!");
    $("#filtro-status").value = "aguardando";
    await Promise.all([carregarAtendimentos(), atualizarPainelTutor()]);
  } catch (err) {
    mostrarErros(form, err);
  }
});

function abrirConcluir(id) {
  const a = atendimentos.find((x) => String(x.id) === String(id));
  const form = $("#form-concluir");
  form.reset();
  limparErros(form);
  form.dataset.id = id;
  $("#titulo-concluir").textContent = `${ROTULO_TIPO[a.tipo] || a.tipo} · ${a.pet_nome}`;
  $("#resumo-concluir").textContent = a.sintomas ? `${a.tipo === "consulta" ? "Sintomas" : "Obs."}: ${a.sintomas}` : "";
  form.elements.status.value = a.status === "aguardando" ? "concluido" : a.status;
  form.elements.observacoes.value = a.observacoes || "";
  $("#dlg-concluir").showModal();
}

$("#form-concluir").addEventListener("submit", async (ev) => {
  ev.preventDefault();
  const form = ev.target;
  limparErros(form);
  try {
    await api("PATCH", `/api/atendimentos/${form.dataset.id}`, dadosDoForm(form));
    $("#dlg-concluir").close();
    avisar("Atendimento atualizado!");
    await carregarAtendimentos();
  } catch (err) {
    mostrarErros(form, err);
  }
});

// ---------- tutores ----------
function renderizarTutores() {
  $("#lista-tutores").innerHTML = tutores.map((t) => `
    <tr>
      <td><b>${esc(t.nome)}</b>${t.tem_conta ? ' <span class="selo">tem conta</span>' : ""}</td>
      <td>${esc(t.telefone)}</td>
      <td>${esc(t.email || "—")}</td>
      <td>${t.qtd_pets}</td>
      <td class="acoes-linha">
        <button type="button" class="pequeno" data-ver-pets="${t.id}">Ver pets</button>
        <button type="button" class="pequeno" data-editar-tutor="${t.id}">Editar</button>
        <button type="button" class="pequeno perigo" data-excluir-tutor="${t.id}" data-nome="${esc(t.nome)}">Excluir</button>
      </td>
    </tr>`).join("");
}

let tutorRapido = false; // true quando o tutor é criado a partir do formulário de pet

function abrirTutor(id, rapido = false) {
  const form = $("#form-tutor");
  form.reset();
  limparErros(form);
  form.dataset.id = id || "";
  tutorRapido = rapido;
  $("#titulo-tutor").textContent = id ? "Editar tutor" : "Novo tutor";
  if (id) {
    const t = tutores.find((x) => String(x.id) === String(id));
    form.elements.nome.value = t.nome;
    form.elements.telefone.value = t.telefone;
    form.elements.email.value = t.email || "";
  }
  $("#dlg-tutor").showModal();
}

$("#form-tutor").addEventListener("submit", async (ev) => {
  ev.preventDefault();
  const form = ev.target;
  limparErros(form);
  const id = form.dataset.id;
  try {
    const t = await api(id ? "PUT" : "POST", id ? `/api/tutores/${id}` : "/api/tutores", dadosDoForm(form));
    $("#dlg-tutor").close();
    avisar(id ? "Tutor atualizado!" : "Tutor cadastrado!");
    await Promise.all([carregarTutores(), carregarPets()]);
    if (tutorRapido) $("#form-pet").elements.tutor_id.value = t.id; // já seleciona o novo tutor
  } catch (err) {
    mostrarErros(form, err);
  }
});

// ---------- avaliações de tutores (persistência em localStorage) ----------
const CHAVE_AVALIACOES = "clinicaPetAvaliacoes";

const AVALIACOES_INICIAIS = [
  {
    id: "seed-1",
    pet_nome: "Floquinho",
    pet_detalhe: "Beagle, 3 anos",
    nota: 5,
    foto_chave: "beagle",
    comentario: "A equipe da Clínica Pet no ITEAM RR foi impecável no atendimento do Floquinho! Ele tinha receio de consultório, mas foi acolhido com tanto carinho que nem sentiu a aplicação das vacinas.",
    tutor_nome: "Mariana Vasconcelos",
    local: "Tutora em Boa Vista/RR",
    propria: false,
  },
  {
    id: "seed-2",
    pet_nome: "Luna",
    pet_detalhe: "Gata SRD, 2 anos",
    nota: 5,
    foto_chave: "gato",
    comentario: "O acompanhamento preventivo da Luna foi excelente. Ambiente climatizado, tranquilo para felinos e profissionais que explicam cada cuidado nos mínimos detalhes.",
    tutor_nome: "Carlos Eduardo Mendes",
    local: "Tutor em Boa Vista/RR",
    propria: false,
  },
  {
    id: "seed-3",
    pet_nome: "Thor & Mel",
    pet_detalhe: "Golden Retriever & Felina",
    nota: 5,
    foto_chave: "dupla",
    comentario: "Excelente iniciativa em Boa Vista! O portal facilitou demais o pedido de atendimento e o histórico das consultas dos meus dois pets. Atendimento nota 10!",
    tutor_nome: "Beatriz Albuquerque",
    local: "Tutora em Boa Vista/RR",
    propria: false,
  },
];

function lerAvaliacoesSalvas() {
  try {
    const bruto = localStorage.getItem(CHAVE_AVALIACOES);
    const salvas = bruto ? JSON.parse(bruto) : [];
    return Array.isArray(salvas) ? salvas : [];
  } catch {
    return [];
  }
}

function guardarAvaliacoesSalvas(lista) {
  try {
    localStorage.setItem(CHAVE_AVALIACOES, JSON.stringify(lista));
  } catch { /* sem storage */ }
}

const TEXTO_NOTA = {
  1: "1.0 · Precisa melhorar",
  2: "2.0 · Regular",
  3: "3.0 · Bom",
  4: "4.0 · Muito bom",
  5: "5.0 · Excelente",
};

function definirNotaEstrelas(nota) {
  const n = Math.min(5, Math.max(1, Number(nota) || 5));
  const form = $("#form-avaliacao");
  if (!form) return;
  form.elements.nota.value = String(n);
  form.querySelectorAll(".estrela-btn").forEach((btn) => {
    btn.classList.toggle("ativa", Number(btn.dataset.estrela) <= n);
  });
  $("#texto-nota-avaliacao").textContent = TEXTO_NOTA[n];
}

function renderizarAvaliacoes() {
  const grade = $("#lista-avaliacoes");
  if (!grade) return;
  const salvas = lerAvaliacoesSalvas();
  const todas = [...salvas, ...AVALIACOES_INICIAIS];

  const soma = todas.reduce((acc, a) => acc + (Number(a.nota) || 5), 0);
  const media = (soma / todas.length).toFixed(1).replace(".", ",");
  $("#resumo-avaliacoes").innerHTML =
    `<strong>★ ${media}</strong><span>${todas.length} ${todas.length === 1 ? "avaliação" : "avaliações"}</span>`;

  grade.innerHTML = todas.map((a) => {
    const nota = Math.min(5, Math.max(1, Number(a.nota) || 5));
    const estrelas = "★".repeat(nota) + "☆".repeat(5 - nota);
    const podeRemover = Boolean(a.propria);
    return `
      <article class="card-avaliacao">
        <div>
          <div class="avaliacao-topo">
            <div class="avaliacao-pet">
              <img data-foto-avaliacao="${esc(a.foto_chave || "beagle")}" alt="Foto do pet ${esc(a.pet_nome)}">
              <div>
                <strong>${esc(a.pet_nome)}</strong>
                <span>${esc(a.pet_detalhe || "Paciente da Clínica Pet")}</span>
              </div>
            </div>
            <span class="avaliacao-selo-pata" aria-hidden="true">🐾</span>
          </div>
          <div class="avaliacao-estrelas" aria-label="Nota ${nota} de 5">
            ${estrelas} <b>${nota}.0</b>
          </div>
          <p class="avaliacao-texto">“${esc(a.comentario)}”</p>
        </div>
        <div class="avaliacao-autor">
          <div>
            <strong>${esc(a.tutor_nome)}</strong>
            <span>${esc(a.local || "Tutor(a) em Boa Vista/RR")}</span>
          </div>
          ${podeRemover ? `<button type="button" class="pequeno perigo" data-excluir-avaliacao="${esc(a.id)}">Remover</button>` : ""}
        </div>
      </article>`;
  }).join("");

  grade.querySelectorAll("img[data-foto-avaliacao]").forEach((img) => {
    configurarImagemComFallback(img, img.dataset.fotoAvaliacao);
  });
}

let petsTutorCache = [];
function atualizarPetsNaAvaliacao(listaPets) {
  petsTutorCache = listaPets || [];
  const bloco = $("#bloco-escolher-pet-avaliacao");
  const select = $("#avaliacao-meu-pet");
  if (!bloco || !select) return;
  bloco.hidden = petsTutorCache.length === 0;
  preencherSelect(select, petsTutorCache, {
    valor: "id",
    rotulo: "nome",
    vazio: "Selecionar pet cadastrado (opcional)…",
  });
}

$("#avaliacao-meu-pet")?.addEventListener("change", (ev) => {
  const p = petsTutorCache.find((x) => String(x.id) === ev.target.value);
  if (!p) return;
  const form = $("#form-avaliacao");
  form.elements.pet_nome.value = p.nome;
  const partes = [p.raca || ROTULO_ESPECIE[p.especie] || p.especie, p.idade?.texto].filter(Boolean);
  form.elements.pet_detalhe.value = partes.join(", ");
  const chaveSugerida = p.especie === "gato" ? "gato" : p.especie === "cachorro" ? "beagle" : "exotico";
  const radio = form.querySelector(`input[name="foto_chave"][value="${chaveSugerida}"]`);
  if (radio) {
    radio.checked = true;
    sincronizarOpcoesFoto();
  }
});

function sincronizarOpcoesFoto() {
  document.querySelectorAll(".opcao-foto").forEach((lbl) => {
    const r = lbl.querySelector('input[name="foto_chave"]');
    lbl.classList.toggle("selecionada", Boolean(r?.checked));
  });
}

$("#form-avaliacao")?.addEventListener("change", (ev) => {
  if (ev.target.name === "foto_chave") sincronizarOpcoesFoto();
});

$("#form-avaliacao")?.addEventListener("submit", (ev) => {
  ev.preventDefault();
  const form = ev.target;
  limparErros(form);
  const dados = dadosDoForm(form);
  const petNome = (dados.pet_nome || "").trim();
  const comentario = (dados.comentario || "").trim();

  const camposErro = {};
  if (!petNome) camposErro.pet_nome = "Informe o nome do pet.";
  if (comentario.length < 8) camposErro.comentario = "Escreva um breve relato (mínimo de 8 caracteres).";
  if (Object.keys(camposErro).length > 0) {
    mostrarErros(form, { message: "Verifique os campos.", dados: { campos: camposErro } });
    return;
  }

  const hoje = new Date().toLocaleDateString("pt-BR");
  const nova = {
    id: `local-${Date.now()}`,
    pet_nome: petNome,
    pet_detalhe: (dados.pet_detalhe || "").trim() || "Paciente atendido no ITEAM RR",
    nota: Number(dados.nota) || 5,
    foto_chave: dados.foto_chave || "beagle",
    comentario,
    tutor_nome: usuario?.nome || "Tutor(a)",
    local: `Boa Vista/RR · ${hoje}`,
    propria: true,
  };

  const salvas = lerAvaliacoesSalvas();
  salvas.unshift(nova);
  guardarAvaliacoesSalvas(salvas);

  form.reset();
  definirNotaEstrelas(5);
  sincronizarOpcoesFoto();
  renderizarAvaliacoes();
  avisar("Avaliação publicada! Obrigado por compartilhar sua experiência.");
});

// ---------- login / cadastro ----------
function trocarAuth(qual) {
  document.querySelectorAll(".auth-aba").forEach((b) => b.classList.toggle("ativa", b.dataset.auth === qual));
  $("#form-login").hidden = qual !== "login";
  $("#form-registro").hidden = qual !== "registro";
}

function atualizarTipoRegistro() {
  const vet = $("#form-registro").elements.papel.value === "veterinario";
  document.querySelectorAll(".reg-vet").forEach((e) => (e.hidden = !vet));
  document.querySelectorAll(".reg-cliente").forEach((e) => (e.hidden = vet));
  document.querySelectorAll("#form-registro .cartao-papel").forEach((lbl) => {
    const r = lbl.querySelector('input[name="papel"]');
    lbl.classList.toggle("selecionado", Boolean(r?.checked));
  });
}
$("#form-registro").addEventListener("change", (ev) => {
  if (ev.target.name === "papel") atualizarTipoRegistro();
});

async function entrou({ token, usuario: u }) {
  guardarToken(token);
  usuario = u;
  await mostrarApp();
}

$("#form-login").addEventListener("submit", async (ev) => {
  ev.preventDefault();
  const form = ev.target;
  limparErros(form);
  try {
    await entrou(await api("POST", "/api/auth/login", dadosDoForm(form)));
    form.reset();
  } catch (err) {
    mostrarErros(form, err);
  }
});

$("#form-registro").addEventListener("submit", async (ev) => {
  ev.preventDefault();
  const form = ev.target;
  limparErros(form);
  const dados = dadosDoForm(form);
  if (dados.papel === "veterinario") delete dados.telefone;
  else delete dados.codigo_clinica;
  try {
    await entrou(await api("POST", "/api/auth/registro", dados));
    form.reset();
    atualizarTipoRegistro();
    avisar(`Bem-vindo(a), ${usuario.nome}!`);
  } catch (err) {
    mostrarErros(form, err);
  }
});

function mostrarLogin() {
  document.body.dataset.papel = "";
  $("#tela-auth").hidden = false;
  trocarAuth("login");
}

async function mostrarApp() {
  document.body.dataset.papel = usuario.papel;
  $("#tela-auth").hidden = true;
  $("#quem").textContent = `${usuario.nome} · ${ehVet() ? "Veterinário(a)" : "Tutor(a)"}`;
  trocarAba("pets");
  // Filtros de outra sessão não valem para esta
  $("#busca").value = "";
  $("#filtro-especie").value = "";
  $("#filtro-tutor").value = "";
  $("#filtro-status").value = "aguardando";
  $("#lista-pets").innerHTML = "";
  $("#lista-atendimentos").innerHTML = "";
  if (!ehVet()) renderizarAvaliacoes();
  await carregarTutores();
  await Promise.all([carregarPets(), carregarAtendimentos(), atualizarPainelTutor()]);
}

async function sair(avisarServidor = true) {
  if (avisarServidor && lerToken()) await api("POST", "/api/auth/logout").catch(() => { });
  guardarToken("");
  usuario = null;
  tutores = [];
  pets = [];
  petsTutorCache = [];
  document.querySelectorAll("dialog[open]").forEach((d) => d.close());
  mostrarLogin();
}

// ---------- eventos ----------
document.addEventListener("click", async (ev) => {
  const b = ev.target.closest("button");
  if (!b) return;
  try {
    if (b.dataset.fechar !== undefined) b.closest("dialog").close();
    else if (b.dataset.verSenha !== undefined) {
      const input = b.closest(".campo-senha")?.querySelector("input");
      if (!input) return;
      const mostrar = input.type === "password";
      input.type = mostrar ? "text" : "password";
      b.textContent = mostrar ? "Ocultar" : "Mostrar";
    }
    else if (b.dataset.estrela) definirNotaEstrelas(b.dataset.estrela);
    else if (b.dataset.excluirAvaliacao) {
      const restantes = lerAvaliacoesSalvas().filter((a) => a.id !== b.dataset.excluirAvaliacao);
      guardarAvaliacoesSalvas(restantes);
      renderizarAvaliacoes();
      avisar("Avaliação removida.");
    }
    else if (b.dataset.irSecao) {
      document.getElementById(b.dataset.irSecao)?.scrollIntoView({ behavior: "smooth", block: "start" });
    }
    else if (b.dataset.acaoPedir !== undefined) await abrirPedido();
    else if (b.dataset.acaoNovoPet !== undefined) await abrirPet();
    else if (b.dataset.auth) trocarAuth(b.dataset.auth);
    else if (b.dataset.aba) {
      trocarAba(b.dataset.aba);
      const alvo = b.dataset.aba === "pets" ? $("#aba-pets") : b.dataset.aba === "atendimentos" ? $("#aba-atendimentos") : $("#aba-tutores");
      if (!ehVet() && b.closest(".painel-tutor, .card-institucional")) {
        alvo?.scrollIntoView({ behavior: "smooth", block: "nearest" });
      }
    }
    else if (b.id === "sair") await sair();
    else if (b.id === "novo-pet") await abrirPet();
    else if (b.id === "novo-atendimento") await abrirPedido();
    else if (b.id === "novo-tutor") abrirTutor();
    else if (b.id === "tutor-rapido") abrirTutor(null, true);
    else if (b.dataset.editarPet) await abrirPet(b.dataset.editarPet);
    else if (b.dataset.atendPet) {
      if (ehVet()) {
        $("#filtro-status").value = "";
        trocarAba("atendimentos");
        await carregarAtendimentos();
        const nome = pets.find((p) => String(p.id) === b.dataset.atendPet)?.nome;
        if (nome) avisar(`Atendimentos de todos os pets. Procure por ${nome}.`);
      } else await abrirPedido(b.dataset.atendPet);
    }
    else if (b.dataset.concluir) abrirConcluir(b.dataset.concluir);
    else if (b.dataset.editarTutor) abrirTutor(b.dataset.editarTutor);
    else if (b.dataset.verPets) {
      $("#filtro-tutor").value = b.dataset.verPets;
      trocarAba("pets");
      await carregarPets();
    } else if (b.dataset.excluirPet) {
      if (!confirm(`Excluir o pet ${b.dataset.nome}? Os pedidos de atendimento dele também serão apagados.`)) return;
      await api("DELETE", `/api/pets/${b.dataset.excluirPet}`);
      avisar("Pet excluído.");
      await Promise.all([carregarPets(), carregarTutores(), carregarAtendimentos(), atualizarPainelTutor()]);
    } else if (b.dataset.excluirTutor) {
      if (!confirm(`Excluir o tutor ${b.dataset.nome}?`)) return;
      await api("DELETE", `/api/tutores/${b.dataset.excluirTutor}`);
      avisar("Tutor excluído.");
      await carregarTutores();
    }
  } catch (err) {
    if (err.status !== 401) avisar(err.message, true);
  }
});

function trocarAba(nome) {
  document.querySelectorAll(".aba[data-aba]").forEach((a) => a.classList.toggle("ativa", a.dataset.aba === nome));
  document.querySelectorAll("[data-painel-aba]").forEach((c) => c.classList.toggle("aba-foco", c.dataset.painelAba === nome));
  $("#aba-pets").hidden = nome !== "pets";
  $("#aba-atendimentos").hidden = nome !== "atendimentos";
  $("#aba-tutores").hidden = nome !== "tutores";
}

let timerBusca;
$("#busca").addEventListener("input", () => {
  clearTimeout(timerBusca);
  timerBusca = setTimeout(carregarPets, 250);
});
$("#filtro-especie").addEventListener("change", carregarPets);
$("#filtro-tutor").addEventListener("change", carregarPets);
$("#filtro-status").addEventListener("change", carregarAtendimentos);

// ---------- início ----------
(async function iniciar() {
  atualizarTipoRegistro();
  definirNotaEstrelas(5);
  try {
    const especies = await api("GET", "/api/especies");
    for (const e of especies) ROTULO_ESPECIE[e.codigo] = e.nome;
    preencherEspecies($("#filtro-especie"), especies, "Todas as espécies");
    preencherEspecies($("#form-pet").elements.especie, especies, "Selecione…");
  } catch {
    mostrarLogin();
    avisar("Não foi possível falar com a API. O servidor está rodando?", true);
    return;
  }
  if (!lerToken()) return mostrarLogin();
  try {
    usuario = await api("GET", "/api/auth/eu");
    await mostrarApp();
  } catch (err) {
    if (err.status !== 401) avisar(err.message, true);
  }
})();
