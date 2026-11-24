# 🛠️ Atividades – Unidade 1: Introdução ao C++
**Curso de Capacitação em Desenvolvimento Full Stack – ITEAM**
Módulo 08 – Linguagem de Programação C++
Professor: Msc. Hygo Sousa De Oliveira

> **Conteúdo da apostila:** Unidade 1, seções 1.1 a 1.6 (história, ambiente, variáveis e tipos, operadores, iostream, comentários)
> **Tópicos:** estrutura de um programa · compilação · variáveis e tipos · operadores · entrada e saída com `iostream` · comentários e documentação

---

## 📌 Como resolver e entregar

> Faça isto **antes de começar a resolver as atividades**.

Faça as atividades na **sua própria cópia** do repositório do curso. Se ainda não criou a sua, siga o passo a passo de [COMO-OBTER-AS-ATIVIDADES.md](../COMO-OBTER-AS-ATIVIDADES.md).

### 1. Copie a pasta `base/` para `resolucao/`

```bash
cp -r unidade-01/base unidade-01/resolucao
```

No PowerShell do Windows: `Copy-Item -Recurse unidade-01\base unidade-01\resolucao`.

> Não altere os arquivos dentro de `base/`: eles pertencem ao professor e podem ser substituídos quando você baixar atualizações.

### 2. Resolva e compile

Abra o arquivo da atividade dentro de `resolucao/`, complete os trechos marcados com `TODO` e compile **sempre com avisos ativados**:

```bash
cd unidade-01/resolucao
g++ -std=c++17 -Wall -Wextra f1_exemplo.cpp -o f1.exe
./f1.exe          # no Windows (CMD/PowerShell): .\f1.exe
```

Troque `f1_exemplo.cpp` e `f1.exe` pelo nome do arquivo da atividade. Atividades com arquivos de dados (`.txt`, `.csv`) devem ser executadas **de dentro da pasta `resolucao/`**.

### 3. Salve o seu progresso na sua cópia

```bash
git add unidade-01/resolucao
git commit -m "feat: unidade 1 - atividades F1 a F3"
git push origin main
```

Faça commits pequenos e frequentes: eles mostram o seu processo. **Não envie arquivos `.exe`** (o `.gitignore` já os ignora).

### 4. Entregue

Quando terminar, marque a entrega com a tag desta unidade e envie ao professor o link da sua cópia:

