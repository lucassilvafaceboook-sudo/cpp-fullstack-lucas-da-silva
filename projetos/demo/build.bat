@echo off
rem ----------------------------------------------------------------------------------------------
rem  build.bat - Compila o servidor no Windows (precisa do g++ no PATH; veja guia/01-preparar-ambiente.md)
rem
rem  Uso:   build.bat           compila tudo
rem         build.bat rodar     compila e executa o servidor
rem
rem  Se a biblioteca do MariaDB (MariaDB Connector/C) NAO estiver nos caminhos padrao do compilador,
rem  defina MARIADB_DIR com a pasta onde ela foi instalada, por exemplo:
rem      set MARIADB_DIR=C:\Program Files\MariaDB\MariaDB Connector C 64-bit
rem
rem  Ao criar novos arquivos .cpp em src\, acrescente-os na lista FONTES abaixo.
rem ----------------------------------------------------------------------------------------------
setlocal
cd /d "%~dp0"

set "FONTES=src\main.cpp src\banco.cpp src\projeto_repositorio.cpp src\rotas_projetos.cpp src\tarefa_repositorio.cpp src\rotas_tarefas.cpp"
set "INC=-Ilibs -Isrc"
set "LIB=-lmariadb"
if defined MARIADB_DIR set "INC=%INC% -I"%MARIADB_DIR%\include" -I"%MARIADB_DIR%\include\mariadb""
if defined MARIADB_DIR set "LIB=-L"%MARIADB_DIR%\lib" -L"%MARIADB_DIR%\lib\mariadb" -lmariadb"

if not exist build mkdir build

echo Compilando (a primeira vez demora um pouco)...
g++ -std=c++17 -O1 -Wall -Wextra -D_WIN32_WINNT=0x0A00 %INC% %FONTES% -o build\servidor.exe %LIB% -lws2_32 -pthread
if errorlevel 1 (
    echo.
    echo ERRO na compilacao. Leia as mensagens acima, de cima para baixo: o primeiro erro e o mais importante.
    exit /b 1
)

echo Pronto: build\servidor.exe
if /i "%~1"=="rodar" build\servidor.exe
exit /b 0
