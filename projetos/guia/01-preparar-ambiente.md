# Guia 1 — Preparar o ambiente (Windows)

**Quando fazer:** o quanto antes, de preferência antes do dia 6. **Todos os 4 integrantes** da equipe precisam de um ambiente funcionando.

Vamos instalar quatro coisas e testar tudo no final:

| O quê | Para quê |
|-------|----------|
| **MSYS2 (UCRT64)** | compilador `g++` e a biblioteca para falar com o MariaDB |
| **Docker Desktop** | roda o banco de dados MariaDB em um *container* (um comando sobe tudo) |
| **Git** | versionamento (já instalado se você fez a seção 1 de [`COMO-OBTER-AS-ATIVIDADES.md`](../../COMO-OBTER-AS-ATIVIDADES.md)) |
| **VS Code** | editor (opcional, mas é o que usamos no curso) |

> Já tem um `g++` funcionando (por exemplo, do MinGW usado nas unidades)? Rode `g++ --version` e `g++ -dumpmachine`. Para este projeto, o caminho testado é o **MSYS2 UCRT64**. Misturar compiladores diferentes é a causa mais comum de erros estranhos de `undefined reference` e de DLLs faltando.

## 1. MSYS2 e o compilador

1. Baixe o instalador em <https://www.msys2.org> e instale em `C:\msys64` (o caminho padrão).
2. Abra o **MSYS2 UCRT64** pelo menu Iniciar (o ícone de fundo azul/ucrt; **não** o "MSYS2 MSYS"). A janela mostra `UCRT64` no prompt.
3. Atualize o sistema de pacotes (se o terminal pedir para fechar no meio, feche, abra de novo e repita):

   ```bash
   pacman -Syu
   ```

4. Instale o compilador, o depurador e a biblioteca cliente do MariaDB:

   ```bash
   pacman -S --needed mingw-w64-ucrt-x86_64-gcc mingw-w64-ucrt-x86_64-gdb mingw-w64-ucrt-x86_64-libmariadbclient
   ```

5. Confira:

   ```bash
   g++ --version
   mariadb_config --version
   ls /ucrt64/include/mariadb/mysql.h
   ```

   Os três comandos devem funcionar (o último deve mostrar o caminho do arquivo `mysql.h`).

### Deixar o `g++` disponível fora do terminal do MSYS2 (recomendado)

Para compilar pelo terminal do VS Code (PowerShell) e pelo `cmd`, acrescente `C:\msys64\ucrt64\bin` ao `PATH` do Windows:

1. Menu Iniciar → procure **"Editar as variáveis de ambiente do sistema"** → *Variáveis de Ambiente…*
2. Em *Variáveis do usuário*, selecione `Path` → *Editar* → *Novo* → `C:\msys64\ucrt64\bin` → OK em tudo.
3. **Feche e abra** o terminal (e o VS Code) e teste `g++ --version`.

Isso também coloca a `libmariadb.dll` no caminho, e é por isso que o `servidor.exe` consegue abrir fora do MSYS2.

## 2. Docker Desktop (banco de dados MariaDB)

O banco de dados roda dentro de um **container** Docker: uma "caixinha" isolada, com o MariaDB já configurado, que sobe com um único comando e é **igual em todos os computadores** (e no computador do professor, na correção). Não é preciso instalar o servidor MariaDB no Windows.

**Requisitos do computador:** Windows 10 (22H2) ou Windows 11, 64 bits, com a **virtualização ligada na BIOS/UEFI** (o Docker usa o WSL 2 do Windows). Para instalar pode ser preciso um usuário **administrador**; no laboratório, peça ao professor ou ao suporte.