```bash
git tag atividade-unidade-01
git push origin atividade-unidade-01
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

### 🟢 F1 – Primeiro programa, compilado com avisos

📄 **Arquivo base:** `base/f1_primeiro_programa.cpp` · **Vale:** 1,0 ponto(s)

Todo projeto começa pelo ambiente. Aqui você prova que o seu compilador funciona e registra como chegou lá.

**O que fazer:**
1. Instale o compilador e confirme a versão com `g++ --version`.
2. Complete o arquivo base para exibir, em linhas separadas: `Ola, mundo!`, o **seu nome completo** e a frase `C++: eficiencia com abstracao.`
3. Compile com `-std=c++17 -Wall -Wextra` e execute o programa.
4. No topo do arquivo, em comentário, registre: a saída de `g++ --version`, o comando de compilação que você usou e, em uma ou duas frases, a diferença entre **editor**, **compilador** e **IDE**.

**Saída esperada (exemplo):**
```text
Ola, mundo!
Ana Lima Souza
C++: eficiencia com abstracao.
```

> 💡 *Dica: nas mensagens do programa, escreva sem acentos para evitar problemas de codificação no terminal do Windows. Os comentários podem ter acentos.*

**✅ Critérios de aceite:**
- [ ] Compila com `-std=c++17 -Wall -Wextra` sem erros e sem avisos
- [ ] Exibe as três linhas pedidas, cada uma em sua linha
- [ ] Comentário no topo com a versão do `g++`, o comando de compilação e a diferença entre editor, compilador e IDE

---

### 🟢 F2 – Variáveis e tipos: ficha de matrícula

📄 **Arquivo base:** `base/f2_variaveis_e_tipos.cpp` · **Vale:** 1,0 ponto(s)

A secretaria precisa de uma ficha simples de matrícula. Escolher o tipo certo para cada dado faz parte do trabalho.

**O que fazer:**
1. Declare e **inicialize com chaves** `{}` quatro variáveis: o nome do aluno, a idade, a altura em metros e a situação de matrícula (matriculado ou não).
2. Escolha o tipo apropriado para cada uma: `std::string`, `int`, `double` ou `bool`.
3. Exiba os quatro valores com rótulos. Para mostrar o `bool` como `true`/`false` (e não `1`/`0`), pesquise o manipulador `std::boolalpha`.

**Saída esperada (exemplo):**
```text
Nome: Ana Lima
Idade: 19
Altura: 1.68
Matriculado: true
```

> 💡 *Dica: `std::string` fica em `<string>`. Variáveis sem valor inicial têm conteúdo indefinido; inicialize sempre.*

**✅ Critérios de aceite:**
- [ ] Os quatro tipos escolhidos são os mais adequados (`std::string`, `int`, `double`, `bool`)
- [ ] Todas as variáveis são inicializadas com `{}` na declaração
- [ ] O `bool` aparece como `true` ou `false`
- [ ] Compila sem avisos

---

### 🟢 F3 – Operadores aritméticos e divisão por zero

📄 **Arquivo base:** `base/f3_operadores.cpp` · **Vale:** 1,0 ponto(s)

Uma calculadora de bancada precisa mostrar o resultado das quatro operações e do resto.

**O que fazer:**
1. Leia dois números inteiros `a` e `b` com `std::cin`, verificando se a leitura funcionou.
2. Exiba soma, subtração e produto.
3. **Antes de dividir**, verifique se `b` é zero. Se for, mostre `Divisao por zero: operacao nao realizada` e não faça as divisões.
4. Caso contrário, exiba o quociente **inteiro**, o quociente **real** (com `static_cast<double>`) e o resto.
5. Compare, em um comentário, o resultado de `7 / 2` com o de `7.0 / 2`.

**Exemplo de execução** (o que o usuário digita aparece depois dos dois-pontos):
```text
Informe dois inteiros: 7 2
Soma: 9
Subtracao: 5
Produto: 14
Quociente (inteiro): 3
Quociente (real): 3.5
Resto: 1
```

> 💡 *Dica: `static_cast<double>(a) / b` converte `a` antes da divisão. Se converter só o resultado, a divisão já terá sido inteira.*

**✅ Critérios de aceite:**
- [ ] Verifica a leitura (`if (!(std::cin >> a >> b))`) e encerra com código `1` em caso de erro
- [ ] Trata o divisor zero sem travar o programa
- [ ] Mostra a diferença entre divisão inteira e real
- [ ] Comentário comparando `7 / 2` e `7.0 / 2`

---

### 🟢 F4 – Conversor de temperatura

📄 **Arquivo base:** `base/f4_conversor_temperatura.cpp` · **Vale:** 1,0 ponto(s)

Uma estação meteorológica registra a temperatura em Celsius e precisa exibi-la também em Fahrenheit e Kelvin.

**Fórmulas:** `F = C × 9/5 + 32` e `K = C + 273,15`

**O que fazer:**
1. Leia a temperatura em Celsius (`double`) e verifique a leitura.
2. Calcule Fahrenheit e Kelvin.
3. Exiba os três valores com rótulos.

**Exemplo de execução** (o que o usuário digita aparece depois dos dois-pontos):
```text
Temperatura em Celsius: 36.5
Celsius: 36.5
Fahrenheit: 97.7
Kelvin: 309.65
```

> 💡 *Cuidado: em C++, `9 / 5` entre inteiros vale `1`, não `1.8`. Escreva `9.0 / 5.0` para obter a fração.*

**✅ Critérios de aceite:**
- [ ] O resultado para `36.5` é `97.7` e `309.65` (a divisão `9/5` não foi feita com inteiros)
- [ ] Usa `double` para as três temperaturas
- [ ] Verifica se a leitura funcionou

---

### 🟢 F5 – Troca de variáveis: achando o defeito

📄 **Arquivo base:** `base/f5_troca_de_variaveis.cpp` · **Vale:** 1,0 ponto(s)

O código do arquivo base tenta trocar os valores de `a` e `b`, mas imprime `20 20`. Descubra por quê e corrija de duas formas.

**O que fazer:**
1. Em um comentário, explique por que `a = b; b = a;` não troca os valores.
2. Corrija com uma **variável auxiliar**.
3. Corrija com **`std::swap`** (`<utility>`).
4. Antes de cada correção, volte `a` e `b` para `10` e `20`, para mostrar que a troca funciona a partir dos valores originais.

**Saída esperada:**
```text
Versao com defeito: a=20 b=20
Com variavel auxiliar: a=20 b=10
Com std::swap: a=20 b=10
```

> 💡 *Dica: depois de `a = b`, o valor antigo de `a` foi perdido. A variável auxiliar guarda esse valor antes de ele ser sobrescrito.*

**✅ Critérios de aceite:**
- [ ] Comentário explicando a causa do defeito
- [ ] As duas correções produzem `a=20 b=10`
- [ ] Usa `std::swap` com o `#include` correto

