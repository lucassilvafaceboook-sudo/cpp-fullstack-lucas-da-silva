# 🛠️ Atividades – Unidade 4: Programação orientada a objetos
**Curso de Capacitação em Desenvolvimento Full Stack – ITEAM**
Módulo 08 – Linguagem de Programação C++
Professor: Msc. Hygo Sousa De Oliveira

> **Conteúdo da apostila:** Unidade 4, seções 4.1 a 4.7 (classes e objetos, construtores e destrutores, encapsulamento, herança, polimorfismo, sobrecarga de operadores, templates)
> **Tópicos:** classes e objetos · construtores e destrutores · `public`/`private`/`protected` · herança simples, múltipla e virtual · funções virtuais e polimorfismo · sobrecarga de operadores · templates de funções e de classes

---

## 📌 Como resolver e entregar

> Faça isto **antes de começar a resolver as atividades**.

Faça as atividades na **sua própria cópia** do repositório do curso. Se ainda não criou a sua, siga o passo a passo de [COMO-OBTER-AS-ATIVIDADES.md](../COMO-OBTER-AS-ATIVIDADES.md).

### 1. Copie a pasta `base/` para `resolucao/`

```bash
cp -r unidade-04/base unidade-04/resolucao
```

No PowerShell do Windows: `Copy-Item -Recurse unidade-04\base unidade-04\resolucao`.

> Não altere os arquivos dentro de `base/`: eles pertencem ao professor e podem ser substituídos quando você baixar atualizações.

### 2. Resolva e compile

Abra o arquivo da atividade dentro de `resolucao/`, complete os trechos marcados com `TODO` e compile **sempre com avisos ativados**:

```bash
cd unidade-04/resolucao
g++ -std=c++17 -Wall -Wextra f1_exemplo.cpp -o f1.exe
./f1.exe          # no Windows (CMD/PowerShell): .\f1.exe
```

Troque `f1_exemplo.cpp` e `f1.exe` pelo nome do arquivo da atividade. Atividades com arquivos de dados (`.txt`, `.csv`) devem ser executadas **de dentro da pasta `resolucao/`**.

### 3. Salve o seu progresso na sua cópia

```bash
git add unidade-04/resolucao
git commit -m "feat: unidade 4 - atividades F1 a F3"
git push origin main
```

Faça commits pequenos e frequentes: eles mostram o seu processo. **Não envie arquivos `.exe`** (o `.gitignore` já os ignora).

### 4. Entregue

Quando terminar, marque a entrega com a tag desta unidade e envie ao professor o link da sua cópia:

