# 🛠️ Atividades – Unidade 2: Estruturas de controle
**Curso de Capacitação em Desenvolvimento Full Stack – ITEAM**
Módulo 08 – Linguagem de Programação C++
Professor: Msc. Hygo Sousa De Oliveira

> **Conteúdo da apostila:** Unidade 2, seções 2.1 a 2.5 (condicionais, repetição, `break`/`continue`/`goto`, exceções)
> **Tópicos:** `if`/`else`/`switch` · `for`/`while`/`do-while` · `break`, `continue` e `goto` · `try`/`catch`/`throw`

---

## 📌 Como resolver e entregar

> Faça isto **antes de começar a resolver as atividades**.

Faça as atividades na **sua própria cópia** do repositório do curso. Se ainda não criou a sua, siga o passo a passo de [COMO-OBTER-AS-ATIVIDADES.md](../COMO-OBTER-AS-ATIVIDADES.md).

### 1. Copie a pasta `base/` para `resolucao/`

```bash
cp -r unidade-02/base unidade-02/resolucao
```

No PowerShell do Windows: `Copy-Item -Recurse unidade-02\base unidade-02\resolucao`.

> Não altere os arquivos dentro de `base/`: eles pertencem ao professor e podem ser substituídos quando você baixar atualizações.

### 2. Resolva e compile

Abra o arquivo da atividade dentro de `resolucao/`, complete os trechos marcados com `TODO` e compile **sempre com avisos ativados**:

```bash
cd unidade-02/resolucao
g++ -std=c++17 -Wall -Wextra f1_exemplo.cpp -o f1.exe
./f1.exe          # no Windows (CMD/PowerShell): .\f1.exe
```

Troque `f1_exemplo.cpp` e `f1.exe` pelo nome do arquivo da atividade. Atividades com arquivos de dados (`.txt`, `.csv`) devem ser executadas **de dentro da pasta `resolucao/`**.

### 3. Salve o seu progresso na sua cópia

```bash
git add unidade-02/resolucao
git commit -m "feat: unidade 2 - atividades F1 a F3"
git push origin main
```

Faça commits pequenos e frequentes: eles mostram o seu processo. **Não envie arquivos `.exe`** (o `.gitignore` já os ignora).

### 4. Entregue

Quando terminar, marque a entrega com a tag desta unidade e envie ao professor o link da sua cópia:

```bash
git tag atividade-unidade-02
git push origin atividade-unidade-02
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

### 🟢 F1 – Média e situação do aluno

📄 **Arquivo base:** `base/f1_media_e_situacao.cpp` · **Vale:** 1,0 ponto(s)

A secretaria quer saber a situação de um aluno a partir de três notas.

**O que fazer:**
1. Leia três notas (`double`) e verifique a leitura.
2. Calcule a média aritmética e exiba-a com duas casas decimais.
3. Classifique: **Aprovado** (média ≥ 6,0), **Recuperacao** (média ≥ 4,0 e < 6,0) ou **Reprovado** (média < 4,0).
4. Em um comentário, documente os limites usados e teste os casos de fronteira (`6.0` e `4.0`).

**Exemplo de execução** (o que o usuário digita aparece depois dos dois-pontos):
```text
Tres notas: 8 5 7
Media: 6.67
Situacao: Aprovado
```

> 💡 *Dica: o `else if` só é avaliado se as condições anteriores forem falsas. Por isso a ordem dos testes importa.*

**✅ Critérios de aceite:**
- [ ] `8 5 7` resulta em `Aprovado`; `5 4 3` em `Recuperacao` e `2 3 4` em `Reprovado`
- [ ] As fronteiras `6.0` e `4.0` caem na classe certa
- [ ] Verifica a leitura e usa `else if` encadeado
- [ ] Comentário documentando os limites

---

### 🟢 F2 – Classificador de temperatura

📄 **Arquivo base:** `base/f2_classificador_temperatura.cpp` · **Vale:** 1,0 ponto(s)

Um sistema de monitoramento climático precisa categorizar temperaturas ambiente.

| Faixa | Classificação |
|-------|---------------|
| abaixo de 0 °C | Congelante |
| de 0 a 14 °C | Frio |
| de 15 a 24 °C | Agradavel |
| de 25 a 34 °C | Quente |
| 35 °C ou mais | Muito quente |

**O que fazer:**
1. Leia uma temperatura em Celsius (`double`) e verifique a leitura.
2. Exiba a temperatura e a classificação conforme a tabela.

**Exemplo de execução** (o que o usuário digita aparece depois dos dois-pontos):
```text
Temperatura em Celsius: 28
Temperatura: 28
Classificacao: Quente
```

> 💡 *Dica: valores como `14.5` ficam entre as faixas se você usar só inteiros. Teste com `14.5`, `24.9` e `34.99` e decida onde cada um se encaixa.*

**✅ Critérios de aceite:**
- [ ] Classifica corretamente `-3`, `0`, `14`, `15`, `24`, `25`, `34` e `35`
- [ ] Todo valor real cai em exatamente uma faixa, inclusive `14.5` (não há "buracos")
- [ ] Verifica a leitura

---

### 🟢 F3 – Tabuada com `for` e com `while`

📄 **Arquivo base:** `base/f3_tabuada_for_while.cpp` · **Vale:** 1,0 ponto(s)

Vamos gerar a tabuada de um número de duas formas e comparar os códigos.

**O que fazer:**
1. Leia um número inteiro e verifique a leitura.
2. Exiba a tabuada de 1 a 10 usando **`for`**, sob o título `Com for:`.
3. Exiba a mesma tabuada usando **`while`**, sob o título `Com while:`.
4. Em um comentário, diga em que situação cada laço é mais natural.

**Exemplo de execução** (o que o usuário digita aparece depois dos dois-pontos; as linhas `...` representam os valores de 2 a 9):
```text
Numero: 7
Com for:
7 x 1 = 7
...
7 x 10 = 70
Com while:
7 x 1 = 7
...
7 x 10 = 70
```

> 💡 *Dica: no `while`, a variável do contador precisa ser inicializada antes do laço e atualizada **dentro** dele. Esquecer a atualização cria um laço infinito.*

**✅ Critérios de aceite:**
- [ ] As duas tabuadas são idênticas, de `x 1` até `x 10`
- [ ] O `for` concentra inicialização, condição e atualização; o `while` atualiza o contador no corpo
- [ ] Nenhum laço infinito
- [ ] Comentário comparando os dois laços

---

### 🟢 F4 – Soma de 1 a N e lista de pares

📄 **Arquivo base:** `base/f4_soma_e_pares.cpp` · **Vale:** 1,0 ponto(s)

Um professor quer somar os números de 1 até N e listar os pares nesse intervalo.

**O que fazer:**
1. Leia `N` (inteiro) e valide: `N` deve ser maior que zero. Caso contrário, escreva `Entrada invalida.` em `std::cerr` e devolva `1`.
2. Calcule a soma de `1` até `N` com um laço (**sem** usar a fórmula `N*(N+1)/2`).
3. Exiba também todos os números pares de `1` até `N`, separados por espaço, e quantos são.

**Exemplo de execução** (o que o usuário digita aparece depois dos dois-pontos):
```text
N: 10
Soma de 1 a 10: 55
Pares: 2 4 6 8 10
Quantidade de pares: 5
```

> 💡 *Dica: um acumulador começa em zero (`int soma{0};`) e recebe `soma += i;` a cada volta. Um número `i` é par quando `i % 2 == 0`.*

**✅ Critérios de aceite:**
- [ ] Resultado correto para `N = 10` (`55` e cinco pares) e para `N = 1`
- [ ] Rejeita `0`, negativos e texto
- [ ] A soma é feita por laço, com acumulador inicializado em zero

---

### 🟢 F5 – `break` e `continue` na prática

📄 **Arquivo base:** `base/f5_break_e_continue.cpp` · **Vale:** 1,0 ponto(s)

Imprima os números de 1 a 20 **ignorando** os múltiplos de 3 e **parando** assim que chegar ao 17.

**O que fazer:**
1. Use um laço `for` de `1` a `20`.
2. Quando o número for múltiplo de 3, use **`continue`** para pular a impressão.
3. Quando o número for `17`, use **`break`** para encerrar o laço (o `17` não deve ser impresso).
4. Em um comentário, explique a diferença entre `break` e `continue`.

**Saída esperada:**
```text
1 2 4 5 7 8 10 11 13 14 16
```

> 💡 *Dica: `continue` pula só o resto da volta atual; `break` encerra o laço inteiro. A ordem dos dois `if` não muda o resultado aqui, mas pense por quê.*

**✅ Critérios de aceite:**
- [ ] A sequência impressa é a esperada (um espaço no fim da linha é tolerado)
- [ ] Usa `continue` para os múltiplos de 3 e `break` no 17
- [ ] Comentário explicando a diferença entre os dois comandos

---

## 🟡 Nível Intermediário

### 🟡 I1 – Calculadora com menu e `switch`

📄 **Arquivo base:** `base/i1_calculadora_switch.cpp` · **Vale:** 1,5 ponto(s)

Uma calculadora de bancada oferece quatro operações por um menu numérico.

```text
1 - Somar
2 - Subtrair
3 - Multiplicar
4 - Dividir
```

**O que fazer:**
1. Mostre o menu, leia a opção e depois leia dois números (`double`). Verifique cada leitura.
2. Use **`switch`** para executar a operação escolhida e mostrar `Resultado: ...`.
3. Opção fora de `1..4`: mostre `Opcao invalida`.
4. Divisão por zero: mostre `Divisao por zero` em vez de um resultado.
5. Não esqueça o `break` de cada `case`. Em um comentário, explique o que aconteceria sem ele.

**Exemplo de execução** (o que o usuário digita aparece depois dos dois-pontos):
```text
Opcao: 4
Dois numeros: 10 4
Resultado: 2.5
```

> 💡 *Dica: `switch` só aceita tipos inteiros ou enumerações. Por isso a opção é um `int`, e não um `double`.*

**✅ Critérios de aceite:**
- [ ] As quatro operações funcionam e usam `switch` com `break` em cada `case`
- [ ] `default` trata a opção inválida
- [ ] A divisão por zero não trava o programa
- [ ] Comentário sobre a falta do `break` (*fall-through*)

---

### 🟡 I2 – Validando idade com exceções

📄 **Arquivo base:** `base/i2_excecao_idade.cpp` · **Vale:** 1,5 ponto(s)

Um cadastro não pode aceitar idades impossíveis. Em vez de devolver códigos de erro, a função validadora **lança uma exceção**.

**O que fazer:**
1. Escreva a função `void validarIdade(int idade)`. Ela lança `std::invalid_argument` com a mensagem `Idade negativa` se a idade for menor que `0`, e `std::out_of_range` com a mensagem `Idade acima de 150` se passar de `150`.
2. Em `main`, leia a idade e chame a função dentro de um bloco `try`.
3. Capture **as duas exceções em blocos `catch` separados**, mostrando `Erro: ` seguido de `erro.what()` em `std::cerr` e devolvendo `1`.
4. Se a idade for válida, mostre `Idade valida: N`.
5. Teste com `-5`, `200`, `30` e com texto (`abc`). Texto não é exceção: trate a leitura com `if`.

**Exemplo de execução** (o que o usuário digita aparece depois dos dois-pontos):
```text
Idade: 30
Idade valida: 30
```
```text
Idade: -5
Erro: Idade negativa
```

> 💡 *Dica: `std::invalid_argument` e `std::out_of_range` ficam em `<stdexcept>`. Capture por referência constante: `catch (const std::invalid_argument& erro)`.*

**✅ Critérios de aceite:**
- [ ] A função lança as duas exceções com as mensagens pedidas
- [ ] Dois `catch` separados, com mensagens em `std::cerr` e código de saída `1`
- [ ] Idade válida mostra `Idade valida: N`
- [ ] A leitura inválida (texto) é tratada sem exceção

---

### 🟡 I3 – Leitura de nota com `do-while`

📄 **Arquivo base:** `base/i3_nota_dowhile.cpp` · **Vale:** 1,5 ponto(s)

Um sistema só deve seguir adiante quando receber uma nota válida: um número entre `0` e `10`.

**O que fazer:**
1. Use **`do-while`** para pedir a nota até que seja válida, contando as tentativas.
2. Se o usuário digitar **texto**, o `std::cin` entra em estado de erro. Limpe-o com `std::cin.clear()` e descarte a linha com `std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n')`.
3. Se digitar um **número fora do intervalo**, avise `Nota fora do intervalo (0 a 10)`.
4. Ao final, mostre `Nota registrada: X` e `Tentativas: N`.
5. Se a entrada acabar (`std::cin.eof()`), encerre com `1` para não ficar em laço infinito.

