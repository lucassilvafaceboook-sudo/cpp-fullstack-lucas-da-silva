# Guia 5 — Front-end do CRUD

**Objetivo:** adaptar a tela do starter kit ao seu tema, entender como ela conversa com a API e depurar problemas pelo navegador.

🎬 **No demo:** o `config.js`, o `config-projetos.js` e a página própria `resumo.html` (passos 4 e 5) são exemplos prontos de tudo o que este guia descreve ([`demo/public/`](../demo/public/)).

## 1. Como o front-end chega ao navegador

O próprio servidor em C++ entrega os arquivos da pasta `public/`:

```
Você digita http://localhost:8080  →  servidor devolve public/index.html
index.html pede config.js, app.js, estilo.css  →  servidor devolve os arquivos
app.js faz fetch("/api/recados")  →  rota C++ → MariaDB → JSON  →  a tabela aparece
```

Como a página e a API vêm do **mesmo endereço** (`localhost:8080`), não há problema de CORS.

| Arquivo | Papel | Quem edita |
|---------|-------|------------|
| `index.html` | esqueleto da página (formulário e tabela vazios) | raramente |
| `config.js` | **configuração do tema**: título, recurso da API, campos | **a equipe** |
| `app.js` | lógica genérica: monta a tela, chama a API, mostra erros | só se precisar de algo novo |
| `estilo.css` | aparência | à vontade |

## 2. Configurando a tela: `config.js`

```js
const CONFIG = {
  titulo: "Biblioteca - Livros",
  recurso: "livros",                    // usa /api/livros
  campos: [
    { nome: "titulo", rotulo: "Título", tipo: "texto", obrigatorio: true, max: 150 },
    { nome: "autor_id", rotulo: "Autor", tipo: "select", obrigatorio: true,
      opcoesDe: { recurso: "autores", valor: "id", rotulo: "nome" } },
    { nome: "ano_publicacao", rotulo: "Ano", tipo: "numero", min: 1000, max: 2100 },
    { nome: "exemplares", rotulo: "Exemplares", tipo: "numero", min: 0, padrao: 1 },
  ],
};
```

O **`nome`** de cada campo precisa ser **exatamente** o nome da chave no JSON da API (`autor_id`, não `autor`). O `rotulo` é o texto que aparece na tela.

### Tipos de campo

| `tipo` | Entrada | Opções |
|--------|---------|--------|
| `"texto"` | uma linha | `max` (tamanho) |
| `"textarea"` | várias linhas | `max` |
| `"numero"` | inteiro | `min`, `max` |
| `"decimal"` | com casas decimais | `min`, `max`, `passo`, `formato: "moeda"` (mostra `R$ 18,90`), `casas: 1` (quantas casas na tabela; padrão 2) |
| `"data"` | seletor de data | — (mostra `15/03/2021` na tabela) |
| `"select"` | lista de opções | `opcoes: [{valor: "gato", rotulo: "Gato"}, ...]` **ou** `opcoesDe: {recurso, valor, rotulo}` (busca na API) |
| `"somenteLeitura"` | só aparece na tabela | ex.: `criado_em` |

Opções que valem para qualquer campo: `obrigatorio: true` (mostra o `*` e avisa antes de enviar), `padrao: valor` (valor inicial do formulário), `largo: true` (ocupa a linha inteira) e `rotuloTabela: "Prioridade"` (título mais curto para a coluna da tabela quando o rótulo do formulário é comprido).

Campos `somenteLeitura` que trazem data e hora do banco (`criado_em`) aparecem como `20/11/2026 14:42`.

### Lista fixa de opções (ex.: espécie do pet)

```js
{ nome: "especie", rotulo: "Espécie", tipo: "select", obrigatorio: true,
  opcoes: [
    { valor: "cachorro", rotulo: "Cachorro" },
    { valor: "gato", rotulo: "Gato" },
    { valor: "ave", rotulo: "Ave" },
    { valor: "outro", rotulo: "Outro" },
  ] },
```

### Lista que vem do banco (ex.: autor, tutor, categoria)

`opcoesDe: { recurso: "autores", valor: "id", rotulo: "nome" }` faz o `app.js` chamar `GET /api/autores` e montar a lista. Na **tabela**, o número `autor_id` é trocado automaticamente pelo **nome** do autor.

### Dinheiro e datas

```js
{ nome: "preco", rotulo: "Preço", tipo: "decimal", formato: "moeda", min: 0 },
{ nome: "data_nascimento", rotulo: "Nascimento", tipo: "data" },
```

## 3. Mais de uma tela (entidade de apoio)

O tema pede uma forma de cadastrar a entidade de apoio (autor, tutor, categoria). O jeito mais simples é uma **segunda página** com o mesmo `app.js`:

1. Copie `index.html` para `autores.html`.
2. Copie `config.js` para `config-autores.js` e ajuste `titulo`, `recurso: "autores"` e os `campos`.
3. Em `autores.html`, troque `<script src="config.js">` por `<script src="config-autores.js">`.
4. Nos **dois** arquivos de configuração, acrescente o menu para as páginas se enxergarem:

   ```js
   menu: [
     { texto: "Livros", href: "index.html" },
     { texto: "Autores", href: "autores.html" },
   ],
   ```

5. Se a API do apoio ainda não tem `PUT`/`DELETE`, esconda os botões com `semEditar: true` e/ou `semExcluir: true` no `config-autores.js`. (Melhor ainda: implemente as rotas!)

### Destacar linhas, botões extras e filtros (opcional)

