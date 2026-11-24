# Rubrica do projeto final

O projeto vale **100 pontos** (nota de 0 a 10 = pontos ÷ 10) e representa **50%** da nota final do módulo (veja [`../AVALIACAO.md`](../AVALIACAO.md)). A nota da equipe é ajustada individualmente, como descrito mais abaixo.

## Como o professor avalia

1. Clona a cópia da equipe na tag `projeto-final` e **segue o README da equipe** para compilar e executar. Se não for possível executar, os critérios 1, 2 e 3 ficam limitados a 50% do valor (veja *Limitações*).
2. Compila com `g++ -std=c++17 -Wall -Wextra` e lê o código.
3. Assiste à apresentação e faz perguntas individuais.
4. Consulta o histórico de *commits* de cada integrante.

## Critérios

### 1. API e CRUD — 25 pontos

| Item | Pontos |
|------|:------:|
| CRUD completo da entidade principal (`GET` lista, `GET` por id, `POST`, `PUT`, `DELETE`) funcionando | 10 |
| Códigos de status corretos (200, 201, 204, 400, 404, 409, 422) e respostas de erro em JSON | 6 |
| Entidade de apoio: ao menos listar e criar, ligada por chave estrangeira | 4 |
| Busca/filtro e/ou uma rota extra do tema (resumo, baixo estoque, movimentação…) | 5 |

### 2. Banco de dados — 20 pontos

| Item | Pontos |
|------|:------:|
| O banco sobe do zero com `docker compose up -d --wait`, sem erros (o `schema.sql` roda sozinho), e o `docker compose down -v` seguido de novo `up` recria tudo | 5 |
| Modelagem: chaves primárias e estrangeiras, tipos adequados, `NOT NULL`, `UNIQUE`/`CHECK` onde faz sentido | 7 |
| **Todo SQL com parâmetros `?`**; nenhum valor concatenado no texto do SQL | 5 |
| Dados de exemplo suficientes para demonstrar o sistema | 3 |

### 3. Front-end — 20 pontos

| Item | Pontos |
|------|:------:|
| Listar, criar, editar e excluir funcionando pela tela | 10 |
| Mensagens de sucesso e de erro (incluindo os erros de validação vindos da API) | 4 |
| Campos do tema corretos, com lista de seleção para a entidade de apoio e valores formatados (data, moeda) | 3 |
| Usabilidade e aparência cuidadas (títulos claros, tabela legível, funciona no celular/janela estreita) | 3 |

### 4. Qualidade do código C++ — 15 pontos

| Item | Pontos |
|------|:------:|
| Organização: SQL nos repositórios, HTTP nas rotas, nada misturado em `main.cpp`; arquivos com responsabilidade clara | 4 |
| Boas práticas da Unidade 4 e 5: RAII, sem `new`/`delete` soltos, `const` e referências, tipos adequados, sem vazamentos | 4 |
| Compila sem avisos com `-Wall -Wextra` | 4 |
| Nomes claros, funções curtas, comentários só onde ajudam | 3 |

### 5. Documentação — 10 pontos

| Item | Pontos |
|------|:------:|
| [`EQUIPE.md`](EQUIPE.md) completo (integrantes, tema, papéis, decisões) | 3 |
| README da equipe: instalar, subir o banco, compilar, executar — reproduzível em outro computador | 4 |
| Tabela das rotas da API com exemplos de requisição/resposta | 3 |

### 6. Apresentação — 10 pontos

| Item | Pontos |
|------|:------:|
| Demonstração ao vivo funcionando (criar, editar, excluir, tratar um erro) | 5 |
| Explicação técnica clara: arquitetura, uma rota de ponta a ponta, uma decisão de projeto | 3 |
| Tempo respeitado (10 a 12 min) e participação de todos os integrantes | 2 |

## Níveis de desempenho (como o professor decide a pontuação de cada item)

| Nível | Fração do item | Quando |
|-------|:--------------:|--------|
| Completo | 100% | Funciona e atende ao que o item descreve, inclusive em casos de erro |
| Parcial | 50% | Funciona no "caminho feliz", mas com falhas em casos de erro ou partes faltando |
| Mínimo | 25% | Existe, mas só funciona em parte ou não foi demonstrado |
| Ausente | 0% | Não existe ou não funciona |

## Limitações (tetos)

- **Não executa seguindo o README** (e o problema não é do computador do professor): critérios 1, 2 e 3 limitados a **50%** do valor.
- **SQL concatenado com valores vindos do usuário** (vulnerável a *SQL injection*): o item de parâmetros `?` zera e a nota do critério 2 fica limitada a 15 pontos.
- **Projeto incompleto no prazo** (sem a tag `projeto-final` até o prazo): desconto combinado com a turma.
- **Plágio** (projeto de outra equipe, ou código que a equipe não consegue explicar e não escreveu): critérios afetados zerados.

## Ajuste individual

**Nota individual = nota da equipe × fator individual.** O fator só reduz a nota (nunca passa de 1,0) e vem de duas fontes: o histórico de *commits* e as perguntas feitas na apresentação.

| Fator | Situação |
|:-----:|----------|
| **1,0** | Contribuiu de forma consistente (commits em mais de um dia, em partes diferentes do projeto) e respondeu bem às perguntas |
| **0,85** | Contribuição pequena ou concentrada em uma parte só, **ou** dificuldade com várias perguntas sobre o que a equipe construiu |
| **0,7** | Pouquíssimos commits **e** dificuldade com as perguntas |
| **0,5 ou menos** | Praticamente não participou, ou não consegue explicar nada do projeto |

Como a equipe evita surpresas:

- Cada pessoa faz *commits* com o **próprio usuário** do GitHub (confiram `git config user.name` e `user.email`).
- Commits pequenos e frequentes, com mensagens que dizem o que mudou.
- Em duplas, o outro integrante entra como coautor (`Co-authored-by:`).
- Revezem as áreas (banco, API, front). Na apresentação, as perguntas podem ser de qualquer parte.

O professor também considera o registro de tarefas do [`EQUIPE.md`](EQUIPE.md) (quem fez o quê) e conversa com a equipe se houver divergência entre o relato e o histórico.

## Perguntas típicas na apresentação

- "Mostre o caminho de uma requisição `POST`: da tela até o banco." (front → rota → validação → repositório → SQL)
- "O que acontece se eu enviar um JSON inválido? E um título vazio? E um id que não existe?"
- "Por que o SQL usa `?` em vez de montar o texto com os valores?"
- "Onde a conexão com o banco é aberta e fechada? O que garante que ela fecha?" (RAII, Unidade 4)
- "O que é a chave estrangeira desta tabela e o que acontece se eu apagar o registro ao qual ela aponta?"
- "Mostre no código uma coisa que vocês aprenderam nas unidades 3, 4 e 5 e usaram aqui."