```bash
git tag atividade-unidade-04
git push origin atividade-unidade-04
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

### 🟢 F1 – Classe `Livro`: emprestar e devolver

📄 **Arquivo base:** `base/f1_classe_livro.cpp` · **Vale:** 1,0 ponto(s)

Uma biblioteca controla quantos exemplares de cada livro estão disponíveis. Você escreve a classe e o `main` (já pronto) a utiliza.

**O que fazer:**
1. Complete a classe `Livro`, que guarda o título, o total de exemplares e quantos estão **disponíveis** (no início, todos).
2. `bool emprestar()`: se houver exemplar disponível, retira um e devolve `true`; senão, devolve `false`.
3. `bool devolver()`: se houver exemplar emprestado, devolve um à estante e retorna `true`; senão (todos já estão na biblioteca), devolve `false`.
4. A quantidade disponível **nunca** pode ficar negativa nem maior que o total.

**Saída esperada:**
```text
Dom Casmurro: 2 disponivel(is)
Emprestimo 1: ok
Emprestimo 2: ok
Emprestimo 3: sem exemplares
Dom Casmurro: 0 disponivel(is)
Devolucao 1: ok
Devolucao 2: ok
Devolucao 3: todos ja estao na biblioteca
Dom Casmurro: 2 disponivel(is)
```

> 💡 *Dica: em um método da classe você acessa os atributos pelo nome (`disponiveis_`). Fora da classe, o acesso é pelo operador ponto (`livro.emprestar()`). Os atributos são privados, e é por isso que existem os métodos.*

**✅ Critérios de aceite:**
- [ ] A saída é exatamente a esperada
- [ ] Atributos privados; `emprestar` e `devolver` validam os limites antes de alterar
- [ ] Métodos de consulta (`disponiveis`, `titulo`) marcados como `const`

---

### 🟢 F2 – Ordem de construtores e destrutores

📄 **Arquivo base:** `base/f2_construtores_destrutores.cpp` · **Vale:** 1,0 ponto(s)

Construtores e destrutores são chamados **automaticamente**. Esta atividade faz você enxergar quando.

**O que fazer:**
1. Complete a classe `Rastro`: o construtor recebe um nome e mostra `Criando <nome>`; o destrutor mostra `Destruindo <nome>`.
2. **Antes de executar**, escreva em um comentário a ordem que você prevê para as mensagens do `main` (já pronto).
3. Execute, compare com a sua previsão e anote o que surpreendeu.

**Saída esperada:**
```text
Criando A
Criando B
Criando C
Dentro do bloco interno
Destruindo C
Dentro do bloco externo
Destruindo B
Criando D
Antes do delete
Destruindo D
Criando E
Criando F
Fim de main
Destruindo F
Destruindo E
Destruindo A
```

> 💡 *Dica: um objeto local é destruído quando o bloco em que foi declarado termina, na **ordem inversa** da criação. Um objeto criado com `new` só é destruído quando você chama `delete`.*

**✅ Critérios de aceite:**
- [ ] A saída é exatamente a esperada
- [ ] Construtor e destrutor mostram as mensagens no formato pedido
- [ ] Comentário com a previsão feita **antes** de executar e com a conclusão sobre a ordem de destruição

---

### 🟢 F3 – Conta bancária com encapsulamento

📄 **Arquivo base:** `base/f3_conta_encapsulada.cpp` · **Vale:** 1,0 ponto(s)

O saldo de uma conta não pode ser alterado por qualquer código. Só depósitos e saques válidos mudam o saldo.

**O que fazer:**
1. Escreva a classe `Conta` com o atributo **privado** `saldo_`.
2. O construtor `explicit Conta(double saldoInicial)` lança `std::invalid_argument("Saldo inicial negativo")` se o valor for negativo.
3. `bool depositar(double valor)`: só aceita `valor > 0`.
4. `bool sacar(double valor)`: só aceita `valor > 0` e `valor <= saldo`.
5. `double saldo() const` devolve o saldo.
6. No `main`, leia o saldo inicial, o valor a depositar e o valor a sacar (verificando as leituras), mostre `Deposito realizado` ou `Deposito recusado`, `Saque realizado` ou `Saque recusado` e, no fim, `Saldo final: ` com duas casas decimais. Se o saldo inicial for negativo, capture a exceção, mostre `Erro: ...` em `std::cerr` e devolva `1`.

**Exemplo de execução** (o que o usuário digita aparece depois dos dois-pontos):
```text
Saldo inicial: 100
Deposito: 50
Deposito realizado
Saque: 500
Saque recusado
Saldo final: 150.00
```

> 💡 *Dica: tentar escrever `conta.saldo_ = 1000000;` em `main` gera erro de compilação, porque o atributo é privado. É exatamente essa proteção que garante a regra do saque.*

**✅ Critérios de aceite:**
- [ ] O exemplo produz a saída mostrada; `100`, `-20`, `30` dá depósito recusado e saque realizado (saldo `70.00`)
- [ ] `saldo_` é privado e só é alterado por `depositar` e `sacar`
- [ ] Saldo inicial negativo lança e captura a exceção
- [ ] As leituras são verificadas

---

### 🟢 F4 – Classe `Retangulo` com métodos `const`

📄 **Arquivo base:** `base/f4_retangulo.cpp` · **Vale:** 1,0 ponto(s)

Um retângulo com lado zero ou negativo não existe. O construtor deve impedir que esse objeto seja criado.

**O que fazer:**
1. Escreva a classe `Retangulo` com os atributos privados `largura_` e `altura_` (`double`).
2. O construtor `Retangulo(double largura, double altura)` lança `std::invalid_argument("Dimensoes devem ser positivas")` se qualquer lado for `<= 0`.
3. Métodos `const`: `double area() const`, `double perimetro() const` e `bool ehQuadrado() const`.
4. Em `main`, leia largura e altura (verificando a leitura), crie o objeto dentro de `try` e mostre `Area`, `Perimetro` e `Quadrado` com duas casas decimais. Se o construtor lançar, mostre `Erro: ...` em `std::cerr` e devolva `1`.

**Exemplo de execução** (o que o usuário digita aparece depois dos dois-pontos):
```text
Largura e altura: 5 3
Area: 15.00
Perimetro: 16.00
Quadrado: nao
```
```text
Largura e altura: 4 4
Area: 16.00
Perimetro: 16.00
Quadrado: sim
```

> 💡 *Dica: `const` depois da lista de parâmetros diz que o método **não altera** o objeto. Sem ele, não é possível chamar o método a partir de um objeto `const`.*

**✅ Critérios de aceite:**
- [ ] Os dois exemplos produzem a saída mostrada
- [ ] Os três métodos de consulta são `const` e os atributos são privados
- [ ] `0 3`, `-2 5` e texto são rejeitados, e o programa devolve `1`

---

### 🟢 F5 – Sobrecarga de operadores: `Vetor2D`

📄 **Arquivo base:** `base/f5_vetor2d_operadores.cpp` · **Vale:** 1,0 ponto(s)

Podemos fazer `a + b` funcionar para tipos nossos, como vetores no plano, definindo `operator+`.

**O que fazer:**
1. Escreva a classe `Vetor2D` com `x_` e `y_` privados e o construtor `Vetor2D(double x = 0.0, double y = 0.0)`.
2. Métodos `double x() const` e `double y() const`.
3. Sobrecarregue, como **métodos `const`**, `operator+`, `operator-` (ambos devolvem um **novo** `Vetor2D`, sem alterar os operandos) e `operator==` (devolve `bool`).
4. No `main`, leia `x1 y1 x2 y2` (verificando a leitura) e mostre os três resultados.

**Exemplo de execução** (o que o usuário digita aparece depois dos dois-pontos):
```text
Dois vetores (x1 y1 x2 y2): 2 3 4 5
Soma: (6, 8)
Diferenca: (-2, -2)
Iguais: nao
```

> 💡 *Dica: `a + b` é lido pelo compilador como `a.operator+(b)`. Por isso o operador recebe só **um** parâmetro (o operando da direita), e o da esquerda é o próprio objeto (`*this`).*

**✅ Critérios de aceite:**
- [ ] O exemplo produz a saída mostrada; `1 2 1 2` dá `Iguais: sim`
- [ ] Os operadores são métodos `const` que devolvem novos objetos
- [ ] `Vetor2D` tem atributos privados e usa o construtor com valores padrão
- [ ] A leitura é verificada

---

## 🟡 Nível Intermediário

### 🟡 I1 – Herança simples: `Pessoa`, `Estudante` e `Trabalhador`

📄 **Arquivo base:** `base/i1_heranca_pessoas.cpp` · **Vale:** 1,5 ponto(s)

`Estudante` e `Trabalhador` **são** pessoas, e por isso herdam o que é comum (nome e idade) e acrescentam o que é próprio.

**O que fazer:**
1. `Pessoa`: atributos **`protected`** `nome_` e `idade_`; construtor `(nome, idade)` que mostra `Pessoa criada: <nome>`; destrutor que mostra `Pessoa destruida: <nome>`; método `void apresentar() const` que mostra `Nome: ...` e `Idade: ...` em linhas separadas.
2. `Estudante : public Pessoa`: acrescenta `curso_`. O construtor **chama o construtor da base** na lista de inicialização e mostra `Estudante criado: <nome>`; o destrutor mostra `Estudante destruido: <nome>`. `apresentar()` chama `Pessoa::apresentar()` e depois mostra `Curso: ...`.
3. `Trabalhador : public Pessoa`: acrescenta `salario_` (`double`). Mesmo padrão de mensagens (`Trabalhador criado:` / `Trabalhador destruido:`). `apresentar()` mostra `Salario: R$ ` com duas casas decimais.
4. O `main` já está pronto. Compare a ordem das mensagens com a explicação do comentário que você vai escrever.

**Saída esperada:**
```text
Pessoa criada: Ana
Estudante criado: Ana
Pessoa criada: Bruno
Trabalhador criado: Bruno
Nome: Ana
Idade: 20
Curso: ADS
Nome: Bruno
Idade: 35
Salario: R$ 4200.00
Trabalhador destruido: Bruno
Pessoa destruida: Bruno
Estudante destruido: Ana
Pessoa destruida: Ana
```

> 💡 *Dica: na construção, a base é criada **primeiro**; na destruição, a ordem se inverte e a classe derivada é destruída **antes** da base. Membros `protected` são visíveis nas classes derivadas, mas não fora delas.*

**✅ Critérios de aceite:**
- [ ] A saída é exatamente a esperada
- [ ] As derivadas chamam o construtor da base na lista de inicialização
- [ ] `nome_` e `idade_` são `protected`, e não `public`
- [ ] `apresentar()` das derivadas reaproveita `Pessoa::apresentar()`
- [ ] Comentário explicando a ordem de construção e destruição

---

### 🟡 I2 – Polimorfismo com `Forma` abstrata

📄 **Arquivo base:** `base/i2_formas_polimorficas.cpp` · **Vale:** 1,5 ponto(s)

Uma função que recebe uma `const Forma&` pode trabalhar com **qualquer** forma, sem saber qual é, e o C++ escolhe em tempo de execução o `area()` correto. É o polimorfismo dinâmico.

**O que fazer:**
1. Escreva a classe abstrata `Forma` com destrutor `virtual` e os métodos virtuais **puros** `double area() const` e `std::string nome() const`.
2. Escreva três derivadas, **cada método com `override`**: `Retangulo(largura, altura)`, `Circulo(raio)` e `Triangulo(base, altura)`. Use `constexpr double PI{3.14159265358979323846};`.
3. O `main` (pronto) usa `mostrar(const Forma&)` e um array de ponteiros para a base.
4. Em um comentário, explique por que não é possível criar `Forma f;` e por que o destrutor da base é `virtual`.

**Saída esperada:**
```text
Retangulo: area = 20.00
Circulo: area = 28.27
Triangulo: area = 12.00
Soma das areas: 60.27
```

> 💡 *Dica: `= 0` ao fim da declaração torna o método virtual **puro**, e a classe passa a ser abstrata, ou seja, não pode ser instanciada. Cada derivada **precisa** implementar todos os métodos puros, senão também fica abstrata.*

**✅ Critérios de aceite:**
- [ ] A saída é exatamente a esperada
- [ ] `Forma` é abstrata (métodos virtuais puros) e tem destrutor virtual
- [ ] As três derivadas usam `override`
- [ ] Comentário explicando a classe abstrata e o destrutor virtual

---

### 🟡 I3 – Templates de função: `menor`, `somaArray` e `trocar`

📄 **Arquivo base:** `base/i3_template_funcoes.cpp` · **Vale:** 1,5 ponto(s)

Em vez de escrever `menor` uma vez para `int`, outra para `double` e outra para `std::string`, escrevemos **um template** e o compilador gera as versões necessárias.

**O que fazer:**
1. `template <typename T> T menor(T a, T b)`: devolve o menor dos dois.
2. `template <typename T> T somaArray(const T* dados, int n)`: soma `n` elementos (comece o acumulador com `T soma{};`).
3. `template <typename T> void trocar(T& a, T& b)`: troca os valores.
4. O `main` (pronto) chama os três com `int`, `double` e `std::string`.
5. Em um comentário, responda: por que `menor(3, 2.5)` **não compila**, e como corrigir?

**Saída esperada:**
```text
menor(3, 8) = 3
menor(2.5, 1.5) = 1.5
menor("banana", "abacaxi") = abacaxi
soma dos inteiros = 10
soma dos reais = 4
antes: x=ola, y=mundo
depois: x=mundo, y=ola
```

> 💡 *Dica: o compilador deduz `T` pelos argumentos. Em `menor(3, 2.5)` ele encontra `int` e `double` e não sabe qual escolher. Escrevendo `menor<double>(3, 2.5)`, você informa `T` explicitamente.*

**✅ Critérios de aceite:**
- [ ] A saída é exatamente a esperada
- [ ] Os três templates estão corretos e não são repetidos para cada tipo
- [ ] Comentário explicando por que `menor(3, 2.5)` não compila e como corrigir

---

### 🟡 I4 – Classe template `Par<A, B>`

📄 **Arquivo base:** `base/i4_par_template.cpp` · **Vale:** 1,5 ponto(s)

Um `Par` guarda dois valores, que podem ter **tipos diferentes**: um número e um texto, um `double` e um `bool`...

**O que fazer:**
1. Escreva `template <typename A, typename B> class Par` com os atributos privados `primeiro_` (do tipo `A`) e `segundo_` (do tipo `B`).
2. Construtor `Par(const A& primeiro, const B& segundo)`; métodos `const A& primeiro() const` e `const B& segundo() const`.
3. Método `Par<B, A> inverter() const`, que devolve um novo par com os valores **trocados de posição** (e de tipo).
4. Template de função `template <typename A, typename B> void mostrar(const Par<A, B>& par)`, que mostra `Par(<primeiro>, <segundo>)`.
5. O `main` (pronto) testa `Par<int, std::string>` e `Par<double, bool>`.

**Saída esperada:**
```text
Par(7, sete)
Par(sete, 7)
Par(2.5, true)
```

> 💡 *Dica: dentro de `Par<A, B>`, o tipo de retorno `Par<B, A>` é **outra** instanciação do mesmo template, e isso é permitido. Para mostrar `true`/`false` em vez de `1`/`0`, o `main` usa `std::boolalpha`.*

**✅ Critérios de aceite:**
- [ ] A saída é exatamente a esperada
- [ ] `Par` é um único template para qualquer combinação de tipos; atributos privados
- [ ] `inverter()` devolve `Par<B, A>` sem alterar o objeto (`const`)
- [ ] Os acessos são `const` e devolvem referência `const` (sem cópias desnecessárias)

---

### 🟡 I5 – `Buffer`: uma classe que cuida da própria memória

📄 **Arquivo base:** `base/i5_buffer_raii.cpp` · **Vale:** 1,5 ponto(s)

Esquecer o `delete[]` é fácil. **RAII** resolve isso: o construtor adquire o recurso e o **destrutor** o libera, automaticamente, mesmo quando uma exceção interrompe o código.

**O que fazer:**
1. Complete a classe `Buffer`, que guarda um array de `int` alocado com `new`:
   - construtor `explicit Buffer(int tamanho)`: se `tamanho <= 0`, lança `std::invalid_argument("Tamanho deve ser positivo")` **antes** de alocar; caso contrário aloca `new int[tamanho]{}` e mostra `Buffer criado (N elementos)`;
   - destrutor: libera com `delete[]` e mostra `Buffer destruido`;
   - `int& operator[](int indice)`: devolve o elemento; se o índice estiver fora de `0..tamanho-1`, lança `std::out_of_range("Indice fora dos limites")`;
   - `int tamanho() const`;
   - **proíba a cópia**: `Buffer(const Buffer&) = delete;` e `Buffer& operator=(const Buffer&) = delete;` (copiar um ponteiro bruto causaria `delete[]` duplo).
2. O `main` (pronto) cria o buffer, preenche com quadrados e acessa um índice inválido de propósito.
3. Em um comentário, explique por que `Buffer destruido` aparece **antes** de `Erro:`.

**Exemplo de execução** (o que o usuário digita aparece depois dos dois-pontos):
```text
Tamanho: 4
Buffer criado (4 elementos)
Conteudo: 0 1 4 9
Acessando indice 4...
Buffer destruido
Erro: Indice fora dos limites
Fim
```
```text
Tamanho: 0
Erro: Tamanho deve ser positivo
Fim
```

> 💡 *Dica: quando uma exceção sai do bloco `try`, os objetos locais dele são destruídos (é o "desempilhamento da pilha") **antes** de o `catch` executar. Se o construtor lança, o objeto nunca chegou a existir e o destrutor **não** é chamado.*

**✅ Critérios de aceite:**
- [ ] Os dois exemplos produzem a saída mostrada
- [ ] Todo `new[]` do construtor tem o `delete[]` correspondente no destrutor
- [ ] `operator[]` valida o índice; a cópia está proibida (`= delete`)
- [ ] Comentário explicando a ordem das mensagens

---

## 🔴 Nível Difícil

### 🔴 D1 – Projeto da unidade: Cadastro orientado a objetos

📄 **Arquivo base:** `base/d1_cadastro_de_produtos.cpp` · **Vale:** 2,0 ponto(s)

**Projeto integrador da Unidade 4.** Um cadastro de produtos com classes bem encapsuladas. O `main` (pronto) exercita **todas** as peças. A sua tarefa é construir as classes para que a saída seja exatamente a esperada.

**Classes a construir** (o arquivo base traz os esqueletos):

- **`Par<A, B>`** (template): guarda dois valores; `primeiro()` e `segundo()` devolvem `const` por referência.
- **`Produto`**: atributos **privados** `nome_`, `preco_`, `quantidade_`.
  - Construtor `(nome, preco, quantidade)` valida e lança `std::invalid_argument` com `Nome vazio`, `Preco negativo` ou `Quantidade negativa`.
  - Destrutor `virtual`. Consultas `const`: `nome()`, `preco()`, `quantidade()`.
  - `atualizarPreco(double)` (valida, `Preco negativo`) e `adicionarEstoque(int)` (valida `> 0`, senão `Quantidade a adicionar deve ser positiva`).
  - `virtual std::string descricao() const` devolve `Nome - R$ 2.50 - 100 un.` (preço com duas casas decimais).
  - `Produto operator+(const Produto& outro) const`: combina **dois produtos de mesmo nome**, somando as quantidades e mantendo o preço do primeiro. Nomes diferentes lançam `Produtos diferentes nao podem ser combinados`.
- **`ProdutoPerecivel : public Produto`**: acrescenta `diasParaVencer_` (se `< 0`, lança `Prazo de validade invalido`). Sobrescreve `descricao()` com `override`, acrescentando ` - vence em N dia(s)`.

**Saída esperada:**
```text
== Catalogo ==
Caneta - R$ 2.50 - 100 un.
Leite - R$ 5.99 - 20 un. - vence em 7 dia(s)
== Apos atualizacoes ==
Caneta - R$ 3.00 - 100 un.
Leite - R$ 5.99 - 30 un. - vence em 7 dia(s)
== Combinacao ==
Caneta - R$ 3.00 - 150 un.
== Entradas invalidas ==
Erro: Nome vazio
Erro: Preco negativo
Erro: Prazo de validade invalido
Erro: Produtos diferentes nao podem ser combinados
Erro: Quantidade a adicionar deve ser positiva
== Resumo ==
Valor total em estoque: R$ 479.70
```

**Documentação:** no topo do arquivo, escreva em comentário **as suas escolhas de projeto** (por que `nome_` etc. são privados, por que o destrutor é virtual, por que `operator+` exige o mesmo nome) e **três testes de entrada inválida** além dos do `main`.

> 💡 *Dica: para formatar o preço dentro de uma `std::string`, use `std::ostringstream` (`#include <sstream>`) com `std::fixed` e `std::setprecision(2)`. `ProdutoPerecivel::descricao()` pode chamar `Produto::descricao()` e complementar o texto.*

