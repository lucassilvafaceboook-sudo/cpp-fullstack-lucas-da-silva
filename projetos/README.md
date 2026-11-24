# Projeto final — API em C++ + banco de dados + front-end

**Equipes de 4 pessoas · 3 temas à escolha · um CRUD completo, com apresentação no último dia.**

Depois das cinco unidades, vocês juntam tudo o que aprenderam (funções, classes, `vector`/`map`, arquivos, tratamento de erros…) e constroem um sistema pequeno de ponta a ponta:

```
Navegador (HTML + CSS + JavaScript)  ⇄  API em C++ (JSON sobre HTTP)  ⇄  MariaDB
```

Não é preciso começar do zero: o [`starter-kit/`](starter-kit/) já traz um CRUD de exemplo funcionando (*recados*). O desafio é **adaptá-lo ao tema da equipe**, com banco bem modelado, API validando os dados e uma tela que funcione de verdade.

🎬 **Quer ver o resultado esperado?** A pasta [`demo/`](demo/) tem um projeto completo, de outro domínio (*Tarefas por Projeto*), construído **em passos**, com uma tag do Git em cada um. Rode-o, leia o código e use o [README do demo](demo/README.md) como modelo para o da sua equipe. O roteiro dos passos está em [`demo/ROTEIRO-LIVE-CODING.md`](demo/ROTEIRO-LIVE-CODING.md).

## O que a equipe entrega

1. **API em C++17** (cpp-httplib + nlohmann/json) com o **CRUD completo** da entidade principal do tema e rotas de apoio para a entidade secundária.
2. **Banco MariaDB em container Docker** (`docker-compose.yml`), criado por um `schema.sql` que roda do zero, com chaves primárias e estrangeiras.
3. **Front-end** em HTML/CSS/JS puro, servido pela própria API, com listar, buscar, criar, editar e excluir.
4. **Documentação**: [`EQUIPE.md`](EQUIPE.md) preenchido e instruções para executar o projeto em outra máquina.
5. **Apresentação** de 10 a 12 minutos no dia 10.

## Os 3 temas

| Tema | Entidade principal | Entidade de apoio | Arquivo |
|------|--------------------|-------------------|---------|
| 📚 Biblioteca | Livro | Autor | [`temas/01-biblioteca.md`](temas/01-biblioteca.md) |
| 🐾 Clínica Pet | Pet | Tutor | [`temas/02-clinica-pet.md`](temas/02-clinica-pet.md) |
| 🛒 Estoque de Loja | Produto | Categoria | [`temas/03-estoque-loja.md`](temas/03-estoque-loja.md) |

Cada tema lista os campos, as regras de validação, as rotas mínimas e ideias de extras. Combine com o professor para não haver mais de duas equipes no mesmo tema, se possível.

## Cronograma

| Dia | Atividade | Ponto de controle (checkpoint) |
|-----|-----------|--------------------------------|
| 5 (final do dia) | Lançamento do projeto, formação das equipes, escolha do tema | Equipe e tema definidos; copiar o `EQUIPE.md` |
| 6 | **Oficina do starter kit**: ambiente, build, primeira rota, JSON, SQL | ✅ O starter kit roda em **todos** os computadores da equipe e `/api/saude/banco` responde `ok` |
| 7 | Banco do tema + entidade principal (listar e criar) | ✅ `schema.sql` do tema aplicado (`docker compose down -v` e `up -d --wait`); `GET` e `POST` funcionando com `curl` |
| 8 | CRUD completo na API + tela no front-end | ✅ Criar, editar e excluir pela tela |
| 9 | Integração, extras, testes, documentação · **prazo das tags de atividades** | ✅ Tag `projeto-final` criada; README testado numa máquina "limpa" |
| 10 | Apresentações e feedback | Demonstração ao vivo |

Os guias em [`guia/`](guia/) acompanham esse ritmo; leiam na ordem enquanto trabalham.

## Passo a passo para começar