**Exemplo de execução** (o que o usuário digita aparece depois dos dois-pontos):
```text
Nota (0 a 10): abc
Entrada invalida
Nota (0 a 10): 15
Nota fora do intervalo (0 a 10)
Nota (0 a 10): -1
Nota fora do intervalo (0 a 10)
Nota (0 a 10): 8.5
Nota registrada: 8.5
Tentativas: 4
```

> 💡 *Dica: sem `clear()`, o `cin` continua em erro e toda leitura seguinte falha. Sem `ignore()`, o texto digitado continua no buffer e causa erro de novo.*

**✅ Critérios de aceite:**
- [ ] A sequência `abc`, `15`, `-1`, `8.5` termina com `Nota registrada: 8.5` e `Tentativas: 4`
- [ ] Usa `do-while` e limpa o estado de erro e o buffer
- [ ] Trata o fim da entrada sem laço infinito

---

### 🟡 I4 – Números primos até N

📄 **Arquivo base:** `base/i4_numeros_primos.cpp` · **Vale:** 1,5 ponto(s)

Um número primo só é divisível por `1` e por ele mesmo. Vamos listar todos os primos até `N`.

**O que fazer:**
1. Leia `N` (inteiro, `N >= 2`) e valide.
2. Para cada `n` de `2` até `N`, descubra se é primo com um **laço interno** que testa divisores `d` de `2` até que `d * d > n`.
3. Assim que achar um divisor, marque o número como não primo e use **`break`** para sair do laço interno.
4. Mostre os primos em uma linha, separados por espaço, e o total.

