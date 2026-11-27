@echo off
rem Compila a API no Windows usando o g++ do MSYS2 (UCRT64).
rem Pré-requisitos (no terminal "MSYS2 UCRT64"):
rem   pacman -S mingw-w64-ucrt-x86_64-gcc mingw-w64-ucrt-x86_64-libmariadbclient mingw-w64-ucrt-x86_64-openssl
setlocal
cd /d "%~dp0"
if "%MSYS2%"=="" set "MSYS2=C:\msys64"
set "PATH=%MSYS2%\ucrt64\bin;%PATH%"

echo Compilando...
g++ -std=c++17 -Wall -Wextra -O2 -Isrc -isystem libs -I"%MSYS2%\ucrt64\include\mariadb" ^
  src\*.cpp -lmariadb -lcrypto -lws2_32 -lcrypt32 -o clinica-pet.exe
if errorlevel 1 (
  echo Falhou a compilacao.
  exit /b 1
)
echo Pronto: clinica-pet.exe   ^(rode com run.bat^)
