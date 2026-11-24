# Como obter e entregar as atividades

O repositório oficial do curso (`Hygo/c--fullstack-iteam-2sem`) é o **material do professor** e é somente para leitura. As atividades **não** são feitas nele e **não** se envia Pull Request para lá: cada aluno cria a **sua própria cópia** e trabalha nela. O projeto final é feito em equipe, em **uma cópia por equipe** (seção 7).

> Pull Requests abertos no repositório oficial são fechados automaticamente.

## O que você precisa

- Uma conta no GitHub
- [Git](https://git-scm.com/downloads) instalado (teste com `git --version`)
- Um compilador C++ com suporte a C++17 (teste com `g++ --version`). No Windows, o passo a passo do MSYS2 está em [`projetos/guia/01-preparar-ambiente.md`](projetos/guia/01-preparar-ambiente.md)
- Um editor ou IDE (veja a unidade 1 da apostila), por exemplo o Visual Studio Code

## 1. Criar a sua cópia (só uma vez)

1. Abra https://github.com/Hygo/c--fullstack-iteam-2sem
2. Clique em **Use this template** → **Create a new repository**.
3. Em *Owner*, escolha a sua conta. Em *Repository name*, use `cpp-fullstack-seunome`.
4. Escolha a visibilidade:
   - **Public**: mais simples, o professor acessa direto pelo link.
   - **Private**: depois, convide o usuário `Hygo` em *Settings → Collaborators*.
5. Deixe **Include all branches** desmarcado e clique em **Create repository**.

> Não use o botão *Fork*. O *Use this template* gera uma cópia independente, só sua.

## 2. Baixar a sua cópia para o computador

Troque `SEU-USUARIO` e `seunome` pelos seus dados:

```bash
git clone https://github.com/SEU-USUARIO/cpp-fullstack-seunome.git
cd cpp-fullstack-seunome
```

A partir daqui, `origin` é a **sua cópia** (onde você envia o seu trabalho).

## 3. Conectar ao repositório do professor (só uma vez)

Isso serve apenas para **baixar** os conteúdos novos:

```bash
git remote add professor https://github.com/Hygo/c--fullstack-iteam-2sem.git
git remote set-url --push professor DESATIVADO
git remote -v
```

A segunda linha é uma trava de segurança: com ela, `git push professor` falha, então você nunca envia nada ao repositório original por engano.

## 4. Fazer as atividades

Cada unidade tem um `exercicios.md` com as instruções. Em resumo: copie `base/` para `resolucao/`, resolva ali dentro, compile com `g++ -std=c++17 -Wall -Wextra` e salve o progresso na **sua** cópia:

```bash
git add unidade-01/resolucao
git commit -m "feat: unidade 1 - atividades F1 a F3"
git push origin main
```

Faça commits pequenos e frequentes. Eles mostram o seu processo, não só o resultado final. Não envie arquivos `.exe` (o `.gitignore` já os ignora).

## 5. Receber uma unidade nova

As unidades são liberadas aos poucos. Quando o professor avisar que uma unidade foi liberada (exemplo com `unidade-02`):

```bash
git fetch professor
git checkout professor/main -- unidade-02
git add unidade-02
git commit -m "Adiciona material da unidade 2"
git push origin main
```

O `git checkout professor/main -- pasta` copia **somente aquela pasta** do professor para a sua cópia. O que você já fez nas outras pastas não é alterado.

> Atenção: se você já tiver alterado arquivos **dentro da pasta que está baixando**, eles serão sobrescritos pela versão do professor. É por isso que você resolve em `resolucao/` e não mexe em `base/`; mesmo assim, faça uma cópia do seu trabalho antes.

## 6. Entregar as atividades de uma unidade

1. Marque a entrega com uma tag e envie. O nome da tag é sempre `atividade-unidade-` seguido do número da unidade com dois dígitos (exemplo com a unidade 1):

   ```bash
   git tag atividade-unidade-01
   git push origin atividade-unidade-01
   ```

2. Envie ao professor o **link da sua cópia** e o **nome da tag**, pelo canal combinado com a turma.

> Se precisar corrigir algo depois de marcar a tag, apague-a e crie de novo: `git tag -d atividade-unidade-01`, `git push origin :refs/tags/atividade-unidade-01`, e repita o passo 1. Tudo deve estar entregue até o prazo informado pelo professor.

## 7. Projeto final em equipe (equipes de 4)

O projeto fica na pasta [`projetos/`](projetos/). Em vez de uma cópia por aluno, a equipe usa **uma única cópia**:

1. **Um** integrante cria a cópia da equipe (passo 1), com o nome `cpp-fullstack-equipe-NOME` (troque `NOME` pelo nome da equipe).
2. Esse integrante convida os outros três em *Settings → Collaborators* e convida também o usuário `Hygo`.
3. Todos fazem `git clone` da cópia da equipe. Trabalhem em ramos (*branches*) e reúnam o trabalho com `git pull`/`git merge` (veja o guia `projetos/guia/06-git-em-equipe.md`).
4. Dentro da cópia da equipe, copie o *starter kit* e trabalhe na cópia:

   ```bash
   cp -r projetos/starter-kit projetos/projeto-equipe
   ```

5. Preencha o arquivo `projetos/EQUIPE.md` (nomes, tema, papéis, como executar).
6. Para entregar, marque a tag `projeto-final` na cópia da equipe e envie ao professor o link e o nome da tag:

   ```bash
   git tag projeto-final
   git push origin projeto-final
   ```

A contribuição individual é avaliada pelo histórico de *commits* de cada integrante e por perguntas na apresentação, então **cada pessoa deve fazer commits com o próprio usuário**.

## Dúvidas comuns

**Posso abrir um Pull Request no repositório do professor?**
Não. Ele será fechado automaticamente. A entrega é feita pelo link da sua cópia.

**O `git push` pede usuário e senha e dá erro.**
O GitHub não aceita mais a senha da conta no Git. Use o GitHub CLI (`gh auth login`) ou o Git Credential Manager, que abre o login pelo navegador.

**O terminal diz que `g++` não é reconhecido.**
O compilador não está instalado ou não está no `PATH`. Instale pelo guia do MSYS2 e abra um terminal novo. Instalar apenas o editor não é suficiente.

**Errei e quero desfazer um arquivo.**
Antes de fazer commit: `git restore nome_do_arquivo.cpp`.