1. Siga [`COMO-OBTER-AS-ATIVIDADES.md`](../COMO-OBTER-AS-ATIVIDADES.md), seção 7: **uma** pessoa cria a cópia da equipe e convida as outras (e o professor).
2. Todos clonam a cópia da equipe e **preparam o ambiente**: [`guia/01-preparar-ambiente.md`](guia/01-preparar-ambiente.md).
3. Copiem o starter kit para a pasta de trabalho da equipe (uma vez só, um integrante faz e dá `push`):

   ```bash
   cp -r projetos/starter-kit projetos/projeto-equipe
   ```

   A pasta `projetos/starter-kit/` continua intacta como referência; **todo o trabalho acontece em `projetos/projeto-equipe/`**, inclusive o banco: suba-o **dentro dessa pasta** (`docker compose up -d --wait`). Se você testou o banco no `starter-kit`, rode antes `docker compose down -v` lá, para não ocupar a porta 3306.
4. Preencham o [`EQUIPE.md`](EQUIPE.md).
5. Combinem como trabalhar com Git sem pisar no código dos colegas: [`guia/06-git-em-equipe.md`](guia/06-git-em-equipe.md).

## Estrutura esperada da cópia da equipe

```
projetos/
├── EQUIPE.md                 preenchido pela equipe
├── projeto-equipe/           ← cópia do starter-kit, adaptada ao tema
│   ├── docker-compose.yml    banco MariaDB em container (o professor sobe com `docker compose up -d --wait`)
│   ├── schema.sql            tabelas do tema (executado automaticamente pelo Docker)
│   ├── src/                  código C++ (rotas, repositórios, banco, main)
│   ├── public/               front-end
│   ├── libs/                 bibliotecas de terceiros (não editar)
│   ├── build.sh  build.bat
│   └── README.md             como instalar, compilar e executar (atualizado pela equipe)
└── (starter-kit/, demo/, guia/, temas/, rubrica.md ... material do professor)
```

> Dentro de `projeto-equipe/`, **substituam o `README.md` do starter kit** por um README da equipe: nome do projeto, como rodar do zero, lista de rotas e prints da tela. O professor vai seguir esse README para executar o projeto.

## Requisitos obrigatórios

- [ ] CRUD completo (listar, buscar um, criar, atualizar, remover) da **entidade principal**
- [ ] Entidade de apoio com **ao menos listar e criar** pela API, ligada à principal por **chave estrangeira**
- [ ] Validação dos dados na API (400, 404, 409 e 422 nos casos corretos), sem derrubar o servidor
- [ ] **Todo SQL com parâmetros `?`** (nunca concatenar valores no texto do SQL)
- [ ] Front-end com lista, formulário de criar/editar e exclusão com confirmação; mensagens de erro vindas da API aparecem na tela
- [ ] Compila com `g++ -std=c++17 -Wall -Wextra` **sem avisos**
- [ ] `docker compose up -d --wait` cria o banco do zero (executando o `schema.sql`), com alguns dados de exemplo
- [ ] README da equipe com instruções que funcionam em outro computador
- [ ] Todos os integrantes com *commits* no próprio usuário

Os itens da rubrica e o peso de cada um estão em [`rubrica.md`](rubrica.md). Extras (busca avançada, rota de resumo, paginação, ordenação…) valem pontos dentro dos critérios, mas **só depois** de os obrigatórios estarem funcionando.

## Regras de convivência

- Todos aprendem tudo: **revezem** as tarefas (um dia banco, outro API, outro front). Na apresentação, qualquer integrante pode ser chamado a explicar qualquer parte.
- Programação em dupla é bem-vinda. Nesse caso, quem digitou faz o *commit* e a outra pessoa entra como coautora (`Co-authored-by:` na mensagem; veja o guia 06).
- É permitido usar documentação, o material do curso e conversar com outras equipes sobre ideias. Copiar o projeto de outra equipe, ou código que ninguém da equipe consegue explicar, não é permitido.
- Problemas com ambiente (compilador, Docker, biblioteca do MariaDB) devem ser levados ao professor **no dia 6**, não deixados para depois.
