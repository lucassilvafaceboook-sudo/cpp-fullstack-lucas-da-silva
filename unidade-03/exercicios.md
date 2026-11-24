# 🛠️ Atividades – Unidade 3: Funções e ponteiros
**Curso de Capacitação em Desenvolvimento Full Stack – ITEAM**
Módulo 08 – Linguagem de Programação C++
Professor: Msc. Hygo Sousa De Oliveira

> **Conteúdo da apostila:** Unidade 3, seções 3.1 a 3.7 (funções, parâmetros, valor e referência, ponteiros, aritmética de ponteiros, alocação dinâmica, recursão)
> **Tópicos:** funções e protótipos · parâmetros e retorno · passagem por valor e por referência · ponteiros e `nullptr` · aritmética de ponteiros · `new`/`delete` · recursividade

---

## 📌 Como resolver e entregar

> Faça isto **antes de começar a resolver as atividades**.

Faça as atividades na **sua própria cópia** do repositório do curso. Se ainda não criou a sua, siga o passo a passo de [COMO-OBTER-AS-ATIVIDADES.md](../COMO-OBTER-AS-ATIVIDADES.md).

### 1. Copie a pasta `base/` para `resolucao/`

```bash
cp -r unidade-03/base unidade-03/resolucao
```

No PowerShell do Windows: `Copy-Item -Recurse unidade-03\base unidade-03\resolucao`.

> Não altere os arquivos dentro de `base/`: eles pertencem ao professor e podem ser substituídos quando você baixar atualizações.

### 2. Resolva e compile

Abra o arquivo da atividade dentro de `resolucao/`, complete os trechos marcados com `TODO` e compile **sempre com avisos ativados**:

```bash
cd unidade-03/resolucao
g++ -std=c++17 -Wall -Wextra f1_exemplo.cpp -o f1.exe
./f1.exe          # no Windows (CMD/PowerShell): .\f1.exe
```

Troque `f1_exemplo.cpp` e `f1.exe` pelo nome do arquivo da atividade. Atividades com arquivos de dados (`.txt`, `.csv`) devem ser executadas **de dentro da pasta `resolucao/`**.

### 3. Salve o seu progresso na sua cópia

```bash
git add unidade-03/resolucao
git commit -m "feat: unidade 3 - atividades F1 a F3"
git push origin main
```

Faça commits pequenos e frequentes: eles mostram o seu processo. **Não envie arquivos `.exe`** (o `.gitignore` já os ignora).

### 4. Entregue

Quando terminar, marque a entrega com a tag desta unidade e envie ao professor o link da sua cópia:

```bash
git tag atividade-unidade-03
git push origin atividade-unidade-03
```

---

## 🧭 Você escolhe o caminho

Esta unidade tem **até 5 atividades por nível**. Cada atividade concluída soma pontos; cada nível tem um teto. A **nota da unidade é a soma dos pontos, limitada a 10,0**.

| Nível | Atividades | Pontos por atividade | Teto do nível |
|-------|-----------|----------------------|---------------|
| 🟢 Fácil | até 5 | 1,0 | 4,0 |
| 🟡 Intermediário | até 5 | 1,5 | 4,5 |
| 🔴 Difícil | até 5 | 2,0 | 5,0 |

- Cada atividade vale a pontuação cheia se **compilar sem erros e atender a todos os critérios de aceite**. Se compilar e atender só parte dos critérios, vale metade. Se não compilar, não pontua. Detalhes em [AVALIACAO.md](../AVALIACAO.md).
- Os tetos somam mais que 10: você pode escolher **quais** atividades fazer. Mas só os fáceis e intermediários não chegam a 10, então é preciso fazer **ao menos uma atividade difícil** para alcançar a nota máxima.
- Não há gabarito: cada enunciado traz a saída esperada e os **critérios de aceite** que o professor usa na correção.

## 🟢 Nível Fácil

### 🟢 F1 – Calculadora organizada em funções

📄 **Arquivo base:** `base/f1_calculadora_funcoes.cpp` · **Vale:** 1,0 ponto(s)

A calculadora do dia a dia fica mais legível quando cada operação é uma função.

**O que fazer:**
1. No topo do arquivo, declare os **protótipos** de `somar`, `subtrair`, `multiplicar` e `dividir` (cada uma recebe dois `double` e devolve `double`).
2. Em `main`, leia dois números e verifique a leitura.
3. Mostre os quatro resultados. Se o divisor for zero, mostre `Divisao: indefinida (divisor zero)` **sem chamar** `dividir`.
4. Escreva as definições das quatro funções **depois** de `main`.