**Exemplo de execução** (o que o usuário digita aparece depois dos dois-pontos):
```text
N: 30
Primos: 2 3 5 7 11 13 17 19 23 29
Total: 10 primos
```

> 💡 *Dica: basta testar divisores até a raiz quadrada de `n`. Por isso a condição `d * d <= n`. Declare a variável booleana `ehPrimo` **dentro** do laço externo, para ela voltar a `true` a cada número.*

**✅ Critérios de aceite:**
- [ ] Para `N = 30`, lista os 10 primos corretos (`1` e os compostos não aparecem)
- [ ] Usa laço interno com `break` ao encontrar divisor
- [ ] `N = 2` mostra apenas `2`; `N < 2` é rejeitado

---

### 🟡 I5 – Desenhando padrões com laços aninhados

📄 **Arquivo base:** `base/i5_padroes_com_lacos.cpp` · **Vale:** 1,5 ponto(s)

Laços aninhados são o jeito mais direto de desenhar figuras no terminal.

**O que fazer:**
1. Leia a altura `h` (inteiro entre `1` e `20`) e valide.
2. Desenhe um **triângulo retângulo** de asteriscos com `h` linhas (a linha `i` tem `i` asteriscos).
3. Deixe uma linha em branco e desenhe uma **pirâmide centralizada** com `h` linhas: a linha `i` tem `h - i` espaços seguidos de `2 * i - 1` asteriscos.

**Exemplo de execução para `h = 4`** (o que o usuário digita aparece depois dos dois-pontos):
```text
Altura: 4
*
**
***
****

   *
  ***
 *****
*******
```

> 💡 *Dica: use um laço externo para as linhas e laços internos para espaços e asteriscos. Imprima `'\n'` ao final de cada linha, depois dos laços internos.*

**✅ Critérios de aceite:**
- [ ] O desenho para `h = 4` é igual ao do exemplo
- [ ] Funciona para `h = 1` (um único `*` em cada figura) e rejeita valores fora de `1..20`
- [ ] Usa laços aninhados (sem escrever as linhas à mão)

---

## 🔴 Nível Difícil

### 🔴 D1 – Projeto da unidade: Menu interativo de operações

📄 **Arquivo base:** `base/d1_menu_interativo.cpp` · **Vale:** 2,0 ponto(s)

