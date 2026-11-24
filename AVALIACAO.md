# Avaliação do módulo

**Curso de Capacitação em Desenvolvimento Full Stack – ITEAM · Módulo 08 – Linguagem de Programação C++**
Professor: Msc. Hygo Sousa De Oliveira

## Como a nota é composta

| Componente | Peso | Como é calculado |
|------------|------|------------------|
| Atividades das unidades 1 a 5 | **50%** | Média das 5 notas de unidade (cada uma de 0 a 10) |
| Projeto final em equipe | **50%** | Rubrica do projeto, com ajuste individual (veja [`projetos/rubrica.md`](projetos/rubrica.md)) |

**Nota final = 0,5 × (média das 5 unidades) + 0,5 × (nota do projeto)**

## Atividades por unidade: você escolhe o caminho

Cada unidade tem até 5 atividades em cada nível. Cada atividade concluída soma pontos, e cada nível tem um teto:

| Nível | Pontos por atividade | Teto do nível |
|-------|----------------------|---------------|
| 🟢 Fácil | 1,0 | 4,0 |
| 🟡 Intermediário | 1,5 | 4,5 |
| 🔴 Difícil | 2,0 | 5,0 |

**Nota da unidade = soma dos pontos dos três níveis, limitada a 10,0.**

Os tetos somam 13,5, então há mais de um caminho para chegar à nota máxima. Fáceis e intermediários juntos chegam a, no máximo, 8,5; para passar disso é preciso fazer atividades difíceis.

Exemplos para a mesma unidade:

| Caminho | Fáceis | Intermediárias | Difíceis | Soma | Nota da unidade |
|---------|--------|----------------|----------|------|-----------------|
| Só os fundamentos | 5 (5,0 → teto 4,0) | 2 (3,0) | 0 | 7,0 | **7,0** |
| Equilibrado | 4 (4,0) | 3 (4,5) | 1 (2,0) | 10,5 | **10,0** |
| Foco no desafio | 2 (2,0) | 1 (1,5) | 3 (6,0 → teto 5,0) | 8,5 | **8,5** |

### Correção de cada atividade

Cada enunciado traz a saída esperada e uma lista de **critérios de aceite**. Não há gabarito publicado. O professor compila cada entrega com `g++ -std=c++17 -Wall -Wextra` e confere os critérios:

| Situação | Fator sobre os pontos da atividade |
|----------|------------------------------------|
| Compila sem erros e atende a **todos** os critérios de aceite | 1,0 (pontuação cheia) |
| Compila e atende a **parte** dos critérios | 0,5 (metade dos pontos) |
| Não compila, não foi entregue ou foi copiada | 0 |

### Entrega e prazo

- Cada unidade é entregue com a tag `atividade-unidade-NN` na sua cópia do repositório (veja [COMO-OBTER-AS-ATIVIDADES.md](COMO-OBTER-AS-ATIVIDADES.md)).
- O prazo final das tags de todas as unidades é o **dia 9** do cronograma (ou outra data informada pelo professor).
- Atividades marcadas depois do prazo perdem pontos conforme combinado com a turma.

### Integridade

O código entregue deve ser **seu**. Conversar sobre o problema é bom, mas copiar a solução de colegas, de repositórios ou de ferramentas e entregá-la como sua zera a atividade. Os *commits* mostram o seu processo: faça commits pequenos e frequentes, e esteja pronto para explicar qualquer linha do que entregou.

## Projeto final

- Equipes de 4 pessoas, 3 temas à escolha (veja [`projetos/`](projetos/)).
- A rubrica, o ajuste individual por *commits* e perguntas, e o formato da apresentação estão em [`projetos/rubrica.md`](projetos/rubrica.md).
- A entrega é a tag `projeto-final` na cópia da equipe e a apresentação no último dia.