**Exemplo de execução** (o que o usuário digita aparece depois dos dois-pontos):
```text
Dois numeros: 12 4
Soma: 16
Subtracao: 8
Multiplicacao: 48
Divisao: 3
```
```text
Dois numeros: 5 0
Soma: 5
Subtracao: 5
Multiplicacao: 0
Divisao: indefinida (divisor zero)
```

> 💡 *Dica: o protótipo permite chamar a função antes de ela ser definida. Ele só tem o tipo de retorno, o nome e os parâmetros, terminado em `;`.*

**✅ Critérios de aceite:**
- [ ] Os quatro protótipos estão no topo e as quatro definições vêm depois de `main`
- [ ] Os resultados dos dois exemplos estão corretos
- [ ] A divisão por zero é tratada sem chamar `dividir`
- [ ] A leitura é verificada

---

### 🟢 F2 – Trocar dois valores: por valor ou por referência?

📄 **Arquivo base:** `base/f2_valor_ou_referencia.cpp` · **Vale:** 1,0 ponto(s)

Duas funções tentam trocar o conteúdo de duas variáveis. Só uma consegue. O programa mostra a diferença.

**O que fazer:**
1. Implemente `void trocarPorValor(int a, int b)` e `void trocarPorReferencia(int& a, int& b)`. As duas trocam `a` e `b` usando uma variável temporária e, **dentro da função**, mostram `Dentro de <nome da função>: a = ..., b = ...`.
2. O `main` já está pronto: lê `x` e `y`, chama cada função e mostra os valores antes e depois.
3. Em um comentário, explique por que `trocarPorValor` não altera `x` e `y`.

**Exemplo de execução** (o que o usuário digita aparece depois dos dois-pontos):
```text
Dois inteiros: 3 7
Antes: x = 3, y = 7
Dentro de trocarPorValor: a = 7, b = 3
Depois de trocarPorValor: x = 3, y = 7
Dentro de trocarPorReferencia: a = 7, b = 3
Depois de trocarPorReferencia: x = 7, y = 3
```

> 💡 *Dica: na passagem por valor a função trabalha numa **cópia**. Com `int&`, o parâmetro é outro nome para a própria variável do chamador.*

**✅ Critérios de aceite:**
- [ ] A saída é a do exemplo para a entrada `3 7`
- [ ] A troca é feita com variável temporária
- [ ] `trocarPorReferencia` usa `int&` e altera as variáveis originais
- [ ] Comentário explicando a diferença entre as duas passagens

---

### 🟢 F3 – Percorrendo um array por índice e por ponteiro

📄 **Arquivo base:** `base/f3_array_e_ponteiros.cpp` · **Vale:** 1,0 ponto(s)

Um array e um ponteiro para o seu primeiro elemento dão acesso aos mesmos dados.

**O que fazer:**
1. O arquivo base já declara `int numeros[6]{10, 20, 30, 40, 50, 60};` e o ponteiro `ponteiro`, que aponta para o primeiro elemento.
2. Mostre os seis valores usando **índices** (`numeros[i]`).
3. Mostre os seis valores usando **aritmética de ponteiros** (`*(ponteiro + i)`).
4. Some os valores com um ponteiro `p` que **avança** (`++p`) até `numeros + 6` (a posição logo após o último elemento, que **não** pode ser desreferenciada).
5. Altere o terceiro elemento por ponteiro (`*(ponteiro + 2) = 99;`) e mostre `numeros[2]`.
6. Em um comentário, explique o que significam `&` e `*`.

**Saída esperada:**
```text
Por indice: 10 20 30 40 50 60
Por ponteiro: 10 20 30 40 50 60
Soma (ponteiro ate o fim): 210
Apos *(ponteiro + 2) = 99, numeros[2] = 99
```

> 💡 *Dica: `ponteiro + 1` avança para o **próximo elemento** (`sizeof(int)` bytes), e não um byte. `numeros[i]` e `*(numeros + i)` são equivalentes.*

**✅ Critérios de aceite:**
- [ ] A saída é exatamente a esperada
- [ ] A soma usa um ponteiro que percorre o array até `numeros + 6`, sem desreferenciar o fim
- [ ] A alteração é feita por ponteiro
- [ ] Comentário explicando `&` e `*`

---

### 🟢 F4 – Funções com retorno e funções `void`

📄 **Arquivo base:** `base/f4_funcoes_utilitarias.cpp` · **Vale:** 1,0 ponto(s)

Um relatório simples dá a chance de usar funções que **devolvem** valores e uma função `void` que apenas **apresenta** o resultado.

**O que fazer:**
1. Escreva `int maiorDeTres(int a, int b, int c)`, que devolve o maior valor.
2. Escreva `bool ehPar(int n)`.
3. Escreva `double mediaDeTres(int a, int b, int c)`.
4. Escreva `void exibirRelatorio(int maior, bool par, double media)`, que mostra as duas linhas do relatório (média com duas casas decimais).
5. Em `main`, leia três inteiros (verificando a leitura), chame as funções e passe os resultados para `exibirRelatorio`. A paridade é a do **maior** valor.