---

## 🟡 Nível Intermediário

### 🟡 I1 – Média de notas com formatação

📄 **Arquivo base:** `base/i1_media_formatada.cpp` · **Vale:** 1,5 ponto(s)

Um boletim precisa do nome completo do aluno e da média de duas notas com duas casas decimais.

**O que fazer:**
1. Leia o nome completo (com espaços) usando `std::getline`.
2. Leia duas notas (`double`) e verifique a leitura.
3. Calcule a média aritmética.
4. Exiba o nome e a média com **duas casas decimais**, usando `std::fixed` e `std::setprecision(2)` de `<iomanip>`.
5. Em um comentário, explique o efeito de `std::fixed` e de `std::setprecision(2)`. O que aconteceria sem `std::fixed`?

**Exemplo de execução** (o que o usuário digita aparece depois dos dois-pontos):
```text
Nome completo: Maria Souza
Nota 1 e nota 2: 10 5
Aluno: Maria Souza
Media: 7.50
```

> 💡 *Dica: sem `std::fixed`, `setprecision(2)` limita o total de dígitos significativos, e a média `7.5` apareceria como `7.5`.*

**✅ Critérios de aceite:**
- [ ] O nome é lido com `std::getline` e aparece completo (com o sobrenome)
- [ ] A média sai com exatamente duas casas decimais (`7.50`)
- [ ] A divisão usa `2.0` (ou `double`), não divisão inteira
- [ ] Comentário explicando `std::fixed` e `std::setprecision`

---

### 🟡 I2 – Refatorando para ficar legível

📄 **Arquivo base:** `base/i2_refatorar_legibilidade.cpp` · **Vale:** 1,5 ponto(s)

O programa do arquivo base calcula um desconto de 10%, mas ninguém entende o que ele faz. Sua missão é deixá-lo claro **sem mudar o cálculo**.

**O que fazer:**
1. Renomeie `v`, `d` e `t` para nomes que expliquem o significado (por exemplo, `valorCompra`, `desconto`, `totalPagar`).
2. Troque o `0.1` por uma **constante nomeada** (por exemplo, `constexpr double TAXA_DESCONTO{0.10};`).
3. Escreva uma instrução por linha e use indentação consistente.
4. Adicione um **cabeçalho em comentário** com: objetivo, entradas, saídas e instruções de compilação.
5. A saída passa a ter rótulos, com duas casas decimais.
6. Use comentários só onde explicam o **porquê** de algo, não onde repetem o código.

**Exemplo de execução** (o que o usuário digita aparece depois dos dois-pontos):
```text
Valor da compra: 200
Valor: R$ 200.00
Desconto: R$ 20.00
Total: R$ 180.00
```

> 💡 *Dica: um bom nome dispensa comentário. `valorCompra * TAXA_DESCONTO` já diz o que acontece.*

**✅ Critérios de aceite:**
- [ ] Nomes descritivos para todas as variáveis, sem abreviações de uma letra
- [ ] Taxa de desconto em uma constante nomeada
- [ ] Cabeçalho com objetivo, entradas, saídas e instruções de compilação
- [ ] O total para `200` é `180.00`
- [ ] Sem comentários que apenas repetem o código

---

### 🟡 I3 – Cadastro rápido: o bug do `getline`

