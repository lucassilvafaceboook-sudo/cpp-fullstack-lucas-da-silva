# C++ Full Stack — ITEAM (2º semestre)
Ambiente de aprendizado de pequenos desafios utilizando a linguagem de programação C++.

**Curso de Capacitação em Desenvolvimento Full Stack – ITEAM · Módulo 08 – Linguagem de Programação C++**
Professor: Msc. Hygo Sousa De Oliveira

## Comece aqui

O repositório oficial do curso é somente para leitura. As atividades são feitas na **sua própria cópia** (criada com *Use this template*); o passo a passo está em [COMO-OBTER-AS-ATIVIDADES.md](COMO-OBTER-AS-ATIVIDADES.md).

Como a nota é calculada: [AVALIACAO.md](AVALIACAO.md).

## Conteúdo

| Pasta | Conteúdo | Atividades | Situação |
|-------|----------|------------|----------|
| [`unidade-01/`](unidade-01/) | Introdução ao C++ | 15 (5 🟢 · 5 🟡 · 5 🔴) | Liberado |
| [`unidade-02/`](unidade-02/) | Estruturas de controle | 15 (5 🟢 · 5 🟡 · 5 🔴) | Liberado |
| [`unidade-03/`](unidade-03/) | Funções e ponteiros | 15 (5 🟢 · 5 🟡 · 5 🔴) | Liberado |
| [`unidade-04/`](unidade-04/) | Programação orientada a objetos | 15 (5 🟢 · 5 🟡 · 5 🔴) | Liberado |
| [`unidade-05/`](unidade-05/) | Bibliotecas e recursos avançados | 15 (5 🟢 · 5 🟡 · 5 🔴) | Liberado |
| [`projetos/`](projetos/) | **Projeto final:** API + banco de dados + front-end, em equipes de 4 (com um [demo](projetos/demo/) completo, feito em passos) | 1 projeto (3 temas) | Liberado |

Cada unidade tem um `exercicios.md` (enunciados, saída esperada e critérios de aceite) e uma pasta `base/` com um arquivo `.cpp` inicial para cada atividade.

## Como compilar

Todos os programas do curso usam **C++17** e devem ser compilados com avisos ativados:

```bash
g++ -std=c++17 -Wall -Wextra programa.cpp -o programa.exe
```

Verifique se o compilador está instalado com `g++ --version`. No Windows, recomendamos o **MSYS2 (UCRT64)**, que instala o `g++` e as bibliotecas usadas no projeto final; o passo a passo está em [`projetos/guia/01-preparar-ambiente.md`](projetos/guia/01-preparar-ambiente.md). No VS Code, o atalho **Ctrl+Shift+B** compila o arquivo aberto (tarefa já configurada em `.vscode/tasks.json`).

## Cronograma sugerido (10 dias · 8 h por dia)

| Dia | O que acontece |
|-----|----------------|
| 1 | Unidade 1 – Introdução ao C++ |
| 2 | Unidade 2 – Estruturas de controle |
| 3 | Unidade 3 – Funções e ponteiros |
| 4 | Unidade 4 – Programação orientada a objetos |
| 5 | Unidade 5 – Bibliotecas e recursos avançados · **lançamento do projeto, formação das equipes e escolha dos temas** |
| 6 | Oficina do starter kit: Docker/MariaDB, build, primeira rota, JSON e SQL (com o [demo](projetos/demo/ROTEIRO-LIVE-CODING.md)) |
| 7 e 8 | Desenvolvimento do CRUD (API + banco + front), com checkpoints |
| 9 | Integração, testes e documentação · **prazo final das tags de atividades** |
| 10 | Apresentações dos projetos (10 a 12 minutos por equipe) e feedback |

Cada unidade aparece como **Liberado** nesta tabela quando o professor liberar o conteúdo; para trazê-la para a sua cópia, veja a seção 5 de [COMO-OBTER-AS-ATIVIDADES.md](COMO-OBTER-AS-ATIVIDADES.md).