**Exemplo de execução** (o que o usuário digita aparece depois dos dois-pontos):
```text
Tres inteiros: 8 3 5
Maior: 8 (par)
Media: 5.33
```
```text
Tres inteiros: 4 9 7
Maior: 9 (impar)
Media: 6.67
```

> 💡 *Dica: uma função `bool` pode ser usada direto em uma expressão, como em `par ? " (par)" : " (impar)"`. Divida por `3.0` (e não `3`) para não perder as casas decimais.*

**✅ Critérios de aceite:**
- [ ] Os dois exemplos produzem a saída mostrada; `5 5 5` dá maior `5` (impar) e média `5.00`
- [ ] Três funções devolvem valores e `exibirRelatorio` é `void`
- [ ] Nenhuma função lê ou escreve dados além do necessário (a leitura fica em `main`; só `exibirRelatorio` imprime)
- [ ] A leitura é verificada

---

### 🟢 F5 – Fatorial recursivo e iterativo

📄 **Arquivo base:** `base/f5_fatorial.cpp` · **Vale:** 1,0 ponto(s)

O fatorial de `n` é `n * (n-1) * ... * 1`, com `0! = 1`. Vamos calculá-lo de duas formas e comparar.

**O que fazer:**
1. Leia `n` e valide: `n` deve estar entre `0` e `20`. Caso contrário, escreva `Entrada invalida (use 0 a 20).` em `std::cerr` e devolva `1`.
2. Escreva `unsigned long long fatorialRecursivo(unsigned int n)` com **caso-base** e chamada a si mesma.
3. Escreva `unsigned long long fatorialIterativo(unsigned int n)` com um laço.
4. Mostre os dois resultados e se eles são iguais.
5. Em um comentário, explique por que o limite é `20` quando se usa `unsigned long long` de 64 bits.

**Exemplo de execução** (o que o usuário digita aparece depois dos dois-pontos):
```text
N (0 a 20): 5
Recursivo: 5! = 120
Iterativo: 5! = 120
Resultados iguais: sim
```
Para `n = 20`, o resultado é `2432902008176640000`.

> 💡 *Dica: sem caso-base a recursão nunca para e a pilha estoura. Aqui o caso-base é `n <= 1`, que devolve `1`. O `21!` vale mais de 5 × 10¹⁹ e não cabe em 64 bits.*

**✅ Critérios de aceite:**
- [ ] `0!` = `1`, `5!` = `120` e `20!` = `2432902008176640000` nas duas versões
- [ ] A versão recursiva tem caso-base e se aproxima dele a cada chamada
- [ ] Rejeita `-1`, `21` e texto
- [ ] Comentário explicando o limite de `20`

---

## 🟡 Nível Intermediário

### 🟡 I1 – Array dinâmico com `new[]` e depois `std::vector`

📄 **Arquivo base:** `base/i1_array_dinamico.cpp` · **Vale:** 1,5 ponto(s)

O tamanho de um array comum precisa ser conhecido em tempo de compilação. Com `new[]`, o usuário decide o tamanho durante a execução. É a técnica que a apostila ensina, e depois você vê como o `std::vector` faz o mesmo trabalho com menos risco.

**O que fazer:**
1. Leia a quantidade `n` (entre `1` e `1000`) e valide.
2. Aloque `double* dados = new double[n];` e leia os `n` valores (`Valor 1: `, `Valor 2: `...). Se uma leitura falhar, **libere a memória antes de sair**.
3. Escreva `double mediaArray(const double* dados, int n)` e mostre a média com duas casas decimais.
4. Copie os valores para um `std::vector<double>` (com `push_back`), libere o array com `delete[]` e atribua `nullptr` ao ponteiro.
5. Escreva `double mediaVetor(const std::vector<double>& dados)` e mostre a média do vetor. As duas médias devem ser iguais.

**Exemplo de execução** (o que o usuário digita aparece depois dos dois-pontos):
```text
Quantidade (1 a 1000): 4
Valor 1: 7
Valor 2: 8
Valor 3: 6
Valor 4: 9
Media (array dinamico): 7.50
Media (std::vector): 7.50
```

> 💡 *Dica: memória criada com `new[]` é liberada com `delete[]` (e não `delete`). Depois de liberar, não use mais o ponteiro. Atribuir `nullptr` ajuda a evitar esse erro.*

**✅ Critérios de aceite:**
- [ ] O exemplo produz a saída mostrada
- [ ] Todo `new[]` tem um `delete[]` correspondente, inclusive no caminho de erro de leitura
- [ ] O ponteiro recebe `nullptr` depois de liberado
- [ ] As duas médias são calculadas por funções e coincidem
- [ ] `0`, `1001` e texto são rejeitados