**✅ Critérios de aceite:**
- [ ] A saída é exatamente a esperada
- [ ] Modelagem e encapsulamento: atributos privados, validação nos construtores e setters (25%)
- [ ] Herança e polimorfismo: `virtual`/`override` e destrutor virtual (25%)
- [ ] Construtores e operadores: `operator+` correto, com as exceções (20%)
- [ ] Template `Par` genérico e usado no resumo (15%)
- [ ] Documentação das escolhas e testes de entradas inválidas (15%)

---

### 🔴 D2 – Herança múltipla e o problema do diamante

📄 **Arquivo base:** `base/d2_heranca_virtual_diamante.cpp` · **Vale:** 2,0 ponto(s)

Um `EstudanteTrabalhador` **é um** estudante e **é um** trabalhador, e os dois **são** pessoas. Sem cuidado, o objeto teria **duas** cópias de `Pessoa` (o "diamante"). A herança **virtual** garante uma só.

**O que fazer:**
1. `Pessoa`: atributo privado `nome_`; construtor `explicit Pessoa(const std::string& nome)` que mostra `Pessoa construida: <nome>`; destrutor que mostra `Pessoa destruida: <nome>`; método `nome() const`.
2. `Estudante : virtual public Pessoa` com `curso_`. O construtor `(nome, curso)` inicializa `Pessoa(nome)` e mostra `Estudante construido: <curso>`; o destrutor mostra `Estudante destruido: <curso>`. Método `curso() const`.
3. `Trabalhador : virtual public Pessoa` com `empresa_`. Mesmo padrão (`Trabalhador construido: <empresa>` / `Trabalhador destruido: <empresa>`) e `empresa() const`.
4. `EstudanteTrabalhador : public Estudante, public Trabalhador`. O construtor `(nome, curso, empresa)` inicializa **`Pessoa(nome)`, `Estudante(nome, curso)` e `Trabalhador(nome, empresa)`**; mostra `EstudanteTrabalhador construido`. O destrutor mostra `EstudanteTrabalhador destruido`. O método `apresentar() const` mostra `Nome:`, `Curso:` e `Empresa:` em linhas separadas.
5. Em um comentário, explique **(a)** por que `Pessoa construida` aparece **uma única vez** na criação de `EstudanteTrabalhador`, e **(b)** o que aconteceria sem `virtual` (quantas cópias de `Pessoa` e o que o compilador diria ao chamar `nome()`).