1. Baixe o **Docker Desktop** em <https://www.docker.com/products/docker-desktop/> e instale mantendo marcada a opção de usar o **WSL 2**. Reinicie o computador se o instalador pedir.
2. Abra o **Docker Desktop**, aceite os termos e espere o ícone indicar que o *engine* está rodando (pode levar um minuto). Não é obrigatório criar conta para usar.
3. Em um terminal (PowerShell, `cmd` ou MSYS2), confira:

   ```bash
   docker --version
   docker compose version
   ```

4. **Baixe a imagem do banco agora** (é um download de algumas centenas de MB; é melhor fazer antes do dia 6, com a internet boa):

   ```bash
   docker pull mariadb:11.8
   ```

> **Por que instalamos a biblioteca do MariaDB no MSYS2 se o banco está no Docker?** O container traz o **servidor**. Para o nosso programa em C++ *conversar* com o servidor, precisamos do **cliente** (`mysql.h` e `libmariadb`), que fica no Windows, dentro do MSYS2. Eles se encontram pela porta 3306, aberta só para o seu computador.

**Lembretes do dia a dia:** o **Docker Desktop precisa estar aberto** para o banco funcionar. O container está configurado para voltar sozinho quando o Docker abre, e os dados ficam guardados mesmo se você desligar o computador. Os comandos do banco estão no README do starter kit (seção *O banco de dados no Docker*).

## 3. Teste final: rodar o starter kit

Dentro da cópia da equipe (já clonada), na pasta `projetos/starter-kit`:

1. **Suba o banco:**

   ```bash
   docker compose up -d --wait
   docker compose ps
   ```

   A primeira vez baixa a imagem (se você não fez o `docker pull`) e executa o `schema.sql` automaticamente. No `docker compose ps`, o serviço `db` deve aparecer como **healthy**.
2. **Compile** (escolha **um** dos dois jeitos):

   | Onde | Comando |
   |------|---------|
   | Terminal do VS Code / `cmd` / PowerShell, dentro de `projetos\starter-kit` | `build.bat` |
   | Terminal **MSYS2 UCRT64**, dentro de `projetos/starter-kit` | `./build.sh` |

   A primeira compilação demora (de 30 segundos a alguns minutos, dependendo do computador). É normal.
3. **Execute**, dentro da pasta `starter-kit`:

   ```bash
   build/servidor.exe
   ```

   A primeira linha deve ser `Banco OK: iteam@127.0.0.1:3306/projeto_iteam`.
4. Abra <http://localhost:8080>. Se aparecer a tela de **Recados** com o registro "Bem-vindo", **o ambiente está pronto** ✅.
5. Teste também <http://localhost:8080/api/saude/banco>: deve mostrar `{"banco":"ok"}`.
6. **Ao terminar o teste**, pare o servidor (Ctrl+C) e **remova o banco de teste**, para ele não ocupar a porta 3306 quando for trabalhar na pasta da equipe:

   ```bash
   docker compose down -v
   ```

Quem terminar primeiro ajuda os colegas da equipe. Só siga para o guia 02 quando **os quatro** estiverem com a tela funcionando.

## 4. Git: identifique-se

Cada pessoa configura o próprio nome e e-mail **uma vez**. É assim que o professor enxerga a sua contribuição:

```bash
git config --global user.name "Seu Nome"
git config --global user.email "o-mesmo-email-da-sua-conta-do-github@exemplo.com"
git config --global user.name    # confira
```

## 5. Plano B: se a biblioteca do MSYS2 não funcionar

Se o `pacman` não conseguir instalar o `libmariadbclient`, ou a compilação reclamar de `mysql.h`/`-lmariadb`, use o **MariaDB Connector/C** oficial:

1. Baixe o instalador **MSI de 64 bits** do *MariaDB Connector/C* em <https://mariadb.com/downloads/connectors/connectors-data-access/c-connector> (o `g++` do UCRT64 é 64 bits; a versão de 32 bits **não** serve).
2. Instale (por exemplo, em `C:\Program Files\MariaDB\MariaDB Connector C 64-bit`).
3. Antes de compilar, informe a pasta:

   ```bat
   set "MARIADB_DIR=C:\Program Files\MariaDB\MariaDB Connector C 64-bit"
   build.bat
   ```