---

### 🟡 I2 – Estatísticas devolvidas por referência

📄 **Arquivo base:** `base/i2_estatisticas_por_referencia.cpp` · **Vale:** 1,5 ponto(s)

Uma função só pode **devolver** um valor com `return`. Para entregar vários resultados de uma vez, usamos parâmetros por referência. Para **ler** um objeto grande sem copiá-lo, usamos `const T&`.

**O que fazer:**
1. Leia a quantidade `n` (entre `1` e `100`) e os `n` valores (`double`), guardando-os em um `std::vector<double>`. Valide as leituras.
2. Escreva `void estatisticas(const std::vector<double>& valores, double& soma, double& menor, double& maior)`. Ela **não pode** alterar o vetor nem fazer cópia dele.
3. Em `main`, chame a função e mostre soma, menor, maior e média (calculada em `main`), todos com duas casas decimais.

**Exemplo de execução** (o que o usuário digita aparece depois dos dois-pontos):
```text
Quantidade: 5
Valores: 4 9.5 1 7 3
Soma: 24.50
Menor: 1.00
Maior: 9.50
Media: 4.90
```

> 💡 *Dica: inicialize `menor` e `maior` com o **primeiro** elemento, e não com `0`. Assim a função funciona também para valores todos negativos.*

**✅ Critérios de aceite:**
- [ ] O exemplo produz a saída mostrada; para `-3 -1 -8` dá menor `-8.00`, maior `-1.00`
- [ ] O vetor é recebido como `const std::vector<double>&` e os três resultados como `double&`
- [ ] A função não imprime nada (quem imprime é `main`)
- [ ] `0`, `101` e texto são rejeitados

---

### 🟡 I3 – Funções que recebem e devolvem ponteiros

📄 **Arquivo base:** `base/i3_trocar_e_maior_com_ponteiros.cpp` · **Vale:** 1,5 ponto(s)

Funções com ponteiros precisam se proteger de dois problemas: ponteiro nulo e acesso além do array.

**O que fazer:**
1. Escreva `bool trocar(int* a, int* b)`: troca os valores apontados e devolve `true`. Se **qualquer** ponteiro for `nullptr`, não faz nada e devolve `false`.
2. Escreva `int* maiorElemento(int* inicio, int* fim)`: devolve o ponteiro para o **primeiro** maior elemento da faixa `[inicio, fim)` (`fim` aponta **uma posição depois** do último). Para faixa vazia (`inicio == fim`), devolve `nullptr`.
3. Em `main`, leia seis inteiros para `int v[6]`, encontre o maior, mostre seu valor e a **posição** (use `maior - v`), e troque-o com o primeiro elemento.
4. Mostre o array, teste `trocar(nullptr, &v[0])` e `maiorElemento(v, v)` e informe os resultados.

**Exemplo de execução** (o que o usuário digita aparece depois dos dois-pontos):
```text
Seis inteiros: 4 17 9 25 3 11
Maior: 25 (posicao 3)
Apos trocar com a primeira posicao: 25 17 9 4 3 11
Troca com ponteiro nulo: ignorada
Elemento maximo de faixa vazia: nulo
```

> 💡 *Dica: subtrair dois ponteiros do mesmo array dá a **distância em elementos**. A função não deve desreferenciar `fim`, pois ele aponta para fora da faixa.*

**✅ Critérios de aceite:**
- [ ] O exemplo produz a saída mostrada; com o maior já na primeira posição o array não muda
- [ ] As duas funções verificam `nullptr` / faixa vazia antes de desreferenciar
- [ ] `maiorElemento` percorre com ponteiros e não desreferencia `fim`
- [ ] A leitura é verificada

---

### 🟡 I4 – Fibonacci recursivo e o custo das chamadas

📄 **Arquivo base:** `base/i4_fibonacci_chamadas.cpp` · **Vale:** 1,5 ponto(s)

A sequência de Fibonacci é `0, 1, 1, 2, 3, 5, 8, ...`: cada termo é a soma dos dois anteriores (`fib(0) = 0` e `fib(1) = 1`). A versão recursiva é elegante, mas repete muito trabalho. Vamos medir isso.

**O que fazer:**
1. Leia `n` (entre `0` e `30`) e valide.
2. Escreva `long long fibRecursivo(int n, long long& chamadas)`. Ela soma `1` a `chamadas` **a cada chamada** (inclusive as dos casos-base) e usa dois casos-base: `0` e `1`.
3. Escreva `long long fibIterativo(int n)` com laço.
4. Mostre os dois resultados e o número de chamadas recursivas.
5. Em um comentário, diga o que acontece com o número de chamadas quando `n` cresce (compare `n = 10`, `20` e `30`).