**Saída esperada** (o `main` já está pronto):
```text
-- Objeto Estudante --
Pessoa construida: Davi
Estudante construido: Redes
Estudante destruido: Redes
Pessoa destruida: Davi
-- Objeto EstudanteTrabalhador --
Pessoa construida: Carla
Estudante construido: ADS
Trabalhador construido: ITEAM
EstudanteTrabalhador construido
Nome: Carla
Curso: ADS
Empresa: ITEAM
-- Fim de main --
EstudanteTrabalhador destruido
Trabalhador destruido: ITEAM
Estudante destruido: ADS
Pessoa destruida: Carla
```

> 💡 *Dica: com herança virtual, quem inicializa a base virtual é a classe **mais derivada** (aqui, `EstudanteTrabalhador`). As chamadas `Pessoa(nome)` dentro de `Estudante` e `Trabalhador` são ignoradas nesse caso. Mas continuam valendo quando o objeto criado é só um `Estudante`, como na primeira parte do `main`.*

**✅ Critérios de aceite:**
- [ ] A saída é exatamente a esperada
- [ ] `Estudante` e `Trabalhador` herdam **virtualmente** de `Pessoa`
- [ ] `EstudanteTrabalhador` inicializa a base virtual `Pessoa` diretamente
- [ ] `nome()` pode ser chamado sem ambiguidade em `EstudanteTrabalhador`
- [ ] Comentário com as respostas (a) e (b)