4. Para **executar**, a `libmariadb.dll` precisa ser encontrada: copie-a da pasta `lib\mariadb` do Connector para `build\` (ao lado do `servidor.exe`).

Se ainda assim não funcionar, **chame o professor** com a mensagem de erro completa (print da tela inteira).

## 5.1. Plano B: sem Docker (banco instalado no Windows)

Se o Docker **não puder ser instalado** no computador (virtualização desligada e sem acesso à BIOS, falta de permissão…), qualquer servidor MariaDB/MySQL na porta 3306 serve (por exemplo, o XAMPP). Crie o banco e o usuário que o projeto espera e importe o `schema.sql`:

```sql
CREATE DATABASE IF NOT EXISTS projeto_iteam CHARACTER SET utf8mb4;
CREATE USER IF NOT EXISTS 'iteam'@'%' IDENTIFIED BY 'iteam123';
GRANT ALL ON projeto_iteam.* TO 'iteam'@'%';
```

Depois importe o `schema.sql` (no phpMyAdmin do XAMPP: aba **Importar**). Com isso o servidor em C++ funciona sem mudar nada. Avise o professor: **cada vez que o `schema.sql` mudar, é preciso importá-lo de novo à mão**, e o README da equipe deve dizer isso.

## 6. Problemas comuns

| Sintoma | O que fazer |
|---------|-------------|
| `g++` não é reconhecido | O `PATH` não tem `C:\msys64\ucrt64\bin`, ou o terminal foi aberto antes de alterá-lo. Feche e abra de novo. |
| `mysql.h: No such file or directory` | A biblioteca não foi instalada (passo 1.4) ou o `MARIADB_DIR` está errado (Plano B). |
| `cannot find -lmariadb` | Mesma causa. No MSYS2, `pacman -S mingw-w64-ucrt-x86_64-libmariadbclient`. |
| `undefined reference to 'WSAStartup'` (ou outros `__imp_...`) | Faltou `-lws2_32` na linha de comando. O `build.bat` e o `build.sh` já incluem; se compilar à mão, acrescente. |
| `servidor.exe` fecha logo ou diz que falta `libmariadb.dll` | A DLL não está no `PATH`. Rode pelo terminal do MSYS2 UCRT64, ou copie `libmariadb.dll` para `build\`. |
| `Can't connect to server on '127.0.0.1'` | O container do banco não está no ar: abra o Docker Desktop e rode `docker compose up -d --wait` na pasta do projeto (confira com `docker compose ps`). |
| `error during connect` / `Cannot connect to the Docker daemon` | O Docker Desktop está fechado ou ainda iniciando. Abra-o e espere o *engine* ficar pronto. |
| `Docker Desktop - WSL 2 ... virtualization` (o Docker não inicia) | Virtualização desligada na BIOS/UEFI, ou o WSL 2 não está instalado. Chame o professor/suporte; se não der, use o plano B (5.1). |
| `port is already allocated` ao subir o banco | A porta 3306 está ocupada (outro MySQL, ou o banco de outra pasta). Rode `docker compose down` na outra pasta, ou use `DB_PORTA=3307`. |
| `Access denied for user 'iteam'` | O banco foi criado com outra senha, ou o servidor está falando com outro MySQL na porta 3306. Zere o banco: `docker compose down -v` e `docker compose up -d --wait`. |
| `Unknown database 'projeto_iteam'` ou tabela inexistente | O `schema.sql` não foi aplicado (ele só roda quando o banco é criado). Zere o banco: `docker compose down -v` e `docker compose up -d --wait`. |
| Antivírus ou firewall bloqueia o `servidor.exe` ou o Docker | Permita o acesso em rede privada. O servidor só escuta em `127.0.0.1` (o próprio computador). |