**Exemplo de execução** (o que o usuário digita aparece depois dos dois-pontos):
```text
N (0 a 30): 10
Fibonacci(10) recursivo = 55 (177 chamadas)
Fibonacci(10) iterativo = 55
```
Para `n = 20` são `21891` chamadas e, para `n = 30`, `2692537`.

> 💡 *Dica: cada chamada com `n >= 2` gera outras **duas**; por isso o número de chamadas cresce de forma exponencial. Para `n` grande, prefira o laço (ou memorização, que você pode estudar depois).*

**✅ Critérios de aceite:**
- [ ] Resultados corretos para `n = 0`, `1`, `10` e `20`; contagem de chamadas igual à do exemplo
- [ ] A recursão tem os dois casos-base e as chamadas são contadas por referência (`long long&`)
- [ ] Rejeita `-1`, `31` e texto
- [ ] Comentário sobre o crescimento das chamadas

---

### 🟡 I5 – Inverter um array com dois ponteiros

📄 **Arquivo base:** `base/i5_inverter_array_ponteiros.cpp` · **Vale:** 1,5 ponto(s)

Inverter um array "no lugar" é um clássico: um ponteiro parte do início, outro parte do fim, eles trocam os valores e se aproximam até se encontrar.

**O que fazer:**
1. Leia `n` (entre `1` e `20`) e valide. Depois leia os `n` valores para `int v[20]`.
2. Escreva `void inverter(int* inicio, int* fim)`, onde a faixa é `[inicio, fim)` (`fim` aponta **uma posição depois** do último elemento). **Não use `[]`** dentro da função: apenas `*`, `++` e `--`.
3. Escreva `void imprimir(const char* rotulo, const int* inicio, const int* fim)`, que mostra o rótulo e os elementos.
4. Mostre o array original, inverta-o e mostre o resultado.

**Exemplo de execução** (o que o usuário digita aparece depois dos dois-pontos):
```text
Quantidade: 5
Valores: 1 2 3 4 5
Original: 1 2 3 4 5
Invertido: 5 4 3 2 1
```

> 💡 *Dica: como `fim` aponta para fora da faixa, comece com `--fim` para que ele aponte para o último elemento. Continue enquanto `inicio < fim`. Funciona para quantidade par e ímpar.*

**✅ Critérios de aceite:**
- [ ] O exemplo produz a saída mostrada; `n = 1` e `n = 2` também funcionam (`7` e `8 9` → `9 8`)
- [ ] `inverter` e `imprimir` usam apenas ponteiros, sem `[]`
- [ ] Nunca desreferencia `fim` e não acessa fora do array
- [ ] A leitura é verificada e `0` e `21` são rejeitados

---

## 🔴 Nível Difícil

### 🔴 D1 – Projeto da unidade: Análise de notas da turma

📄 **Arquivo base:** `base/d1_analise_de_notas.cpp` · **Vale:** 2,0 ponto(s)

**Projeto integrador da Unidade 3.** Construa um programa modular que analisa as notas de uma turma. Ele roda a análise duas vezes: com um **array dinâmico** e com um **`std::vector`**. As duas versões devem dar o mesmo resultado.

**O que fazer:**
1. Leia o tamanho da turma `n` (entre `1` e `50`) e valide.
2. Aloque `double* notas = new double[n];` e leia as `n` notas (`Nota 1: `, `Nota 2: `...). Cada nota deve estar entre `0` e `10`; senão mostre `Nota invalida (use 0 a 10).` em `std::cerr`, **libere a memória** e devolva `1`.
3. Escreva as funções (declare os protótipos no topo e defina depois de `main`):
   - `double calcularMedia(const double* notas, int quantidade)`: percorre os dados **com ponteiros**;
   - `double encontrarMaior(const double* notas, int quantidade)`: também com ponteiros;
   - `void atualizarEstatistica(double nota, int& aprovados, int& reprovados)`: atualiza os contadores **por referência** (aprovado: nota `>= 6,0`);
   - `void relatorio(const double* notas, int quantidade)`: mostra os quatro resultados com duas casas decimais.
4. Mostre `--- Versao com array dinamico ---` e chame `relatorio`.
5. Copie as notas para um `std::vector<double>`, libere o array (`delete[]`, depois `nullptr`) e mostre `--- Versao com std::vector ---`. Chame o **mesmo** `relatorio` usando `vetor.data()` e `vetor.size()`.
6. No topo do arquivo, documente em comentário **três casos de teste** que você executou (entradas e saídas).

**Exemplo de execução** (o que o usuário digita aparece depois dos dois-pontos):
```text
Tamanho da turma (1 a 50): 5
Nota 1: 7.5
Nota 2: 4
Nota 3: 9
Nota 4: 6
Nota 5: 10
--- Versao com array dinamico ---
Media: 7.30
Maior nota: 10.00
Aprovados: 4
Reprovados: 1
--- Versao com std::vector ---
Media: 7.30
Maior nota: 10.00
Aprovados: 4
Reprovados: 1
```