---

### 🔴 D3 – Folha de pagamento polimórfica

📄 **Arquivo base:** `base/d3_folha_polimorfica.cpp` · **Vale:** 2,0 ponto(s)

Uma empresa tem três tipos de funcionário, e cada um calcula o salário de um jeito. A folha trabalha com **ponteiros para a base** e não precisa saber o tipo concreto de cada um.

**O que fazer:**
1. `Funcionario` (abstrata): atributo privado `nome_`; construtor `explicit Funcionario(const std::string&)`; **destrutor virtual** que mostra `Destruindo Funcionario: <nome>`; métodos virtuais puros `double salario() const` e `std::string cargo() const`; `nome() const`.
2. `Assalariado(nome, salarioMensal)`: salário = o valor mensal. Cargo `Assalariado`.
3. `Horista(nome, valorHora, horas)`: até `160` horas, `valorHora * horas`; as horas **acima de 160** valem `1,5` vezes o valor da hora. Cargo `Horista`.
4. `Comissionado(nome, fixo, vendas, percentual)`: `fixo + vendas * percentual / 100`. Cargo `Comissionado`.
5. Cada derivada usa `override` e tem destrutor que mostra `Destruindo <Cargo>: <nome>`.
6. O `main` (pronto) cria os três com `new`, lista, soma, descobre o maior salário e destrói tudo com `delete` por ponteiro da base.
7. Em um comentário, explique por que, sem o destrutor `virtual` na base, o `delete` por ponteiro da base seria um problema.