**Projeto integrador da Unidade 2.** Construa um programa que apresenta um menu repetidamente até o usuário escolher sair.

```text
===== MENU =====
1 - Somar
2 - Subtrair
3 - Multiplicar
4 - Dividir
0 - Sair
```

**O que fazer:**
1. Repita o menu com **`do-while`** até a opção `0`.
2. Use **`switch`** para executar a opção, com **`break`** em cada caso.
3. As operações (`1` a `4`) leem dois números e mostram `Resultado: ...`. A divisão por zero **lança** `std::invalid_argument("divisao por zero")`; o programa **captura** a exceção e mostra `Erro: divisao por zero`, sem encerrar.
4. Opção inválida (número fora do menu ou texto): mostre `Opcao invalida` e use **`continue`** para voltar ao menu sem executar nada. Se o texto foi digitado, limpe o estado de erro do `std::cin` e descarte a linha.
5. Ao escolher `0`, mostre `Encerrando` e termine. Se a entrada acabar antes, termine com código `1`.
6. **Não use `goto`.** Em um comentário, explique por que a solução fica mais clara sem ele.

**Exemplo de execução** (o que o usuário digita aparece depois dos dois-pontos; o menu foi omitido):
```text
Opcao: 1
Dois numeros: 2 3
Resultado: 5
Opcao: 4
Dois numeros: 10 0
Erro: divisao por zero
Opcao: 9
Opcao invalida
Opcao: 4
Dois numeros: 10 4
Resultado: 2.5
Opcao: 0
Encerrando
```

> 💡 *Dica: separe a divisão em uma função que lança a exceção. O `try`/`catch` fica dentro do laço, para um erro não derrubar o programa.*

**✅ Critérios de aceite:**
- [ ] A sequência do exemplo produz exatamente os resultados mostrados
- [ ] Usa `do-while`, `switch` com `break`, `continue` e `try`/`catch`
- [ ] A divisão por zero e a opção inválida não encerram o programa
- [ ] Sem `goto` e com o comentário justificando a escolha
- [ ] Documentação e legibilidade (nomes claros, cabeçalho de comentário)

---

### 🔴 D2 – Reescrevendo código com `goto`

📄 **Arquivo base:** `base/d2_goto_sem_goto.cpp` · **Vale:** 2,0 ponto(s)

A apostila diz que `goto` existe, mas costuma prejudicar a legibilidade. O arquivo base tem **duas** partes escritas com `goto`. Reescreva-as sem ele, mantendo o mesmo comportamento.

**Parte 1 – Soma até o zero:** lê números e soma até aparecer `0`.
**Parte 2 – Par que fecha as contas:** procura o primeiro par `(a, b)`, com `a` e `b` de `1` a `9`, tal que `a * b == 42` e `a + b == 13`. O `goto` serve para escapar dos dois laços de uma vez.

**O que fazer:**
1. Execute o arquivo base com a entrada `5`, `10`, `-3`, `0` e confirme a saída.
2. Reescreva a **parte 1** com `while` (ou `do-while`), sem `goto` e sem rótulos.
3. Reescreva a **parte 2** sem `goto`, usando uma variável booleana de controle (`achou`) e `break` nos dois laços.
4. Em um comentário, diga o que é mais fácil de ler em cada versão e por que escapar de laços aninhados é o caso em que o `goto` mais "tenta" os programadores.
5. A saída das duas partes não pode mudar.

**Exemplo de execução** (o que o usuário digita aparece depois dos dois-pontos):
```text
Numero (0 para encerrar): 5
Numero (0 para encerrar): 10
Numero (0 para encerrar): -3
Numero (0 para encerrar): 0
Soma: 12
Par encontrado: 6 e 7
```

> 💡 *Dica: na parte 2, a variável `achou` precisa ser consultada também na condição do laço externo (`a <= 9 && !achou`), senão ele continua rodando depois que o `break` interno sai.*

**✅ Critérios de aceite:**
- [ ] A saída das duas partes é igual à do arquivo base
- [ ] O arquivo final **não contém** a palavra `goto` (nem rótulos), exceto no comentário
- [ ] A parte 2 usa `achou` e `break` para sair dos dois laços
- [ ] Comentário comparando as versões