> 💡 *Dica: os protótipos com `const double*` aceitam tanto o array dinâmico quanto `vetor.data()`. É isso que permite reaproveitar as mesmas funções nas duas versões. Nunca acesse `notas[quantidade]`: o último índice válido é `quantidade - 1`.*

**✅ Critérios de aceite:**
- [ ] O exemplo produz a saída mostrada, e as duas versões coincidem
- [ ] Organização em funções com protótipos no topo (25%)
- [ ] Passagem por referência em `atualizarEstatistica` e `const` nos dados de entrada (20%)
- [ ] Ponteiros percorrem os dados sem acessar fora dos limites (20%)
- [ ] `new[]` com `delete[]` correspondente, inclusive no erro de leitura (20%)
- [ ] Tamanhos e notas inválidos são rejeitados; três testes documentados no topo (15%)

---

### 🔴 D2 – Busca binária recursiva e iterativa

📄 **Arquivo base:** `base/d2_busca_binaria.cpp` · **Vale:** 2,0 ponto(s)

Em um array **ordenado**, a busca binária olha o elemento do meio e descarta metade dos candidatos a cada passo.

**O que fazer:**
1. Leia `n` (entre `1` e `20`) e os `n` valores (`int v[20]`). Verifique as leituras.
2. Escreva `bool estaOrdenado(const int* v, int n)`. Se os valores **não** estiverem em ordem crescente, mostre `Valores fora de ordem crescente.` em `std::cerr` e devolva `1`.
3. Leia o `alvo` a procurar.
4. Escreva **duas** funções de busca que devolvem o **índice** do alvo ou `-1`, e contam os passos por referência (cada vez que o elemento do meio é examinado conta **1** passo):
   - `int buscaRecursiva(const int* v, int inicio, int fim, int alvo, int& passos)` (`fim` é inclusivo);
   - `int buscaIterativa(const int* v, int n, int alvo, int& passos)`.
5. Mostre o resultado das duas. Elas devem concordar quanto ao índice **e** à quantidade de passos.

**Exemplo de execução** (o que o usuário digita aparece depois dos dois-pontos):
```text
Quantidade: 8
Valores (ordem crescente): 2 5 8 12 16 23 38 56
Alvo: 23
Recursiva: posicao 5 (2 passo(s))
Iterativa: posicao 5 (2 passo(s))
```
Para o alvo `7` nos mesmos valores:
```text
Recursiva: nao encontrado (3 passo(s))
Iterativa: nao encontrado (3 passo(s))
```

> 💡 *Dica: calcule o meio como `inicio + (fim - inicio) / 2`. O caso-base da recursão é `inicio > fim` (faixa vazia, alvo ausente). A cada chamada, a faixa diminui, e é isso que garante a parada.*

**✅ Critérios de aceite:**
- [ ] Os dois exemplos produzem a saída mostrada; alvos no início e no fim do array também são achados
- [ ] A busca recursiva tem caso-base e reduz a faixa a cada chamada
- [ ] As duas buscas dão o mesmo índice e a mesma contagem de passos
- [ ] Valores desordenados, `n` fora de `1..20` e texto são rejeitados

---

### 🔴 D3 – Matriz dinâmica e sua transposta

📄 **Arquivo base:** `base/d3_matriz_dinamica.cpp` · **Vale:** 2,0 ponto(s)

Uma matriz `linhas x colunas` alocada dinamicamente é um array de ponteiros, e cada ponteiro aponta para uma linha. Alocar é fácil. O desafio é **liberar na ordem certa**.

**O que fazer:**
1. Leia `linhas` e `colunas` (cada uma entre `1` e `10`) e valide.
2. Escreva as funções:
   - `int** criarMatriz(int linhas, int colunas)`: aloca o array de ponteiros e cada linha com `new int[colunas]{}`;
   - `void liberarMatriz(int** m, int linhas)`: libera **cada linha** com `delete[]` e **depois** o array de ponteiros;
   - `int** transpor(int** m, int linhas, int colunas)`: devolve uma **nova** matriz `colunas x linhas`;
   - `void imprimir(int** m, int linhas, int colunas)`: mostra cada elemento com `std::setw(4)`.
3. Preencha `m[i][j]` com `i * colunas + j + 1` (1, 2, 3, ...).
4. Mostre a matriz, a transposta e a **soma de cada linha** da matriz original (uma linha de texto, valores separados por espaço).
5. Libere as **duas** matrizes antes de terminar.