📄 **Arquivo base:** `base/i3_cadastro_getline.cpp` · **Vale:** 1,5 ponto(s)

O programa do arquivo base lê a idade e depois o nome completo, mas o nome sai **vazio**. Descubra por quê e conserte.

**O que fazer:**
1. Compile e execute o arquivo base. Digite `19`, `Enter` e depois um nome. Observe o resultado.
2. Em um comentário, explique o que sobrou no buffer de entrada depois de `std::cin >> idade`.
3. Corrija **duas vezes** (uma versão de cada vez, deixando a outra comentada):
   - com `std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n')` (de `<limits>`);
   - com `std::getline(std::cin >> std::ws, nome)`.
4. Em um comentário, diga qual efeito colateral `std::ws` tem e quando a primeira opção é mais segura.
5. Verifique se a leitura da idade funcionou; se não, mostre `Entrada invalida.` em `std::cerr` e devolva `1`.

**Exemplo de execução** (o que o usuário digita aparece depois dos dois-pontos):
```text
Idade: 19
Nome completo: Ana Clara Lima
Aluno: Ana Clara Lima (19 anos)
```

> 💡 *Dica: o `Enter` que você digita depois do número continua no buffer. O `getline` encontra esse `\n` logo no início e devolve uma linha vazia.*

**✅ Critérios de aceite:**
- [ ] O nome completo (com espaços) aparece corretamente
- [ ] As duas correções estão no arquivo (uma ativa, outra comentada)
- [ ] Comentários explicando a causa do defeito e o efeito de `std::ws`
- [ ] Entrada inválida na idade encerra com código `1`

---

### 🟡 I4 – Calculadora de IMC com validação

📄 **Arquivo base:** `base/i4_calculadora_imc.cpp` · **Vale:** 1,5 ponto(s)

Uma academia quer calcular o Índice de Massa Corporal: `IMC = peso / (altura × altura)`, com o peso em kg e a altura em metros.

**O que fazer:**
1. Leia o peso e a altura (`double`).
2. Valide: a leitura precisa ter funcionado e **os dois valores precisam ser maiores que zero**. Caso contrário, escreva `Entrada invalida.` em `std::cerr` e devolva `1`.
3. Calcule o IMC e exiba-o com **duas casas decimais**.
4. Teste e anote, em um comentário, três execuções: uma normal, uma com altura `0` e uma com texto no lugar de número.

**Exemplo de execução** (o que o usuário digita aparece depois dos dois-pontos):
```text
Peso (kg): 70
Altura (m): 1.75
IMC: 22.86
```

> 💡 *Dica: o operador `||` combina condições. A leitura `!(std::cin >> peso >> altura)` e os testes `peso <= 0` podem ficar no mesmo `if`.*

**✅ Critérios de aceite:**
- [ ] IMC para `70` e `1.75` igual a `22.86`
- [ ] Rejeita zero, negativos e texto, com código de saída `1`
- [ ] Mensagens de erro em `std::cerr`
- [ ] Comentário com as três execuções de teste

---

### 🟡 I5 – Explorando tipos: tamanhos e limites

📄 **Arquivo base:** `base/i5_tamanhos_e_limites.cpp` · **Vale:** 1,5 ponto(s)

O tamanho dos tipos pode variar entre computadores, então um programador nunca deve presumir esses números. Vamos descobrir os valores da **sua** máquina.

**O que fazer:**
1. Para os tipos `short`, `int`, `long long` e `unsigned int`, exiba o tamanho em bytes (`sizeof`) e os valores mínimo e máximo (`std::numeric_limits<T>::min()` e `max()`, de `<limits>`).
2. Faça o mesmo para `double` e mostre o menor valor positivo (`min()`) e o maior (`max()`).
3. Mostre o valor de `unsigned int` máximo e o resultado de somar `1` a ele (o contador volta a `0`).
4. Em um comentário, explique por que o tamanho dos tipos não deve ser presumido e por que somar `1` ao maior `int` **com sinal** é um erro (comportamento indefinido), enquanto com `unsigned` é bem definido.

