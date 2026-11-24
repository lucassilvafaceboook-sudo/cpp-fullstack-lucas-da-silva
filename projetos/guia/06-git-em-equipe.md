# Guia 6 — Git em equipe

**Objetivo:** quatro pessoas mexendo no mesmo projeto **sem apagar o trabalho umas das outras**, e deixando um histórico que mostra a contribuição de cada um.

🎬 **No demo:** o projeto foi construído em *commits* pequenos, com uma *tag* por passo (`demo-passo-0` … `demo-passo-6`). Veja como revisar um passo na seção "Para os alunos" de [`demo/ROTEIRO-LIVE-CODING.md`](../demo/ROTEIRO-LIVE-CODING.md).

Pré-requisito: a cópia da equipe criada e os colaboradores convidados ([`COMO-OBTER-AS-ATIVIDADES.md`](../../COMO-OBTER-AS-ATIVIDADES.md), seção 7) e o Git identificado com o seu nome e e-mail ([guia 1](01-preparar-ambiente.md), seção 4).

## 1. A ideia em uma figura

```
main  ───●─────────●───────────────●────────►   (sempre funcionando)
          \       /               /
 feature   ●──●──●   (Pull Request, revisado por um colega, depois "Merge")
```

- **`main`** é a versão que funciona. Ninguém desenvolve direto nela.
- Cada tarefa é feita em um **ramo** (*branch*) próprio, curto e com um nome claro: `feature/rotas-livros`, `feature/tela-autores`, `fix/validacao-isbn`.
- Quando a tarefa fica pronta, abre-se um **Pull Request (PR)** no GitHub; **outro integrante** olha o código e clica em *Merge*. Isso também vale como revisão de código.

> Os Pull Requests da *sua equipe* funcionam normalmente. A regra de "PR fechado automaticamente" vale só para o repositório oficial do professor.

## 2. Combinados da equipe (conversem no dia 5)

1. **Quem é dono de quê.** Dividam o trabalho por **arquivos**, para ninguém editar o mesmo arquivo ao mesmo tempo. Exemplo para o tema Biblioteca:

   | Pessoa | Tarefa | Arquivos principais |
   |--------|--------|---------------------|
   | A | banco | `schema.sql`, `autor_repositorio.*` |
   | B | livros (API) | `livro_repositorio.*`, `rotas_livros.*` |
   | C | front-end | `public/*` |
   | D | documentação e testes com `curl` | `README.md`, `EQUIPE.md`, apoio na validação |

   E **revezem** nos dias seguintes: todos devem passar por banco, API e front.

2. **Arquivos compartilhados** (`main.cpp`, `schema.sql`, `config.js`, `build.bat`) são os que mais dão conflito. Antes de editar um deles, **avise no grupo** e faça um commit pequeno e rápido.
3. **Ritual:** ao começar a trabalhar, `git pull`; ao terminar um pedaço, commit e push. Nada de ficar três horas sem sincronizar.
4. **Quem revisa o PR de quem** (por exemplo, em ciclo: A→B→C→D→A).

## 3. Passo a passo do dia a dia

```bash
# 1) Começar o dia: atualizar a main
git switch main
git pull

# 2) Criar o seu ramo para a tarefa
git switch -c feature/rotas-livros

# 3) Trabalhar. Ver o que mudou:
git status
git diff

# 4) Salvar um pedaço pronto (commit pequeno!)
git add src/livro_repositorio.hpp src/livro_repositorio.cpp
git commit -m "Adiciona LivroRepositorio com listar e buscar"

# 5) Enviar o ramo ao GitHub
git push -u origin feature/rotas-livros       # a 1ª vez; depois só "git push"
```

6. No GitHub, aparece o aviso **Compare & pull request**. Clique, escreva o que mudou e **peça a revisão** de um colega.
7. O revisor lê as alterações (aba *Files changed*), comenta o que for preciso e, estando tudo certo, clica em **Merge pull request**.
8. Todos voltam à `main` e atualizam: `git switch main` e `git pull`. O ramo antigo pode ser apagado: `git branch -d feature/rotas-livros`.

**Dica de ouro:** antes de abrir o PR (e sempre que a `main` andar), traga as novidades para o seu ramo: `git pull origin main`. Conflitos pequenos agora são melhores do que conflitos enormes depois.

## 4. Commits que contam uma história