---

### 🔴 D3 – Jogo de adivinhação

📄 **Arquivo base:** `base/d3_jogo_adivinhacao.cpp` · **Vale:** 2,0 ponto(s)

O computador sorteia um número de `1` a `100` e o jogador tem **7 tentativas** para acertá-lo, recebendo dicas de *maior* ou *menor*.

Para que os testes sejam **reproduzíveis**, o sorteio usa uma **semente** informada pelo jogador. Este trecho já está pronto no arquivo base:

```cpp
std::mt19937 gerador(semente);
int segredo = static_cast<int>(gerador() % 100) + 1;
```

**O que fazer:**
1. Leia a semente (`unsigned int`) e valide a leitura.
2. Repita até **7 tentativas**. Em cada uma, leia o palpite.
3. Palpite fora de `1..100` ou texto: mostre `Palpite invalido`, limpe o estado do `std::cin` e **não** conte como tentativa.
4. Palpite menor que o segredo: `O numero e maior`; maior: `O numero e menor`.
5. Se acertar: `Acertou em N tentativa(s)!` e encerre o laço com `break`.
6. Se esgotar as 7 tentativas sem acertar: `Fim de jogo. O numero era X`.
7. Se a entrada acabar, encerre com código `1`.

**Exemplo de execução com a semente `42`** (o número sorteado é `43`; o que o usuário digita aparece depois dos dois-pontos):
```text
Semente: 42
Palpite: 50
O numero e menor
Palpite: 25
O numero e maior
Palpite: 43
Acertou em 3 tentativa(s)!
```

> 💡 *Dica: um `for` com contador de tentativas separado do índice do laço ajuda a não contar palpites inválidos.*

**✅ Critérios de aceite:**
- [ ] O exemplo com a semente `42` e os palpites `50`, `25`, `43` produz a saída mostrada
- [ ] Máximo de 7 tentativas e revelação do número ao perder
- [ ] Palpites inválidos não consomem tentativas e não travam o programa
- [ ] Usa `break` ao acertar

---

### 🔴 D4 – Caixa eletrônico: notas para um saque

📄 **Arquivo base:** `base/d4_caixa_eletronico.cpp` · **Vale:** 2,0 ponto(s)

Um caixa eletrônico tem notas de **R$ 100, 50, 20, 10 e 5**. Dado um valor de saque, ele deve usar o **menor número de notas** (começando pelas maiores).

**Regras de negócio:**
- O valor deve ser maior que zero e múltiplo de `5` (senão, `std::invalid_argument("Valor deve ser multiplo de 5")`).
- O valor máximo por saque é `5000` (senão, `std::out_of_range("Limite de saque excedido")`).

**O que fazer:**
1. Leia o valor e verifique a leitura.
2. Dentro de `try`, valide o valor (lançando as exceções acima) e calcule as notas com um laço sobre o vetor `NOTAS`, dividindo e usando o resto (`/` e `%`).
3. Mostre apenas as notas **que foram usadas**, no formato `N nota(s) de R$ V`. Use `continue` para pular as notas com quantidade zero.
4. Mostre `Erro: ` seguido da mensagem em `std::cerr` quando uma exceção for capturada, e devolva `1`.

**Exemplo de execução** (o que o usuário digita aparece depois dos dois-pontos):
```text
Valor do saque: 235
2 nota(s) de R$ 100
1 nota(s) de R$ 20
1 nota(s) de R$ 10
1 nota(s) de R$ 5
```
```text
Valor do saque: 237
Erro: Valor deve ser multiplo de 5
```

> 💡 *Dica: depois de usar `N` notas de valor `v`, o que sobra é `valor % v`. Você pode atualizar o próprio `valor` ou usar uma variável `restante`.*

**✅ Critérios de aceite:**
- [ ] `235` produz exatamente as quatro linhas mostradas; `5000` usa `50` notas de `100`
- [ ] `237`, `0`, `-10` e `5005` lançam e capturam as exceções corretas
- [ ] Notas com quantidade zero não são exibidas (uso de `continue`)
- [ ] Código de saída `1` em caso de erro

---

### 🔴 D5 – Estatísticas com valor sentinela

