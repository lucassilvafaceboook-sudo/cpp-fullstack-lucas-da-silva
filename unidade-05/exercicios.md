# 🛠️ Atividades – Unidade 5: Bibliotecas e recursos avançados
**Curso de Capacitação em Desenvolvimento Full Stack – ITEAM**
Módulo 08 – Linguagem de Programação C++
Professor: Msc. Hygo Sousa De Oliveira

> **Conteúdo da apostila:** Unidade 5, seções 5.1 a 5.7 (containers da STL, algoritmos e iteradores, strings, `fstream`, namespaces, lambdas, smart pointers)
> **Tópicos:** `vector`, `list`, `map` e `unordered_map` · algoritmos e iteradores · `std::string` · arquivos com `fstream` · namespaces · expressões lambda · smart pointers

---

## 📌 Como resolver e entregar

> Faça isto **antes de começar a resolver as atividades**.

Faça as atividades na **sua própria cópia** do repositório do curso. Se ainda não criou a sua, siga o passo a passo de [COMO-OBTER-AS-ATIVIDADES.md](../COMO-OBTER-AS-ATIVIDADES.md).

### 1. Copie a pasta `base/` para `resolucao/`

```bash
cp -r unidade-05/base unidade-05/resolucao
```

No PowerShell do Windows: `Copy-Item -Recurse unidade-05\base unidade-05\resolucao`.

> Não altere os arquivos dentro de `base/`: eles pertencem ao professor e podem ser substituídos quando você baixar atualizações.

### 2. Resolva e compile

Abra o arquivo da atividade dentro de `resolucao/`, complete os trechos marcados com `TODO` e compile **sempre com avisos ativados**:

```bash
cd unidade-05/resolucao
g++ -std=c++17 -Wall -Wextra f1_exemplo.cpp -o f1.exe
./f1.exe          # no Windows (CMD/PowerShell): .\f1.exe
```

Troque `f1_exemplo.cpp` e `f1.exe` pelo nome do arquivo da atividade. Atividades com arquivos de dados (`.txt`, `.csv`) devem ser executadas **de dentro da pasta `resolucao/`**.

### 3. Salve o seu progresso na sua cópia

```bash
git add unidade-05/resolucao
git commit -m "feat: unidade 5 - atividades F1 a F3"
git push origin main
```

Faça commits pequenos e frequentes: eles mostram o seu processo. **Não envie arquivos `.exe`** (o `.gitignore` já os ignora).

### 4. Entregue

Quando terminar, marque a entrega com a tag desta unidade e envie ao professor o link da sua cópia:

```bash
git tag atividade-unidade-05
git push origin atividade-unidade-05
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

### 🟢 F1 – Notas em um `vector`: `sort` e `count_if`

📄 **Arquivo base:** `base/f1_vector_sort_count_if.cpp` · **Vale:** 1,0 ponto(s)

Um `std::vector` guarda as notas, e os algoritmos da biblioteca padrão fazem o trabalho pesado, sem laços manuais.

**O que fazer:**
1. Leia a quantidade `n` (entre `1` e `50`) e as `n` notas (`double`) em um `std::vector<double>`. Valide as leituras.
2. Leia um `limite` (`double`).
3. Ordene o vetor em ordem **crescente** com `std::sort(notas.begin(), notas.end())` e mostre-o.
4. Conte com `std::count_if` quantas notas são **maiores** que o limite. A condição é uma **lambda** que captura `limite`.

**Exemplo de execução** (o que o usuário digita aparece depois dos dois-pontos):
```text
Quantidade: 5
Notas: 7.5 4 9 6 10
Limite: 6
Ordenadas: 4 6 7.5 9 10
Acima de 6: 3
```

> 💡 *Dica: `begin()` aponta para o primeiro elemento e `end()` para a posição **depois** do último; nunca desreferencie `end()`. A lambda `[limite](double nota) { return nota > limite; }` guarda uma cópia de `limite`.*

**✅ Critérios de aceite:**
- [ ] O exemplo produz a saída mostrada; com limite `10`, o resultado é `0`
- [ ] Usa `std::sort` e `std::count_if` (sem laço manual para ordenar ou contar)
- [ ] A lambda captura o limite e não repete o valor "fixo" no código
- [ ] `0`, `51` e texto são rejeitados

---

### 🟢 F2 – Separando o nome: `find` e `substr`

📄 **Arquivo base:** `base/f2_string_find_substr.cpp` · **Vale:** 1,0 ponto(s)

Um formulário recebe o nome completo em um só campo, e o sistema precisa separar o primeiro nome do resto.

**O que fazer:**
1. Leia **uma linha** com `std::getline(std::cin, nome)`. Se a leitura falhar ou a linha for vazia, mostre `Entrada invalida.` em `std::cerr` e devolva `1`.
2. Mostre o nome completo e o seu `size()`.
3. Procure o **primeiro espaço** com `find(' ')`. Se não houver (`std::string::npos`), mostre `Resto do nome: (nao informado)`; senão, use `substr` para mostrar o `Primeiro nome` e o `Resto do nome`.
4. Mostre se o nome contém o trecho `Silva` (`sim`/`nao`).

**Exemplo de execução** (o que o usuário digita aparece depois dos dois-pontos):
```text
Nome completo: Ana Maria Silva
Tamanho: 15
Primeiro nome: Ana
Resto do nome: Maria Silva
Contem "Silva": sim
```
```text
Nome completo: Bruno
Tamanho: 5
Primeiro nome: Bruno
Resto do nome: (nao informado)
Contem "Silva": nao
```

> 💡 *Dica: `find` devolve a **posição** do trecho ou `std::string::npos` quando não encontra. Compare sempre com `npos` antes de usar a posição em `substr`. `substr(pos, tamanho)` extrai `tamanho` caracteres a partir de `pos`; sem o segundo argumento, vai até o fim.*

**✅ Critérios de aceite:**
- [ ] Os dois exemplos produzem a saída mostrada
- [ ] A ausência de espaço é tratada comparando com `std::string::npos`
- [ ] Usa `find` e `substr` (sem laço manual caractere a caractere)
- [ ] Linha vazia ou falha de leitura são rejeitadas

---

### 🟢 F3 – Organizando funções em namespaces

📄 **Arquivo base:** `base/f3_namespace_calculos.cpp` · **Vale:** 1,0 ponto(s)

Duas áreas de um sistema podem ter funções com o **mesmo nome** sem conflito, se cada uma morar no seu próprio *namespace*.

**O que fazer:**
1. Crie o `namespace geometria` com `double areaRetangulo(double largura, double altura)`, `double areaCirculo(double raio)` (use `constexpr double PI{3.14159265358979323846};`) e `double calcular(double a, double b)`, que devolve `a * b`.
2. Crie o `namespace financas` com `double jurosSimples(double capital, double taxaPercentual, int meses)`, `double desconto(double valor, double percentual)` e `double calcular(double capital, double taxaPercentual)`, que devolve o capital acrescido da taxa (`capital * (1 + taxa / 100)`).
3. O `main` (pronto) chama tudo com nomes **qualificados** (`geometria::...`). Não use `using namespace` global.
4. Em um comentário, explique por que os dois `calcular` não colidem.

**Saída esperada:**
```text
Area do retangulo 3 x 4: 12.00
Area do circulo r=2: 12.57
Juros simples (1000, 2%, 6 meses): 120.00
Desconto (200, 15%): 170.00
geometria::calcular(3, 4) = 12.00
financas::calcular(1000, 5) = 1050.00
```

> 💡 *Dica: o operador `::` escolhe o nome dentro do namespace. Evitar `using namespace std;` e `using namespace` globais mantém visível de onde cada nome vem. Uma função com o mesmo nome em outro namespace é outra função.*

**✅ Critérios de aceite:**
- [ ] A saída é exatamente a esperada
- [ ] As seis funções estão em dois namespaces e os dois `calcular` têm significados diferentes
- [ ] O código não usa `using namespace` global
- [ ] Comentário explicando por que não há conflito

---

### 🟢 F4 – Alunos por código em um `std::map`

📄 **Arquivo base:** `base/f4_map_de_alunos.cpp` · **Vale:** 1,0 ponto(s)

Um `std::map` associa **chaves** a **valores** e mantém as chaves **ordenadas**. Aqui a chave é o código do aluno.

**O que fazer:**
1. O arquivo base já cria `std::map<int, std::string> alunos` com os códigos `3`, `1` e `2` inseridos **fora de ordem**.
2. Mostre todos os alunos percorrendo o `map` (`codigo - nome`). Observe a ordem.
3. Leia um código e procure-o com **`alunos.find(codigo)`**. Se existir, mostre `Encontrado: <nome>`; senão, `Codigo <N> nao encontrado`.
4. Mostre `Total de alunos: ...` no final e confirme que a busca **não aumentou** o tamanho do mapa.

**Exemplo de execução** (o que o usuário digita aparece depois dos dois-pontos):
```text
Alunos (ordem do map):
1 - Ana
2 - Bruno
3 - Carla
Codigo a buscar: 2
Encontrado: Bruno
Total de alunos: 3
```
```text
Codigo a buscar: 9
Codigo 9 nao encontrado
Total de alunos: 3
```

> 💡 *Dica: `find` devolve um iterador; se for igual a `alunos.end()`, a chave não existe. Cada elemento é um `std::pair`: `it->first` é a chave e `it->second` é o valor. Evite `alunos[9]` para consultar, pois o operador `[]` **cria** a chave `9` se ela não existir.*

**✅ Critérios de aceite:**
- [ ] Os dois exemplos produzem a saída mostrada
- [ ] A busca usa `find` e compara com `end()`; o tamanho continua `3` depois de buscar um código inexistente
- [ ] Os alunos aparecem em ordem crescente de código
- [ ] A leitura é verificada

---

### 🟢 F5 – Gravando e lendo um arquivo texto

📄 **Arquivo base:** `base/f5_gravar_e_ler_arquivo.cpp` · **Vale:** 1,0 ponto(s)

Dados em memória somem quando o programa termina. Um arquivo texto os mantém.

**O que fazer:**
1. Leia `n` (entre `1` e `10`) e os `n` nomes (uma palavra cada, com `std::cin >> nome`).
2. Grave os nomes em `alunos.txt` com `std::ofstream`, **um por linha**. Verifique se o arquivo abriu (`if (!saida)`) e se a escrita deu certo. Mostre `Gravados N nome(s) em alunos.txt`.
3. Leia o arquivo de volta com `std::ifstream` e `std::getline`, mostrando `Lidos do arquivo:` e depois `1: Ana`, `2: Bruno`...
4. Tente abrir `inexistente.txt` e mostre `Arquivo inexistente.txt nao encontrado` **sem** encerrar com erro.

**Exemplo de execução** (o que o usuário digita aparece depois dos dois-pontos):
```text
Quantidade: 2
Nome 1: Ana
Nome 2: Bruno
Gravados 2 nome(s) em alunos.txt
Lidos do arquivo:
1: Ana
2: Bruno
Arquivo inexistente.txt nao encontrado
```

> 💡 *Dica: o arquivo é criado na **pasta de execução** do programa. Coloque a gravação em um bloco `{ }` para o `ofstream` ser fechado (e os dados gravados) antes de você reabrir o arquivo para ler. `while (std::getline(entrada, linha))` repete até acabar o arquivo.*

**✅ Critérios de aceite:**
- [ ] O exemplo produz a saída mostrada e o arquivo `alunos.txt` contém um nome por linha
- [ ] A abertura de cada arquivo é verificada e a falha de escrita é tratada
- [ ] A gravação fica em um escopo que fecha o arquivo antes da leitura
- [ ] A ausência de `inexistente.txt` é tratada sem encerrar com erro
- [ ] `0`, `11` e texto em `n` são rejeitados

---

## 🟡 Nível Intermediário

### 🟡 I1 – `map` × `unordered_map`: contando palavras

📄 **Arquivo base:** `base/i1_map_vs_unordered_map.cpp` · **Vale:** 1,5 ponto(s)

Os dois containers associam chave a valor, mas diferem na **ordem** e no custo. Contar palavras é um bom teste.

**O que fazer:**
1. Leia **uma linha** de texto (palavras minúsculas separadas por espaço) com `std::getline`. Separe as palavras com `std::istringstream` (`while (fluxo >> palavra)`).
2. Conte cada palavra em um `std::map<std::string, int>` **e** em um `std::unordered_map<std::string, int>` (use `contagem[palavra]++`).
3. Mostre o `map` percorrendo-o (`palavra: N`). Para o `unordered_map`, mostre **só a quantidade** de palavras distintas: a ordem dele não é garantida e não deve aparecer na saída.
4. Leia uma palavra a consultar e mostre a contagem nos dois (com `find`, para não criar chaves; palavra ausente conta `0`).
5. Verifique se **todas** as contagens do `map` coincidem com as do `unordered_map` e mostre `Contagens iguais nos dois: sim` ou `nao`.
6. Em um comentário, descreva a diferença de ordenação entre os dois.

**Exemplo de execução** (o que o usuário digita aparece depois dos dois-pontos):
```text
Texto: banana maca banana uva maca banana
map (ordem alfabetica):
banana: 3
maca: 2
uva: 1
unordered_map: 3 palavras distintas
Palavra a consultar: maca
map: 2 | unordered_map: 2
Contagens iguais nos dois: sim
```

> 💡 *Dica: `std::map` mantém as chaves ordenadas (árvore balanceada). `std::unordered_map` usa tabela hash, tem acesso médio mais rápido e **nenhuma ordem garantida**. O `operator[]` cria a chave com valor `0` na primeira vez, o que é conveniente para contar.*

**✅ Critérios de aceite:**
- [ ] O exemplo produz a saída mostrada; palavra inexistente mostra `0` nos dois
- [ ] A saída não depende da ordem do `unordered_map`
- [ ] A consulta usa `find` (não usa `[]`, que inseriria a palavra consultada)
- [ ] Comentário comparando a ordenação dos dois containers

---

### 🟡 I2 – Filtros com lambdas: captura por valor e por referência

📄 **Arquivo base:** `base/i2_lambdas_filtros.cpp` · **Vale:** 1,5 ponto(s)

Uma **lambda** é uma função anônima escrita no ponto de uso. A lista de captura `[ ]` decide o que ela enxerga: `[x]` guarda uma **cópia** de `x`, e `[&x]` usa o **próprio** `x`.

O arquivo base já cria `std::vector<int> numeros{3, 8, 12, 5, 20, 7, 15, 10}` e lê a faixa `minimo` e `maximo`.

**O que fazer:**
1. Mostre os números e a faixa lida.
2. Com `std::copy_if` e `std::back_inserter(filtrados)`, copie para `filtrados` os valores entre `minimo` e `maximo` (inclusive). A lambda captura `minimo` e `maximo` **por valor** e também um contador `verificacoes` **por referência**, incrementado a cada chamada.
3. Mostre `Dentro da faixa: ...` e `Verificacoes feitas: N`.
4. Com `std::for_each` e uma lambda que captura `soma` **por referência**, calcule a soma dos filtrados e mostre `Soma dos filtrados: ...`.
5. Calcule a média dos filtrados e, com outra lambda que a captura **por valor**, mostre os filtrados **maiores que a média**.

**Exemplo de execução** (o que o usuário digita aparece depois dos dois-pontos):
```text
Numeros: 3 8 12 5 20 7 15 10
Minimo e maximo: 6 15
Dentro da faixa: 8 12 7 15 10
Verificacoes feitas: 8
Soma dos filtrados: 52
Maiores que a media dos filtrados (10.4): 12 15
```

> 💡 *Dica: capturas por referência exigem que a variável ainda exista quando a lambda executa. Aqui isso é garantido, pois as lambdas são usadas na hora. `std::back_inserter` está em `<iterator>`; `copy_if` e `for_each` em `<algorithm>`.*

**✅ Critérios de aceite:**
- [ ] O exemplo produz a saída mostrada
- [ ] Há capturas **por valor** (faixa e média) e **por referência** (contador e soma)
- [ ] Usa `copy_if` e `for_each` (sem laços manuais para filtrar e somar)
- [ ] Com faixa `100 200` mostra lista vazia e não divide por zero (trate a lista vazia)

---

### 🟡 I3 – `unique_ptr`, `shared_ptr` e `weak_ptr` em ação

📄 **Arquivo base:** `base/i3_smart_pointers.cpp` · **Vale:** 1,5 ponto(s)

Smart pointers cuidam do `delete` por você. Cada tipo expressa uma **relação de posse** diferente. A classe `Recurso` (já pronta) mostra mensagens ao ser criada e destruída para você acompanhar a vida dos objetos.

**O que fazer** (escreva o corpo de `main`, em três blocos `{ }`, depois de cada título já impresso):
1. **`unique_ptr` (posse exclusiva):** crie `A` com `std::make_unique<Recurso>("A")`, chame `usar()`, **transfira** a posse para `u2` com `std::move` e mostre `u1 vazio: sim` ou `nao` (teste `u1` como `bool`). Chame `usar()` por `u2`.
2. **`shared_ptr` (posse compartilhada):** crie `B` com `std::make_shared`, faça uma **cópia** `s2` dentro de um bloco interno e mostre `Contagem: ` com `use_count()` dentro e depois do bloco.
3. **`weak_ptr` (observador):** crie `C` com `make_shared` dentro de um bloco, atribua a um `std::weak_ptr`, use `lock()` para chamar `usar()` e mostre `Expirou antes: ` (`expired()`). Depois que o bloco acabar, mostre `Expirou depois: `.
4. Em um comentário, explique **quando usar** cada um dos três.

**Saída esperada:**
```text
-- unique_ptr --
Criando A
Usando A
u1 vazio: sim
Usando A
Destruindo A
-- shared_ptr --
Criando B
Contagem: 2
Contagem: 1
Destruindo B
-- weak_ptr --
Criando C
Usando C
Expirou antes: nao
Destruindo C
Expirou depois: sim
```

> 💡 *Dica: `unique_ptr` não pode ser copiado, apenas movido. O `shared_ptr` destrói o objeto quando o **último** dono some. O `weak_ptr` não conta como dono; `lock()` devolve um `shared_ptr` válido (ou vazio, se o objeto já foi destruído). Todos ficam em `<memory>`.*

**✅ Critérios de aceite:**
- [ ] A saída é exatamente a esperada
- [ ] Usa `make_unique`/`make_shared` e **nenhum** `new`/`delete` no código
- [ ] A posse do `unique_ptr` é transferida com `std::move`
- [ ] O `weak_ptr` é consultado com `lock()` e `expired()`
- [ ] Comentário explicando quando usar cada smart pointer

---

### 🟡 I4 – Lendo um CSV com linhas inválidas

📄 **Arquivo base:** `base/i4_arquivo_csv.cpp` · **Vale:** 1,5 ponto(s)

Dados reais chegam sujos: linhas sem separador, notas que não são números, nomes vazios. O programa precisa **seguir em frente** e relatar o que ignorou.

O arquivo `notas.csv` (na pasta `base/`) tem o formato `nome;nota`, com um cabeçalho na linha 1.

**O que fazer:**
1. Abra `notas.csv` com `std::ifstream`. Se não abrir, mostre `Arquivo notas.csv nao encontrado` em `std::cerr` e devolva `1`.
2. Ignore o cabeçalho (linha 1). Para cada linha de dados, **remova um `\r` no fim** (se houver), procure o `;` com `find` e separe `nome` e `nota` com `substr`.
3. Linhas inválidas **não** entram nos cálculos, e cada uma é relatada com o **número da linha** do arquivo:
   - sem `;`: `Linha N invalida: sem separador`
   - nome vazio: `Linha N invalida: nome vazio`
   - nota que não é número (use `std::stod` em `try`/`catch`, conferindo que **todo** o texto foi convertido): `Linha N invalida: nota "texto"`
   - nota fora de `0..10`: `Linha N invalida: nota fora de 0 a 10`
4. No final, mostre `Registros validos`, `Registros invalidos`, a `Media` (duas casas decimais) e o `Melhor` aluno com a nota. Se não houver registros válidos, mostre `Nenhum registro valido` e devolva `1`.

**Saída esperada** (com o `notas.csv` fornecido):
```text
Linha 3 invalida: nota "abc"
Linha 5 invalida: nota fora de 0 a 10
Linha 6 invalida: nome vazio
Linha 8 invalida: sem separador
Registros validos: 3
Registros invalidos: 4
Media: 8.00
Melhor: Elisa (9.5)
```

> 💡 *Dica: `std::stod("abc")` lança `std::invalid_argument`; `std::stod("6x", &pos)` converte só `6` e deixa `pos` em `1`, então confira `pos == texto.size()`. No Windows o arquivo pode ter fim de linha `\r\n`, por isso o `\r` sobra no fim da linha lida por `getline`.*

**✅ Critérios de aceite:**
- [ ] A saída é exatamente a esperada para o arquivo fornecido
- [ ] Cada tipo de linha inválida é identificado com o número correto da linha
- [ ] O arquivo inexistente é tratado (mensagem e código `1`) e o `\r` é removido
- [ ] Usa `find`/`substr` e `std::stod` com `try`/`catch`

---

### 🟡 I5 – `std::list` e iteradores: remover, inserir e ordenar

📄 **Arquivo base:** `base/i5_list_e_iteradores.cpp` · **Vale:** 1,5 ponto(s)

Em uma `std::list` (lista duplamente encadeada), inserir e remover no meio é barato **se você já tem o iterador**. É a hora de dominar iteradores.

**O que fazer:**
1. Leia `n` (entre `1` e `30`) e os `n` valores inteiros para uma `std::list<int>`.
2. **Remova os negativos** percorrendo a lista com um iterador e usando `erase`. Atenção: `erase` invalida o iterador atual. Use o valor que ele **devolve** (`it = lista.erase(it)`). Mostre `Sem negativos: ...`. (Não use `remove_if`.)
3. **Duplique cada número par**: insira uma cópia logo **depois** dele, com `insert`, e avance o iterador para **depois da cópia** para não duplicar infinitamente. Mostre `Pares duplicados: ...`.
4. Ordene com o **método** `lista.sort()` e remova repetidos vizinhos com `lista.unique()`. Mostre `Ordenada sem repetidos: ...`.
5. Mostre `De tras para frente: ...` percorrendo com `rbegin()`/`rend()`.

**Exemplo de execução** (o que o usuário digita aparece depois dos dois-pontos):
```text
Quantidade: 6
Valores: 3 -1 4 -5 4 2
Sem negativos: 3 4 4 2
Pares duplicados: 3 4 4 4 4 2 2
Ordenada sem repetidos: 2 3 4
De tras para frente: 4 3 2
```

> 💡 *Dica: `std::sort` exige iteradores de acesso aleatório e não funciona em `std::list`; use o método `lista.sort()`. `unique()` só remove repetidos **vizinhos**, por isso a ordenação vem antes. `insert(it, x)` insere **antes** de `it`; para inserir depois, use `std::next(it)`.*

**✅ Critérios de aceite:**
- [ ] O exemplo produz a saída mostrada; lista só de negativos termina vazia sem erro
- [ ] A remoção usa `erase` com o iterador devolvido (sem usar um iterador invalidado)
- [ ] A duplicação não entra em laço infinito e usa `insert`
- [ ] Usa `lista.sort()`, `lista.unique()` e `rbegin()`/`rend()`
- [ ] `0`, `31` e texto são rejeitados

---

## 🔴 Nível Difícil

### 🔴 D1 – Projeto da unidade: Cadastro de alunos

📄 **Arquivo base:** `base/d1_cadastro_de_alunos.cpp` · **Vale:** 2,0 ponto(s)

**Projeto integrador da Unidade 5.** Um cadastro de alunos (nome, matrícula e nota) guardado em `std::vector`, organizado em um **namespace**, com algoritmos e lambdas e persistência em arquivo. O `main` (pronto) exercita tudo. A sua tarefa é implementar as funções do namespace `cadastro`.

**Funções a implementar** (os protótipos estão no arquivo base):

- `struct Aluno { std::string nome; int matricula; double nota; };`
- `bool validar(const Aluno& aluno, std::string& erro)`: `Nome vazio`, `Matricula invalida` (`<= 0`) ou `Nota fora de 0 a 10`, **nessa ordem de verificação**.
- `bool adicionar(std::vector<Aluno>& turma, const Aluno& aluno, std::string& erro)`: valida e rejeita matrícula repetida (`Matricula duplicada`). Use `std::any_of` com lambda para a repetição.
- `void ordenarPorNome(std::vector<Aluno>&)` e `void ordenarPorNota(std::vector<Aluno>&)` (maior nota primeiro; empate pelo nome). Use `std::sort` com **lambda**.
- `std::vector<Aluno> aprovados(const std::vector<Aluno>& turma, double notaMinima)`: usa `std::copy_if` com lambda que **captura** `notaMinima`.
- `void listar(const std::vector<Aluno>& turma)`: uma linha `Nome (mat N): nota` por aluno ou `(lista vazia)`.
- `bool salvar(const std::vector<Aluno>& turma, const std::string& caminho)`: grava `nome;matricula;nota`, um por linha; `false` se o arquivo não abrir ou a escrita falhar.
- `bool carregar(std::vector<Aluno>& turma, const std::string& caminho, std::string& erro)`: limpa `turma` e lê o arquivo. Se não abrir, `erro = "Arquivo nao encontrado"`; se uma linha estiver malformada, `erro = "Linha N invalida"` (N = número da linha).

**Saída esperada:**
```text
== Turma vazia ==
(lista vazia)
== Cadastro ==
Adicionado: Carla
Adicionado: Ana
Adicionado: Bruno
Adicionado: Davi
Rejeitado: Nome vazio
Rejeitado: Matricula duplicada
Rejeitado: Nota fora de 0 a 10
== Por nome ==
Ana (mat 101): 8.5
Bruno (mat 102): 4.5
Carla (mat 103): 6
Davi (mat 104): 9.5
== Por nota (maior primeiro) ==
Davi (mat 104): 9.5
Ana (mat 101): 8.5
Carla (mat 103): 6
Bruno (mat 102): 4.5
== Aprovados (nota >= 6) ==
Davi (mat 104): 9.5
Ana (mat 101): 8.5
Carla (mat 103): 6
== Arquivo ==
Salvo: turma.txt (4 registro(s))
Carregados: 4 registro(s)
Davi (mat 104): 9.5
Ana (mat 101): 8.5
Carla (mat 103): 6
Bruno (mat 102): 4.5
Erro ao carregar: Arquivo nao encontrado
Erro ao carregar: Linha 1 invalida
```

**Documentação:** no topo do arquivo, comente **onde smart pointers seriam apropriados** neste projeto e **onde valores diretos são mais simples** (e por quê), e registre **três testes** de entrada inválida além dos do `main`.

> 💡 *Dica: para converter o texto da matrícula e da nota, use `std::stoi` e `std::stod` dentro de `try`/`catch`, e confira que todo o texto foi convertido. `std::any_of(turma.begin(), turma.end(), [&](const Aluno& a) { return a.matricula == aluno.matricula; })` verifica a duplicidade.*

**✅ Critérios de aceite:**
- [ ] A saída é exatamente a esperada
- [ ] Uso correto da STL: `vector`, `sort`, `copy_if`, `any_of` (30%)
- [ ] Strings e arquivos: `find`/`substr`, `stoi`/`stod` e verificações de abertura e escrita (25%)
- [ ] Namespace `cadastro` e lambdas (com captura) nos lugares indicados (20%)
- [ ] Tratamento de erros: arquivo inexistente, linha inválida, lista vazia (15%)
- [ ] Organização e documentação, incluindo a reflexão sobre smart pointers (10%)

---

### 🔴 D2 – Ranking de palavras de um texto

📄 **Arquivo base:** `base/d2_contador_de_palavras.cpp` · **Vale:** 2,0 ponto(s)

Dado um texto, descubra as palavras mais frequentes. Maiúsculas e pontuação não devem fazer diferença: `Programa,` e `programa` são a mesma palavra.

O arquivo `texto.txt` (na pasta `base/`) tem três linhas com letras, pontuação e maiúsculas.

**O que fazer:**
1. Abra `texto.txt` com `std::ifstream`. Se não abrir, mostre `Arquivo texto.txt nao encontrado` em `std::cerr` e devolva `1`.
2. Leia palavra por palavra (`arquivo >> palavra`). **Normalize** cada uma: converta para minúsculas e **descarte** tudo que não for letra (`std::tolower` e `std::isalpha`, de `<cctype>`, com conversão para `unsigned char`). Ignore palavras que ficarem vazias.
3. Conte em um `std::map<std::string, int>` e mostre `Total de palavras` e `Palavras distintas`.
4. Copie o `map` para um `std::vector<std::pair<std::string, int>>` e **ordene** com `std::sort` e uma lambda: **maior frequência primeiro** e, em empate, **ordem alfabética**. Mostre o `Top 3`.
5. Grave o **ranking completo** em `ranking.txt` (uma linha `palavra frequencia` por palavra, na ordem do ranking), verificando a abertura e a escrita. Mostre `Ranking gravado em ranking.txt (N linhas)`.
6. Leia a **primeira linha** de `ranking.txt` e mostre `Primeira linha do arquivo: ...`.

**Saída esperada** (com o `texto.txt` fornecido):
```text
Total de palavras: 23
Palavras distintas: 13
Top 3:
1. e: 3
2. problemas: 3
3. resolver: 3
Ranking gravado em ranking.txt (13 linhas)
Primeira linha do arquivo: e 3
```

> 💡 *Dica: `std::tolower` recebe e devolve `int`: use `static_cast<unsigned char>(c)` ao chamá-la com um `char`. A lambda do `sort` compara dois `pair`: `a.second != b.second ? a.second > b.second : a.first < b.first`.*

**✅ Critérios de aceite:**
- [ ] A saída é exatamente a esperada para o arquivo fornecido
- [ ] A normalização ignora maiúsculas e pontuação (`Programa,` e `programa` contam juntas)
- [ ] O ranking usa `std::sort` com lambda e desempata por ordem alfabética
- [ ] Verifica a abertura dos dois arquivos e a escrita; o arquivo inexistente é tratado

---

### 🔴 D3 – Árvore de tarefas: `shared_ptr` e `weak_ptr` sem ciclos

📄 **Arquivo base:** `base/d3_arvore_shared_weak.cpp` · **Vale:** 2,0 ponto(s)

Em uma árvore de tarefas, cada tarefa **possui** suas filhas e **conhece** a sua pai. Se as duas ligações fossem `shared_ptr`, pai e filha se segurariam mutuamente (**ciclo**) e **nunca** seriam destruídas. A solução é a ligação de volta ser um `weak_ptr`.

**O que fazer:**
1. Escreva a classe `Tarefa` (o arquivo base traz o esqueleto):
   - atributos privados: `nome_`, `pai_` (`std::weak_ptr<Tarefa>`) e `filhas_` (`std::vector<std::shared_ptr<Tarefa>>`);
   - construtor `explicit Tarefa(const std::string& nome)` que mostra `Criando <nome>` e destrutor que mostra `Destruindo <nome>`;
   - `void definirPai(const std::shared_ptr<Tarefa>& pai)` e `void adicionarFilha(const std::shared_ptr<Tarefa>& filha)`;
   - `std::string caminho() const`: devolve o caminho da raiz até a tarefa, como `Projeto/Etapa1/Passo1` (use `pai_.lock()` e **recursão**; sem pai, devolve só o nome).
2. Escreva `void ligar(const std::shared_ptr<Tarefa>& pai, const std::shared_ptr<Tarefa>& filha)`, que chama `adicionarFilha` no pai e `definirPai` na filha.
3. O `main` (pronto) monta a árvore `Projeto` → `Etapa1` → `Passo1`, mostra o caminho e as contagens de referência e prova que não há vazamento: todas as tarefas são destruídas ao fim do bloco.
4. Em um comentário, explique **(a)** por que `use_count` da raiz é `1` e o da etapa é `2`, e **(b)** o que aconteceria se `pai_` fosse `shared_ptr`.

**Saída esperada:**
```text
Criando Projeto
Criando Etapa1
Criando Passo1
Caminho: Projeto/Etapa1/Passo1
use_count raiz: 1
use_count etapa: 2
use_count passo: 2
Passo ainda vivo: sim
Destruindo Projeto
Destruindo Etapa1
Destruindo Passo1
Fim do bloco
```

> 💡 *Dica: `weak_ptr` **não** aumenta `use_count`. Por isso a raiz tem um dono só (a variável `raiz`), enquanto a etapa tem dois (a variável `etapa` e o vetor `filhas_` da raiz). Ao fim do bloco, a destruição da raiz solta a etapa, que solta o passo, e a mensagem de cada destrutor sai antes da destruição dos membros dele.*

**✅ Critérios de aceite:**
- [ ] A saída é exatamente a esperada, com as três destruições
- [ ] A ligação para o pai é `weak_ptr` e as filhas são `shared_ptr`
- [ ] `caminho()` usa `lock()` e recursão e trata o caso da raiz (sem pai)
- [ ] O código não usa `new`/`delete` (usa `make_shared`)
- [ ] Comentário com as respostas (a) e (b)

---

### 🔴 D4 – Relatório de vendas só com algoritmos da STL

📄 **Arquivo base:** `base/d4_vendas_com_algoritmos.cpp` · **Vale:** 2,0 ponto(s)

Quase todo laço manual sobre um container tem um algoritmo pronto. Aqui você monta um relatório **sem escrever laços de cálculo**: cada etapa é uma chamada a um algoritmo, com uma lambda quando precisar.

**O que fazer:**
1. Leia `n` (entre `1` e `20`) e `n` vendas no formato `produto preco quantidade` (`std::string`, `double`, `int`), guardando-as em `std::vector<Venda>`. `Venda` é uma `struct` com esses três campos. Valide as leituras e rejeite preço negativo ou quantidade negativa.
2. Com **`std::transform`**, gere um `std::vector<double>` com o total de cada venda (`preco * quantidade`) e mostre `Totais: ...`.
3. Com **`std::accumulate`** (`<numeric>`), mostre `Soma: ...`.
4. Com **`std::max_element`** e uma lambda, mostre `Maior venda: produto (total)`.
5. Com **`std::all_of`** e **`std::any_of`**, mostre `Todas com quantidade > 0: sim/nao` e `Alguma abaixo de 10: sim/nao` (total abaixo de `10`).
6. Com o idioma **erase-remove** (`vendas.erase(std::remove_if(...), vendas.end())`), remova as vendas com total **abaixo de 20** e mostre `Apos remover totais abaixo de 20: ...` (só os nomes).
7. Com **`std::stable_partition`**, deixe **primeiro** as vendas com total `>= 60`, **mantendo a ordem relativa** dentro de cada grupo, e mostre `Ordem estavel (totais >= 60 primeiro): ...`.

**Exemplo de execução** (o que o usuário digita aparece depois dos dois-pontos):
```text
Quantidade de vendas: 5
Vendas (produto preco quantidade):
caneta 2.5 10
caderno 12 5
mochila 85 2
lapis 1 8
agenda 30 3
Totais: 25 60 170 8 90
Soma: 353
Maior venda: mochila (170)
Todas com quantidade > 0: sim
Alguma abaixo de 10: sim
Apos remover totais abaixo de 20: caneta caderno mochila agenda
Ordem estavel (totais >= 60 primeiro): caderno mochila agenda caneta
```

> 💡 *Dica: `std::remove_if` não apaga nada de fato: ele **reorganiza** e devolve o novo fim lógico; é o `erase` que encolhe o vetor. `stable_partition` devolve um iterador para o início do segundo grupo. Calcule o total dentro de uma função auxiliar `total(const Venda&)` para reaproveitar nas lambdas.*

**✅ Critérios de aceite:**
- [ ] O exemplo produz a saída mostrada
- [ ] Cada etapa usa o algoritmo pedido (sem laço manual para somar, buscar o maior, filtrar ou particionar)
- [ ] O `erase-remove` é feito corretamente e `stable_partition` mantém a ordem relativa
- [ ] Entradas inválidas são rejeitadas; lista que fica vazia após a remoção não quebra o programa

---

### 🔴 D5 – Analisador de arquivo de log

📄 **Arquivo base:** `base/d5_analisador_de_log.cpp` · **Vale:** 2,0 ponto(s)

Servidores registram eventos em arquivos de log. Neste desafio, você lê um log, **ignora linhas quebradas**, conta eventos por nível, lista os erros em ordem de horário e grava um resumo.

O arquivo `servidor.log` (na pasta `base/`) tem linhas no formato:
`AAAA-MM-DD HH:MM:SS NIVEL modulo: mensagem` (por exemplo `2026-11-03 14:23:10 ERROR db: falha ao conectar`).

**O que fazer:**
1. Abra `servidor.log`. Se não abrir, mostre `Arquivo servidor.log nao encontrado` em `std::cerr` e devolva `1`.
2. Leia linha a linha (removendo um `\r` no fim). Extraia com `std::istringstream`: `data`, `hora`, `nivel`, `modulo` (com `:` no fim) e o **resto** da linha (`std::getline`, sem o espaço inicial) como mensagem.
3. A linha é **válida** se: `data` tem 10 caracteres com `-` nas posições 4 e 7; `hora` tem 8 caracteres com `:` nas posições 2 e 5; `nivel` é `INFO`, `WARN` ou `ERROR`; `modulo` termina em `:`. Linha inválida: mostre `Linha N ignorada (formato invalido)` e siga.
4. Conte os níveis em um `std::map<std::string, int>` e mostre `Linhas validas`, `Linhas ignoradas` e a contagem de `INFO`, `WARN` e `ERROR` (nível sem ocorrências mostra `0`).
5. Guarde os eventos `ERROR` em um vetor e **ordene por data e hora** com `std::sort` e lambda. Mostre `Erros em ordem de horario:` e, para cada um, `HH:MM:SS [modulo] mensagem` (modulo **sem** o `:`).
6. Grave em `resumo.txt` a linha `Total=N INFO=A WARN=B ERROR=C`, verifique a escrita, mostre `Resumo gravado em resumo.txt`, leia a linha de volta e mostre `Primeira linha do resumo: ...`.

**Saída esperada** (com o `servidor.log` fornecido):
```text
Linha 5 ignorada (formato invalido)
Linhas validas: 7
Linhas ignoradas: 1
INFO: 3
WARN: 1
ERROR: 3
Erros em ordem de horario:
14:21:30 [web] certificado expirado
14:23:10 [db] falha ao conectar
14:26:02 [web] timeout na rota /notas
Resumo gravado em resumo.txt
Primeira linha do resumo: Total=7 INFO=3 WARN=1 ERROR=3
```

> 💡 *Dica: depois de `>> modulo`, o resto da linha começa com um espaço; use `std::getline(fluxo, mensagem)` e remova esse primeiro espaço com `substr(1)` (se existir). Como data e hora têm tamanho fixo, comparar `data + " " + hora` como `std::string` ordena cronologicamente. Para `modulo`, use `modulo.substr(0, modulo.size() - 1)`.*

**✅ Critérios de aceite:**
- [ ] A saída é exatamente a esperada para o arquivo fornecido
- [ ] A validação cobre os quatro campos e informa o número da linha ignorada
- [ ] Os erros saem ordenados por horário (o log tem um erro fora de ordem) e usam lambda no `sort`
- [ ] Arquivo inexistente, falha de escrita e `\r` de fim de linha são tratados

---

## 📊 Tabela Resumo das Atividades

| Atividade | Tópico principal | Nível | Pontos | Arquivo base |
|-----------|------------------|-------|--------|--------------|
| F1 | `std::vector`, `std::sort` e `std::count_if` com lambda | 🟢 | 1,0 | `f1_vector_sort_count_if.cpp` |
| F2 | `std::string`, `size`, `find`, `substr` e `std::string::npos` | 🟢 | 1,0 | `f2_string_find_substr.cpp` |
| F3 | `namespace`, operador `::` e nomes iguais em contextos diferentes | 🟢 | 1,0 | `f3_namespace_calculos.cpp` |
| F4 | `std::map`, iteração ordenada e busca com `find` | 🟢 | 1,0 | `f4_map_de_alunos.cpp` |
| F5 | `ofstream`, `ifstream`, `getline` e verificação de abertura | 🟢 | 1,0 | `f5_gravar_e_ler_arquivo.cpp` |
| I1 | Comparação entre `std::map` e `std::unordered_map` | 🟡 | 1,5 | `i1_map_vs_unordered_map.cpp` |
| I2 | Expressões lambda, `[valor]`, `[&referencia]` e `std::copy_if` | 🟡 | 1,5 | `i2_lambdas_filtros.cpp` |
| I3 | Posse exclusiva, posse compartilhada e observador sem posse | 🟡 | 1,5 | `i3_smart_pointers.cpp` |
| I4 | `ifstream`, `getline`, `find`/`substr` e `std::stod` com tratamento de erros | 🟡 | 1,5 | `i4_arquivo_csv.cpp` |
| I5 | `std::list`, iteradores, `erase`/`insert`, `sort` e `unique` | 🟡 | 1,5 | `i5_list_e_iteradores.cpp` |
| D1 | Integração: `vector`, algoritmos, lambdas, namespace, strings e arquivos | 🔴 | 2,0 | `d1_cadastro_de_alunos.cpp` |
| D2 | Arquivos, strings, `map`, `sort` com lambda e persistência do resultado | 🔴 | 2,0 | `d2_contador_de_palavras.cpp` |
| D3 | Posse compartilhada, `weak_ptr` para a ligação de volta e contagem de referências | 🔴 | 2,0 | `d3_arvore_shared_weak.cpp` |
| D4 | `transform`, `accumulate`, `max_element`, `remove_if`, `stable_partition`, `any_of`/`all_of` | 🔴 | 2,0 | `d4_vendas_com_algoritmos.cpp` |
| D5 | Arquivos, strings, `map`, `sort` com lambda e tratamento de linhas inválidas | 🔴 | 2,0 | `d5_analisador_de_log.cpp` |

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