- **Pequenos e frequentes**: um commit = uma ideia. `git add` só dos arquivos daquela ideia (evite `git add .` sem conferir `git status`).
- **Mensagem no imperativo, dizendo o que mudou:**

  | ✅ Bom | ❌ Ruim |
  |--------|---------|
  | `Adiciona validação do ISBN no POST de livros` | `mudanças` |
  | `Corrige 404 ao buscar livro inexistente` | `arrumei` |
  | `Cria tela de autores com menu` | `final` / `final2` / `agora vai` |

- Cada pessoa commita **com o próprio usuário** (é o que o professor usa no ajuste individual; veja a [rubrica](../rubrica.md)). Se fizerem programação em dupla, quem digitou faz o commit e a outra pessoa entra como **coautora**, com esta linha no fim da mensagem (depois de uma linha em branco):

  ```
  Adiciona busca por gênero

  Co-authored-by: Nome da Colega <email-da-colega@exemplo.com>
  ```

- Não versionem: a pasta `build/`, executáveis (`*.exe`), senhas e arquivos pessoais. O `.gitignore` já cobre `build/` e `*.exe`.

## 5. Conflitos: não entre em pânico

Um **conflito** acontece quando duas pessoas mudam a **mesma parte** do mesmo arquivo. O Git não decide por vocês; ele marca o arquivo:

```
<<<<<<< HEAD
    servidor.Get("/api/livros", listarLivros);
=======
    servidor.Get("/api/livros", rotaListarLivros);
>>>>>>> feature/outro-ramo
```

Como resolver:

1. Abra o arquivo no VS Code: ele mostra os botões **Accept Current Change**, **Accept Incoming Change** e **Accept Both Changes**. Escolha (ou edite à mão) e **apague as linhas** `<<<<<<<`, `=======` e `>>>>>>>`.
2. Compile e teste: o resultado final tem que funcionar.
3. `git add arquivo` e depois `git commit` (o Git já sugere a mensagem de *merge*).

Quando o conflito for entre o trabalho de duas pessoas, **resolvam juntos**: quem entende cada lado precisa estar na conversa.

## 6. Comandos de socorro

| Situação | Comando |
|----------|---------|
| Ver o estado e o que mudou | `git status`, `git diff` |
| Ver o histórico bonito | `git log --oneline --graph --all` |
| Quantos commits cada um fez | `git shortlog -sn` |
| Descartar a mudança de **um arquivo** ainda não commitado | `git restore arquivo.cpp` |
| Guardar o trabalho pela metade para trocar de ramo | `git stash` (e `git stash pop` para voltar) |
| Commitei no ramo errado (ainda **sem** `push`) | peça ajuda ao professor ou a um colega **antes** de mexer: `git reset` mal usado perde trabalho |
| `rejected ... non-fast-forward` ao dar `push` | alguém enviou antes: `git pull` e tente de novo |
| Mensagem do último commit errada (sem `push`) | `git commit --amend -m "Nova mensagem"` |

Evitem `git push --force` e `git reset --hard`. Se um comando parece "perigoso", pergunte antes.

## 7. Entrega: a tag `projeto-final`

No **dia 9**, com tudo já na `main` (e o `EQUIPE.md` preenchido):

```bash
git switch main
git pull
git tag projeto-final
git push origin projeto-final
```

Conferência: no GitHub, em *Releases/Tags*, deve aparecer `projeto-final`. Depois, enviem ao professor o **link da cópia da equipe** e o nome da tag.

Precisou corrigir algo depois de marcar? Apaguem e criem de novo:

```bash
git tag -d projeto-final
git push origin :refs/tags/projeto-final
git tag projeto-final
git push origin projeto-final
```

## 8. Checklist do dia a dia

- [ ] `git pull` antes de começar
- [ ] Trabalho em um **ramo** (não na `main`)
- [ ] Commits pequenos, com mensagem clara e no **meu** usuário
- [ ] `git push` ao terminar um pedaço
- [ ] Pull Request revisado por um colega antes do *merge*
- [ ] O projeto **compila e roda** na `main` depois do merge

## 9. Erros comuns

| Sintoma | Causa e solução |
|---------|-----------------|
| `Author identity unknown` | Falta `git config --global user.name` e `user.email` (guia 1). |
| Meus commits aparecem como outra pessoa | O `user.email` do computador não é o e-mail da sua conta do GitHub. Corrija e avise o professor para os commits antigos. |
| `Permission denied` / 403 ao dar `push` | Você não foi convidado como colaborador, ou o convite não foi aceito (veja o e-mail/GitHub). |
| `warning: LF will be replaced by CRLF` | Aviso normal no Windows; pode ignorar. |
| A `main` quebrou depois do merge | Reverter pelo botão **Revert** do PR no GitHub, ou corrigir com um novo PR pequeno. Avisem o grupo. |