**Saída esperada** (os números dependem da plataforma; abaixo, um computador de 64 bits comum):
```text
short: 2 bytes, min=-32768, max=32767
int: 4 bytes, min=-2147483648, max=2147483647
long long: 8 bytes, min=-9223372036854775808, max=9223372036854775807
unsigned int: 4 bytes, min=0, max=4294967295
double: 8 bytes, min=2.22507e-308, max=1.79769e+308
unsigned int maximo + 1 = 0
```

> 💡 *Dica: para tipos de ponto flutuante, `std::numeric_limits<double>::min()` é o menor valor **positivo**, e não o mais negativo (esse seria `lowest()`).*

**✅ Critérios de aceite:**
- [ ] Mostra tamanho, mínimo e máximo dos tipos pedidos, com rótulos
- [ ] Usa `sizeof` e `std::numeric_limits`, e não números escritos à mão
- [ ] Demonstra a volta a `0` do `unsigned int`
- [ ] Comentário sobre portabilidade e sobre o estouro de `int` com sinal

---

## 🔴 Nível Difícil

### 🔴 D1 – Projeto da unidade: Calculadora de consumo

📄 **Arquivo base:** `base/d1_calculadora_consumo.cpp` · **Vale:** 2,0 ponto(s)

**Projeto integrador da Unidade 1.** Uma loja precisa de um resumo da compra de cada cliente.

**O que fazer:**
1. Leia o **nome do produto** (com espaços), o **preço unitário** (`double`), a **quantidade** (`int`) e a **taxa de desconto em %** (`double`).
2. Valide cada entrada: o preço e a quantidade devem ser maiores que zero e o desconto deve estar entre `0` e `100`. Em caso de erro, escreva uma mensagem específica em `std::cerr` e devolva `1`.
3. Calcule o subtotal, o valor do desconto e o total final.
4. Exiba o resumo alinhado, com duas casas decimais.
5. Use identificadores claros, constantes nomeadas quando houver números fixos e um cabeçalho de documentação (objetivo, entradas, saídas, compilação).
6. Registre, em comentário, ao menos três execuções de teste: normal, preço inválido e texto no lugar de número.

**Exemplo de execução** (o que o usuário digita aparece depois dos dois-pontos):
```text
Produto: Caderno Espiral
Preco unitario: 12.50
Quantidade: 4
Desconto (%): 10
===== RESUMO DA COMPRA =====
Produto   : Caderno Espiral
Preco unit: R$ 12.50
Quantidade: 4
Subtotal  : R$ 50.00
Desconto  : 10.00% (R$ 5.00)
Total     : R$ 45.00
```

> 💡 *Dica: se a leitura de `preco` falhar, o `std::cin` entra em estado de erro e as leituras seguintes também falham. Valide **cada** leitura logo depois de fazê-la.*

**✅ Critérios de aceite:**
- [ ] Resumo correto para o exemplo (`Subtotal 50.00`, `Total 45.00`)
- [ ] Valida preço, quantidade, desconto e falhas de leitura, com mensagens distintas e código `1`
- [ ] O nome do produto é lido por inteiro, com espaços
- [ ] Cabeçalho de documentação e três testes registrados
- [ ] Compila sem avisos

---

### 🔴 D2 – Nota fiscal alinhada

📄 **Arquivo base:** `base/d2_nota_fiscal.cpp` · **Vale:** 2,0 ponto(s)

Uma loja precisa imprimir uma nota fiscal de três itens com as colunas alinhadas. Os dados já estão declarados no arquivo base.

**O que fazer:**
1. Calcule o subtotal de cada item (`quantidade × preço`), o subtotal geral, o imposto de **12%** e o total.
2. Imprima a nota em formato de tabela: nomes alinhados à **esquerda**, números alinhados à **direita**, valores monetários com **duas casas decimais** e linhas separadoras.
3. Use `std::setw`, `std::left`, `std::right` e `std::fixed`/`std::setprecision` (e, se quiser, `std::string(n, '=')` para as linhas).
4. O alinhamento pode variar do exemplo, desde que as colunas fiquem alinhadas.

**Saída esperada (exemplo):**
```text
=============== NOTA FISCAL ===============
Item              Qtd     Preco    Subtotal
Caneta             10      2.50       25.00
Caderno             3     12.90       38.70
Mochila             1     89.90       89.90
-------------------------------------------
Subtotal                             153.60
Imposto (12%)                         18.43
Total                                172.03
```