**Saída esperada:**
```text
Ana (Assalariado): R$ 3500.00
Bruno (Horista): R$ 4375.00
Carla (Comissionado): R$ 3100.00
Total da folha: R$ 10975.00
Maior salario: Bruno
Destruindo Assalariado: Ana
Destruindo Funcionario: Ana
Destruindo Horista: Bruno
Destruindo Funcionario: Bruno
Destruindo Comissionado: Carla
Destruindo Funcionario: Carla
```

> 💡 *Dica: Bruno trabalhou 170 h a R$ 25: `160 * 25 = 4000` mais `10 * 25 * 1,5 = 375`, total `4375`. Observe que, para cada objeto, o destrutor da derivada roda **antes** do da base, e que as duas mensagens só aparecem porque o destrutor da base é virtual.*

**✅ Critérios de aceite:**
- [ ] A saída é exatamente a esperada
- [ ] `Funcionario` é abstrata, com destrutor virtual e métodos puros; as derivadas usam `override`
- [ ] A regra das horas extras e a comissão estão corretas
- [ ] Comentário sobre o destrutor virtual (comportamento indefinido sem ele)

---

### 🔴 D4 – Classe `Fracao` com operadores sobrecarregados

📄 **Arquivo base:** `base/d4_fracao_operadores.cpp` · **Vale:** 2,0 ponto(s)