Três ganchos no `config.js` deixam a tela mais útil sem mexer no `app.js`:

```js
// 1) Pinta a linha com uma classe CSS (prontas no estilo.css: "linha-alerta" e "linha-apagada")
classeLinha: (r) => r.status === "feito" ? "linha-apagada" : null,

// 2) Botões a mais em cada linha, que chamam uma rota da API (ex.: POST /api/tarefas/3/concluir)
acoesExtras: [
  { rotulo: "Concluir", metodo: "POST", mensagem: "Tarefa concluída.",
    caminho: (r) => `/api/tarefas/${r.id}/concluir`,
    mostrarSe: (r) => r.status !== "feito" },
],

// 3) Listas de filtro ao lado da busca: cada uma envia ?nome=valor (ex.: GET /api/tarefas?status=feito)
filtros: [
  { nome: "status", rotulo: "Status", opcoes: [{ valor: "pendente", rotulo: "Pendente" }, { valor: "feito", rotulo: "Feito" }] },
  { nome: "projeto_id", rotulo: "Projeto", opcoesDe: { recurso: "projetos", valor: "id", rotulo: "nome" } },
],
```

- `acoesExtras`: o `metodo` é `POST` por padrão, e `mostrarSe` (opcional) esconde o botão nas linhas em que ele não faz sentido. Depois do clique, a tabela é recarregada sozinha.
- `filtros`: o navegador só **envia** o parâmetro; quem filtra de verdade é a API. Implemente o `?status=` / `?projeto_id=` no repositório (guia 04, receita de busca) e valide o valor recebido.

## 4. Como o `app.js` fala com a API

O coração é o `fetch`. Por exemplo, criar um registro:

```js
const resposta = await fetch("/api/livros", {
  method: "POST",
  headers: { "Content-Type": "application/json" },
  body: JSON.stringify({ titulo: "Dom Casmurro", autor_id: 1 }),
});
const dados = await resposta.json();      // o registro criado (201) ou {"erro": ..., "detalhes": [...]}
if (!resposta.ok) { /* mostrar dados.erro e dados.detalhes */ }
```

- `async`/`await` faz o código esperar a resposta sem travar a página.
- `resposta.ok` é `true` para status 200–299. Para 400, 404, 409, 422, 500, é `false`, e o `app.js` mostra a mensagem da API na tela (caixa vermelha), com a lista de `detalhes`.
- Um **204** não tem corpo: não chame `.json()` nele (o `app.js` já trata isso).

## 5. Segurança: nunca use `innerHTML` com dados do banco

O `app.js` escreve os dados na tela com `textContent`. Se alguém cadastrar o título `<img src=x onerror=alert(1)>`, ele aparece **como texto**, sem executar. Com `innerHTML`, o navegador interpretaria a marcação e o script rodaria (ataque **XSS**). Se acrescentarem código ao front-end, mantenham `textContent`.

Teste: cadastre um registro com um título contendo `<b>negrito</b>` e confira que aparece literalmente.

## 6. Depurando com as ferramentas do navegador (F12)

| Aba | Para quê |
|-----|----------|
| **Console** | erros de JavaScript (linha vermelha com o arquivo e a linha) |
| **Network (Rede)** | cada requisição: método, URL, **status**, corpo enviado e resposta. Clique em uma linha → *Payload* / *Response* |
| **Elements (Elementos)** | o HTML gerado e o CSS aplicado |

Roteiro quando "a tela não funciona":

1. **F12 → Network**, recarregue (Ctrl+F5) e veja se alguma requisição está vermelha. Qual o status? Qual a resposta?
2. **Status 404** na API: caminho errado no `recurso` do `config.js`, ou a rota não existe/ não foi registrada no `main.cpp`.
3. **Status 500**: veja o **console do servidor** (a janela do `servidor.exe`): o erro do banco está lá.
4. **Console** com `CONFIG is not defined`: o `config.js` não foi carregado antes do `app.js` (confira as tags `<script>` no HTML).
5. Tela em branco e nada no Console: o servidor está rodando? A pasta `public/` foi encontrada?
6. Mudei o `config.js` e nada mudou: recarregue com **Ctrl+F5** (o navegador guarda os arquivos em cache).

## 7. Aparência e usabilidade (vale pontos)

- Títulos claros e rótulos em português correto, com acentos.
- Tabela legível: números alinhados à direita (o `app.js` já faz), datas como `dd/mm/aaaa`, dinheiro como `R$ 18,90`.
- Mensagens de sucesso e de erro visíveis (o `app.js` já mostra).
- Teste com a janela **estreita** (como celular): o formulário e a tabela devem continuar usáveis.
- Mexam nas variáveis de cor no começo do `estilo.css` para dar a identidade da equipe.

## 8. Exercícios

1. No starter kit, mude o `titulo` e os `rotulo` dos campos no `config.js`, recarregue com Ctrl+F5 e veja a tela mudar. Depois deixe o campo `prioridade` com `max: 10` e envie 9: o navegador deixa, mas a **API recusa** (422). Por quê?
2. Configure a tela do **seu tema** e teste criar, editar, buscar e excluir.
3. Crie a segunda tela da entidade de apoio, com o menu ligando as duas.
4. Provoque um erro de validação (campo obrigatório vazio; valor fora da faixa) e confira a mensagem mostrada.
5. (Desafio) Mostre, em vermelho, as linhas cujo estoque/exemplares seja 0, alterando o `desenharTabela` do `app.js`.

Próximo: [guia 06 — Git em equipe](06-git-em-equipe.md).