**Exemplo de execução** (o que o usuário digita aparece depois dos dois-pontos):
```text
Linhas (1 a 10): 2
Colunas (1 a 10): 3
Matriz 2x3:
   1   2   3
   4   5   6
Transposta 3x2:
   1   4
   2   5
   3   6
Soma por linha: 6 15
```

> 💡 *Dica: se você só fizer `delete[] m`, as linhas ficam "perdidas" (vazamento). Cada `new` precisa de um `delete[]`. Em Linux ou WSL, compile com `-fsanitize=address` para o compilador apontar vazamentos.*

**✅ Critérios de aceite:**
- [ ] O exemplo produz a saída mostrada; `1x1` e `3x1` também funcionam
- [ ] As funções pedidas existem e `liberarMatriz` libera linhas e depois o array de ponteiros
- [ ] As duas matrizes (original e transposta) são liberadas; não há vazamento nem acesso fora dos limites
- [ ] Valores fora de `1..10` e texto são rejeitados

---

### 🔴 D4 – Torre de Hanói

📄 **Arquivo base:** `base/d4_torre_de_hanoi.cpp` · **Vale:** 2,0 ponto(s)

Na Torre de Hanói há três pinos (`A`, `B` e `C`) e `n` discos empilhados no `A`, do maior (embaixo) para o menor (em cima). O objetivo é levar todos para o `C`, movendo **um disco por vez** e **nunca** pondo um disco maior sobre um menor. A solução recursiva cabe em poucas linhas:

para mover `n` discos de `origem` para `destino` usando `auxiliar`: (1) mova `n-1` discos de `origem` para `auxiliar`; (2) mova o disco `n` de `origem` para `destino`; (3) mova os `n-1` discos de `auxiliar` para `destino`.

**O que fazer:**
1. Leia `n` (entre `1` e `10`) e valide.
2. Escreva `void hanoi(int n, char origem, char destino, char auxiliar, int& movimentos, bool imprimir)`. O caso-base é `n == 0`. A função soma `1` em `movimentos` a cada disco movido e, se `imprimir` for `true`, mostra `Mover disco D de X para Y`.
3. Imprima os movimentos **somente** quando `n <= 4`. Para `n` maior, mostre apenas `Movimentos nao listados (n > 4).`
4. Mostre `Total de movimentos: ...` e o mínimo teórico `Minimo teorico (2^n - 1): ...`, calculado **sem** usar a função recursiva (por exemplo, com um laço ou `(1 << n) - 1`).

**Exemplo de execução** (o que o usuário digita aparece depois dos dois-pontos):
```text
Discos (1 a 10): 3
Mover disco 1 de A para C
Mover disco 2 de A para B
Mover disco 1 de C para B
Mover disco 3 de A para C
Mover disco 1 de B para A
Mover disco 2 de B para C
Mover disco 1 de A para C
Total de movimentos: 7
Minimo teorico (2^n - 1): 7
```
Para `n = 10`, o total é `1023`.

> 💡 *Dica: o segredo é trocar os papéis dos pinos nas duas chamadas recursivas: na primeira, o destino vira o `auxiliar`; na segunda, a origem vira o `auxiliar`. Teste com `n = 1` e `n = 2` antes de tentar `n = 3`.*

**✅ Critérios de aceite:**
- [ ] A sequência de movimentos para `n = 3` é exatamente a do exemplo
- [ ] O total confere com o mínimo teórico para `n = 1` a `10`
- [ ] A função tem caso-base e duas chamadas recursivas, e conta movimentos por referência
- [ ] `0`, `11` e texto são rejeitados

---

### 🔴 D5 – Mini-biblioteca de strings C com ponteiros

📄 **Arquivo base:** `base/d5_strings_com_ponteiros.cpp` · **Vale:** 2,0 ponto(s)

Uma "string C" é um array de `char` terminado por `'\0'`. Funções como `strlen` e `strcpy` apenas percorrem esse array com ponteiros. Aqui você escreve as suas.

**O que fazer:**
1. Leia **uma linha** de texto (até 99 caracteres) para `char texto[100]` com `std::cin.getline(texto, 100)`. Se a leitura falhar, mostre `Entrada invalida.` em `std::cerr` e devolva `1`.
2. Escreva as quatro funções **usando só ponteiros** (sem `[]`, sem `<cstring>`, sem `std::string`):
   - `int tamanho(const char* s)`: conta os caracteres até o `'\0'`;
   - `void copiar(char* destino, const char* origem)`: copia o texto e **o terminador**;
   - `int contarVogais(const char* s)`: conta `a e i o u`, em maiúsculas ou minúsculas;
   - `void maiusculas(char* s)`: converte `a..z` em `A..Z`, no próprio texto.
3. Copie o texto para `char copia[100]`, converta **a cópia** para maiúsculas e mostre os resultados. O texto original deve ficar intacto.