Frações são o exemplo clássico de tipo que **merece** operadores: `a + b` deve funcionar como na matemática. A classe também precisa se manter coerente (sempre simplificada, com denominador positivo).

**O que fazer:**
1. Escreva a classe `Fracao` com atributos privados `numerador_` e `denominador_` (`int`) e o construtor `Fracao(int numerador = 0, int denominador = 1)`.
2. O construtor lança `std::invalid_argument("Denominador zero")` se o denominador for `0`. Depois **normaliza**: se o denominador for negativo, troca os sinais dos dois; e divide ambos pelo **MDC** (máximo divisor comum), para que `2/4` vire `1/2` e `0/5` vire `0/1`.
3. Métodos `numerador() const`, `denominador() const` e `double valor() const`.
4. Operadores **membros `const`** `+`, `-`, `*` e `/` (que devolvem novas frações). A divisão por fração de numerador zero lança `std::invalid_argument("Divisao por fracao nula")`.
5. Operadores `==` (compara as frações **já simplificadas**) e `<` (compare por multiplicação cruzada, usando `long long` para evitar estouro).
6. Operador de saída, como **função livre**: `std::ostream& operator<<(std::ostream& saida, const Fracao& f)`, que escreve `n/d`.
7. O `main` (pronto) lê duas frações e mostra todas as operações. Se um construtor ou operador lançar, mostra `Erro: ...` em `std::cerr` e devolve `1`.

**Exemplo de execução** (o que o usuário digita aparece depois dos dois-pontos):
```text
Fracao 1 (numerador denominador): 1 2
Fracao 2 (numerador denominador): 1 3
1/2 + 1/3 = 5/6
1/2 - 1/3 = 1/6
1/2 * 1/3 = 1/6
1/2 / 1/3 = 3/2
1/2 == 1/3: nao
1/2 < 1/3: nao
Valor decimal de 1/2: 0.5
```
Com `2 4` e `1 -2`, as frações viram `1/2` e `-1/2`. Com `1 0`, a saída é `Erro: Denominador zero`.

> 💡 *Dica: o MDC se calcula com o algoritmo de Euclides: `while (b != 0) { r = a % b; a = b; b = r; }` e o resultado fica em `a` (use o valor absoluto do numerador). Como `operator<<` recebe o `std::ostream` à esquerda, ele **não** pode ser método da classe, e por isso é função livre usando os métodos `numerador()` e `denominador()`.*

**✅ Critérios de aceite:**
- [ ] O exemplo produz a saída mostrada; `2 4` e `1 2` dão `1/2 == 1/2: sim`
- [ ] Toda fração é normalizada (`2/4` → `1/2`, denominador sempre positivo, `0/x` → `0/1`)
- [ ] Os operadores são `const` e devolvem novos objetos; `<<` é função livre
- [ ] Denominador zero e divisão por fração nula lançam as exceções corretas

---

### 🔴 D5 – Pilha genérica e verificador de parênteses

📄 **Arquivo base:** `base/d5_pilha_template.cpp` · **Vale:** 2,0 ponto(s)

Uma **pilha** é uma estrutura LIFO: o último que entra é o primeiro que sai. Escrita como *template*, ela serve para `int`, `std::string`, `char`... Vamos usá-la para verificar se uma expressão tem parênteses balanceados.