📄 **Arquivo base:** `base/d5_estatisticas_sentinela.cpp` · **Vale:** 2,0 ponto(s)

Um sensor envia leituras e o programa deve resumi-las. A leitura termina quando chega o valor `0` (o **sentinela**, que não entra nas estatísticas).

**O que fazer:**
1. Leia números reais (`double`) em um laço até encontrar `0`.
2. Se o usuário digitar **texto**, mostre `Entrada invalida, ignorada` em `std::cerr`, limpe o estado do `std::cin`, descarte a linha e **continue** lendo.
3. Calcule: **quantidade**, **soma**, **média**, **maior** e **menor** valor. Os valores podem ser negativos.
4. Se **nenhum valor** foi informado antes do `0`, lance `std::runtime_error("Nenhum valor informado")`. Capture em `main`, mostre `Erro: ...` em `std::cerr` e devolva `1`.
5. Mostre os resultados com duas casas decimais.
6. Se a entrada acabar sem o sentinela, encerre o laço e calcule com o que houver.

**Exemplo de execução** (o que o usuário digita aparece depois dos dois-pontos):
```text
Valor (0 para encerrar): 4.5
Valor (0 para encerrar): 8
Valor (0 para encerrar): abc
Entrada invalida, ignorada
Valor (0 para encerrar): 6.5
Valor (0 para encerrar): 0
Quantidade: 3
Soma: 19.00
Media: 6.33
Maior: 8.00
Menor: 4.50
```

> 💡 *Dica: inicialize `maior` e `menor` com o **primeiro** valor lido (e não com `0`), senão uma lista só de valores negativos ou só de positivos dá resposta errada.*

**✅ Critérios de aceite:**
- [ ] O exemplo produz os resultados mostrados
- [ ] Lista só de negativos (`-3`, `-1`, `0`) dá maior `-1.00` e menor `-3.00`
- [ ] Texto é ignorado sem encerrar o programa; lista vazia lança e captura a exceção
- [ ] Usa sentinela, acumuladores e formatação com duas casas decimais

---

## 📊 Tabela Resumo das Atividades

| Atividade | Tópico principal | Nível | Pontos | Arquivo base |
|-----------|------------------|-------|--------|--------------|
| F1 | `if` / `else if` / `else` | 🟢 | 1,0 | `f1_media_e_situacao.cpp` |
| F2 | `if` / `else if` com faixas de valores | 🟢 | 1,0 | `f2_classificador_temperatura.cpp` |
| F3 | `for`, `while` e comparação entre laços | 🟢 | 1,0 | `f3_tabuada_for_while.cpp` |
| F4 | Acumuladores e contadores | 🟢 | 1,0 | `f4_soma_e_pares.cpp` |
| F5 | Controle de fluxo dentro de laços | 🟢 | 1,0 | `f5_break_e_continue.cpp` |
| I1 | `switch`, `case`, `break` e `default` | 🟡 | 1,5 | `i1_calculadora_switch.cpp` |
| I2 | `try`, `catch` e `throw` com `<stdexcept>` | 🟡 | 1,5 | `i2_excecao_idade.cpp` |
| I3 | `do-while`, estado de erro de `std::cin` e validação | 🟡 | 1,5 | `i3_nota_dowhile.cpp` |
| I4 | Laços aninhados e `break` | 🟡 | 1,5 | `i4_numeros_primos.cpp` |
| I5 | Laços aninhados | 🟡 | 1,5 | `i5_padroes_com_lacos.cpp` |
| D1 | Integração: `do-while`, `switch`, `break`, `continue` e exceções | 🔴 | 2,0 | `d1_menu_interativo.cpp` |
| D2 | `goto`, saída de laços aninhados e alternativas estruturadas | 🔴 | 2,0 | `d2_goto_sem_goto.cpp` |
| D3 | Laço com limite de tentativas, dicas e tratamento de entrada | 🔴 | 2,0 | `d3_jogo_adivinhacao.cpp` |
| D4 | Laços, `continue` e exceções para validar regras de negócio | 🔴 | 2,0 | `d4_caixa_eletronico.cpp` |
| D5 | Laço com sentinela, acumuladores, máximo/mínimo e exceção | 🔴 | 2,0 | `d5_estatisticas_sentinela.cpp` |

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