**Exemplo de execução** (o que o usuário digita aparece depois dos dois-pontos):
```text
Texto: Programacao em C++
Tamanho: 18
Vogais: 6
Copia em maiusculas: PROGRAMACAO EM C++
Original preservado: Programacao em C++
```

> 💡 *Dica: `while (*p != '\0') ++p;` percorre uma string C. A diferença `p - s` entre o ponteiro final e o inicial dá o tamanho. Para converter minúsculas, subtraia `'a' - 'A'` do caractere.*

**✅ Critérios de aceite:**
- [ ] O exemplo produz a saída mostrada; texto vazio dá `Tamanho: 0` e `Vogais: 0`
- [ ] As quatro funções não usam `[]`, `<cstring>` nem `std::string`
- [ ] `copiar` copia também o `'\0'` e o destino tem espaço suficiente
- [ ] O texto original não é alterado

---

## 📊 Tabela Resumo das Atividades

| Atividade | Tópico principal | Nível | Pontos | Arquivo base |
|-----------|------------------|-------|--------|--------------|
| F1 | Declaração (protótipo), definição e chamada de funções | 🟢 | 1,0 | `f1_calculadora_funcoes.cpp` |
| F2 | Passagem de parâmetros por valor e por referência | 🟢 | 1,0 | `f2_valor_ou_referencia.cpp` |
| F3 | Endereço (`&`), desreferenciação (`*`) e aritmética de ponteiros | 🟢 | 1,0 | `f3_array_e_ponteiros.cpp` |
| F4 | Parâmetros, tipos de retorno e `void` | 🟢 | 1,0 | `f4_funcoes_utilitarias.cpp` |
| F5 | Recursividade, caso-base e limites do tipo | 🟢 | 1,0 | `f5_fatorial.cpp` |
| I1 | `new[]`, `delete[]` e `std::vector` | 🟡 | 1,5 | `i1_array_dinamico.cpp` |
| I2 | `const T&` para entrada e `T&` para saída | 🟡 | 1,5 | `i2_estatisticas_por_referencia.cpp` |
| I3 | Ponteiros como parâmetros e retorno, `nullptr` e faixas `[inicio, fim)` | 🟡 | 1,5 | `i3_trocar_e_maior_com_ponteiros.cpp` |
| I4 | Recursão com dois casos-base e contagem de chamadas por referência | 🟡 | 1,5 | `i4_fibonacci_chamadas.cpp` |
| I5 | Aritmética de ponteiros e trabalho no próprio array | 🟡 | 1,5 | `i5_inverter_array_ponteiros.cpp` |
| D1 | Integração: funções, referência, ponteiros e memória dinâmica | 🔴 | 2,0 | `d1_analise_de_notas.cpp` |
| D2 | Recursão sobre faixas de um array, ponteiros `const` e contagem por referência | 🔴 | 2,0 | `d2_busca_binaria.cpp` |
| D3 | `new`/`delete[]` com ponteiro para ponteiro e liberação em duas etapas | 🔴 | 2,0 | `d3_matriz_dinamica.cpp` |
| D4 | Recursão com duas chamadas, caso-base e contagem por referência | 🔴 | 2,0 | `d4_torre_de_hanoi.cpp` |
| D5 | Ponteiros `char*`, terminador `'\0'` e funções sem usar `[]` | 🔴 | 2,0 | `d5_strings_com_ponteiros.cpp` |

## 🧾 Ficha de pontuação

Marque o que concluiu antes de entregar (o professor confere na correção).

| Atividade | Pontos | Concluí? |
|-----------|--------|----------|
| 🟢 F1 | 1,0 | [ ] |
| 🟢 F2 | 1,0 | [ ] |
| 🟢 F3 | 1,0 | [ ] |
| 🟢 F4 | 1,0 | [ ] |
| 🟢 F5 | 1,0 | [ ] |
| 🟡 I1 | 1,5 | [ ] |
| 🟡 I2 | 1,5 | [ ] |
| 🟡 I3 | 1,5 | [ ] |
| 🟡 I4 | 1,5 | [ ] |
| 🟡 I5 | 1,5 | [ ] |
| 🔴 D1 | 2,0 | [ ] |
| 🔴 D2 | 2,0 | [ ] |
| 🔴 D3 | 2,0 | [ ] |
| 🔴 D4 | 2,0 | [ ] |
| 🔴 D5 | 2,0 | [ ] |

- Soma dos fáceis (teto 4,0): ____
- Soma dos intermediários (teto 4,5): ____
- Soma dos difíceis (teto 5,0): ____
- **Nota da unidade (soma, no máximo 10,0): ____**

*Bons estudos! Lembre-se: compile sempre com `-std=c++17 -Wall -Wextra` e leia os avisos. 💻*