**O que fazer:**
1. Escreva `template <typename T> class Pilha` com o array dinâmico `T* dados_`, `capacidade_` e `tamanho_` (privados).
   - Construtor `explicit Pilha(int capacidade)`: lança `std::invalid_argument("Capacidade deve ser positiva")` se `capacidade <= 0`; aloca com `new T[capacidade]`.
   - Destrutor com `delete[]`; **proíba a cópia** (`= delete` no construtor de cópia e na atribuição).
   - `void empilhar(const T& valor)`: se a pilha estiver cheia, lança `std::overflow_error("Pilha cheia")`.
   - `T desempilhar()`: se estiver vazia, lança `std::underflow_error("Pilha vazia")`.
   - `const T& topo() const` (também lança `Pilha vazia` se vazia), `bool vazia() const` e `int tamanho() const`.
2. Escreva `bool balanceada(const std::string& expressao)`, que usa uma `Pilha<char>`: empilha `(`, `[` e `{`; ao ler `)`, `]` ou `}`, desempilha e confere se o par **combina**. Pilha vazia ao fechar, par errado ou sobra no fim indicam expressão **desbalanceada**. Os outros caracteres são ignorados. A capacidade da pilha pode ser `expressao.size() + 1`.
3. O `main` (pronto) testa `Pilha<int>`, `Pilha<std::string>` e lê uma linha para o verificador.

**Exemplo de execução** (o que o usuário digita aparece depois dos dois-pontos):
```text
-- Pilha<int> --
Empilhando 10 20 30
Erro: Pilha cheia
Desempilhando: 30 20 10
Erro: Pilha vazia
-- Pilha<std::string> --
Topo: mundo
-- Balanceamento --
Expressao: (a[b]{c})
Balanceada
```
Para `(a[b)]` ou `((`, a última linha é `Desbalanceada`. Uma linha vazia é `Balanceada`.

> 💡 *Dica: `new T[n]` exige que `T` tenha construtor padrão (`int`, `char` e `std::string` têm). Numa pilha cheia, `tamanho_ == capacidade_`. Ao empilhar, grave em `dados_[tamanho_]` e **depois** incremente `tamanho_`; ao desempilhar, decremente antes de ler.*

**✅ Critérios de aceite:**
- [ ] O exemplo produz a saída mostrada; `(a[b)]` e `((` são desbalanceadas; `{[()]}` é balanceada
- [ ] `Pilha` é um único template com memória dinâmica liberada no destrutor e cópia proibida
- [ ] Estouro e esvaziamento lançam as exceções corretas (`overflow_error`/`underflow_error`)
- [ ] `balanceada` usa `Pilha<char>` e trata os três tipos de delimitador

---

## 📊 Tabela Resumo das Atividades

| Atividade | Tópico principal | Nível | Pontos | Arquivo base |
|-----------|------------------|-------|--------|--------------|
| F1 | Classes, atributos, métodos e operador ponto | 🟢 | 1,0 | `f1_classe_livro.cpp` |
| F2 | Construtores, destrutores e tempo de vida dos objetos | 🟢 | 1,0 | `f2_construtores_destrutores.cpp` |
| F3 | Encapsulamento: atributo privado e métodos com validação | 🟢 | 1,0 | `f3_conta_encapsulada.cpp` |
| F4 | Construtor com validação, métodos `const` e exceções | 🟢 | 1,0 | `f4_retangulo.cpp` |
| F5 | Sobrecarga de `+`, `-` e `==` | 🟢 | 1,0 | `f5_vetor2d_operadores.cpp` |
| I1 | Herança, `protected` e ordem de construção e destruição | 🟡 | 1,5 | `i1_heranca_pessoas.cpp` |
| I2 | Classe abstrata, funções virtuais puras, `override` e referência à base | 🟡 | 1,5 | `i2_formas_polimorficas.cpp` |
| I3 | Funções genéricas e dedução do tipo `T` | 🟡 | 1,5 | `i3_template_funcoes.cpp` |
| I4 | Templates de classe com dois parâmetros de tipo | 🟡 | 1,5 | `i4_par_template.cpp` |
| I5 | RAII, `operator[]`, exceções e cópia proibida | 🟡 | 1,5 | `i5_buffer_raii.cpp` |
| D1 | Integração: encapsulamento, herança, polimorfismo, operador e template | 🔴 | 2,0 | `d1_cadastro_de_produtos.cpp` |
| D2 | Herança múltipla e herança virtual | 🔴 | 2,0 | `d2_heranca_virtual_diamante.cpp` |
| D3 | Polimorfismo com ponteiros para a base, `override` e destrutor virtual | 🔴 | 2,0 | `d3_folha_polimorfica.cpp` |
| D4 | Sobrecarga de `+ - * / == <` e `<<`, normalização e exceções | 🔴 | 2,0 | `d4_fracao_operadores.cpp` |
| D5 | Template de classe com memória dinâmica, exceções e RAII | 🔴 | 2,0 | `d5_pilha_template.cpp` |

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