> 💡 *Dica: `std::setw` vale apenas para a **próxima** impressão, mas `std::left`, `std::right` e `std::fixed` continuam valendo até serem trocados.*

**✅ Critérios de aceite:**
- [ ] Subtotal `153.60`, imposto `18.43` e total `172.03`
- [ ] Colunas alinhadas (texto à esquerda, números à direita)
- [ ] Todos os valores monetários com duas casas decimais
- [ ] Os cálculos usam as variáveis (nada de números prontos escritos à mão na impressão)

---

### 🔴 D3 – Conversão encadeada de unidades

📄 **Arquivo base:** `base/d3_conversao_unidades.cpp` · **Vale:** 2,0 ponto(s)

Uma loja de materiais vende fita métrica e precisa mostrar a mesma distância em várias unidades.

**O que fazer:**
1. Parta de uma distância de `1234.5` metros (já declarada no arquivo base).
2. Converta para quilômetros, centímetros, milímetros, polegadas e pés. Use **constantes nomeadas** para os fatores (`1 polegada = 0,0254 m`, `1 pé = 0,3048 m`).
3. Imprima uma tabela com os rótulos à esquerda e os valores à direita, com **quatro casas decimais**.
4. Em um comentário, explique por que as constantes são melhores que números soltos no cálculo.

**Saída esperada (exemplo):**
```text
Distancia: 1234.5000 m
Quilometros           1.2345
Centimetros      123450.0000
Milimetros      1234500.0000
Polegadas         48602.3622
Pes                4050.1969
```

> 💡 *Dica: dividir por `0.0254` e multiplicar por `39.3701` dão resultados ligeiramente diferentes. Use o fator exato definido no enunciado.*

**✅ Critérios de aceite:**
- [ ] Cinco conversões corretas (confira `48602.3622` polegadas e `4050.1969` pés)
- [ ] Fatores em constantes nomeadas (`constexpr`)
- [ ] Tabela alinhada, com quatro casas decimais
- [ ] Comentário sobre constantes nomeadas

---

### 🔴 D4 – Dinheiro sem surpresa

📄 **Arquivo base:** `base/d4_dinheiro_sem_surpresa.cpp` · **Vale:** 2,0 ponto(s)

A apostila avisa que `double` pode produzir pequenas imprecisões em operações financeiras. Primeiro você vai **ver** o problema; depois, resolvê-lo guardando o dinheiro em **centavos inteiros**.

**O que fazer:**
1. Mostre que `0.1 + 0.2 == 0.3` é **falso** com `double`, e imprima a soma com 17 dígitos (`std::setprecision(17)`).
2. Guarde três preços em `long long` **centavos**: `1990` (R$ 19,90), `510` (R$ 5,10) e `10` (R$ 0,10). Some-os.
3. Imprima o total no formato brasileiro, `R$ 25,10`: separe reais (`/ 100`) e centavos (`% 100`) e use `std::setfill('0')` e `std::setw(2)` nos centavos.
4. Aplique um desconto de **15%** com aritmética inteira, **arredondando para cima o meio centavo** (`(total * 15 + 50) / 100`), e imprima o desconto e o total com desconto.
5. Em um comentário, explique por que dinheiro não deve ser guardado em `double`.

**Saída esperada:**
```text
0.1 + 0.2 == 0.3 ? false (double)
0.1 + 0.2 = 0.30000000000000004
Soma em centavos: 2510
Total: R$ 25,10
Desconto 15%: R$ 3,77
Total com desconto: R$ 21,33
```

> 💡 *Dica: `setfill('0')` vale até ser trocado. Depois de imprimir os centavos, volte para `std::setfill(' ')`.*

**✅ Critérios de aceite:**
- [ ] Mostra `false` na comparação e `0.30000000000000004` na soma
- [ ] Total `R$ 25,10`, desconto `R$ 3,77` e total com desconto `R$ 21,33`
- [ ] Valores guardados em `long long` (centavos), sem `double` no cálculo do dinheiro
- [ ] Centavos sempre com dois dígitos (`R$ 5,05`, e não `R$ 5,5`)
- [ ] Comentário sobre o risco de usar `double` para dinheiro

---

### 🔴 D5 – Relógio: segundos para dias, horas, minutos e segundos

📄 **Arquivo base:** `base/d5_relogio_segundos.cpp` · **Vale:** 2,0 ponto(s)

Um sistema de logs guarda durações em segundos, mas as pessoas preferem ler em dias, horas, minutos e segundos. Você vai converter nos dois sentidos.

**O que fazer:**
1. Leia um total de segundos (`long long`, não negativo). Converta para **dias, horas, minutos e segundos** usando apenas `/` e `%`.
2. Exiba no formato `D dia(s) HH:MM:SS`, com `0` à esquerda quando necessário (`std::setfill('0')` e `std::setw(2)`).
3. Leia agora um horário em três números (`h m s`). Valide que `h >= 0`, `0 <= m < 60` e `0 <= s < 60`. Converta de volta para segundos.
4. Em qualquer entrada inválida, escreva `Entrada invalida.` em `std::cerr` e devolva `1`.

**Exemplo de execução** (o que o usuário digita aparece depois dos dois-pontos):
```text
Total de segundos: 93784
93784 segundos = 1 dia(s) 02:03:04
Horario (h m s): 2 3 4
02:03:04 = 7384 segundos
```

> 💡 *Dica: 1 dia = 86400 s, 1 hora = 3600 s. Divida pelo maior valor primeiro e continue com o resto. Use `3600LL` para forçar `long long` na multiplicação.*

**✅ Critérios de aceite:**
- [ ] `93784` vira `1 dia(s) 02:03:04` e `2 3 4` vira `7384 segundos`
- [ ] Usa apenas `/` e `%` na conversão (sem `if` para tratar horas ou minutos)
- [ ] Zeros à esquerda corretos (`05` e não `5`)
- [ ] Valida negativos, `m`/`s` fora de `0..59` e leitura inválida

---

## 📊 Tabela Resumo das Atividades

| Atividade | Tópico principal | Nível | Pontos | Arquivo base |
|-----------|------------------|-------|--------|--------------|
| F1 | Ambiente, compilação e `main` | 🟢 | 1,0 | `f1_primeiro_programa.cpp` |
| F2 | Declaração, inicialização e tipos fundamentais | 🟢 | 1,0 | `f2_variaveis_e_tipos.cpp` |
| F3 | Operadores `+ - * / %`, divisão inteira e real | 🟢 | 1,0 | `f3_operadores.cpp` |
| F4 | Expressões com `double` e armadilha da divisão inteira | 🟢 | 1,0 | `f4_conversor_temperatura.cpp` |
| F5 | Atribuição, variável auxiliar e `std::swap` | 🟢 | 1,0 | `f5_troca_de_variaveis.cpp` |
| I1 | `std::getline`, `std::cin` e `<iomanip>` | 🟡 | 1,5 | `i1_media_formatada.cpp` |
| I2 | Nomes significativos, constantes e documentação de código | 🟡 | 1,5 | `i2_refatorar_legibilidade.cpp` |
| I3 | Mistura de `>>` e `std::getline`; `cin.ignore` e `std::ws` | 🟡 | 1,5 | `i3_cadastro_getline.cpp` |
| I4 | Entrada validada, expressões e formatação | 🟡 | 1,5 | `i4_calculadora_imc.cpp` |
| I5 | `sizeof`, `<limits>` e estouro de `unsigned` | 🟡 | 1,5 | `i5_tamanhos_e_limites.cpp` |
| D1 | Integração: entrada validada, expressões, formatação e documentação | 🔴 | 2,0 | `d1_calculadora_consumo.cpp` |
| D2 | Formatação de tabelas com `<iomanip>` | 🔴 | 2,0 | `d2_nota_fiscal.cpp` |
| D3 | Constantes, conversões e tabela formatada | 🔴 | 2,0 | `d3_conversao_unidades.cpp` |
| D4 | Imprecisão de `double` e valores monetários em centavos | 🔴 | 2,0 | `d4_dinheiro_sem_surpresa.cpp` |
| D5 | Divisão inteira, resto e `std::setfill`/`std::setw` | 🔴 | 2,0 | `d5_relogio_segundos.cpp` |

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
