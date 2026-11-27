@echo off
rem Sobe a API (precisa das DLLs do MSYS2 no PATH: MariaDB, OpenSSL, libstdc++).
rem Uso: run.bat   ou   run.bat --redefinir-senha email@exemplo.com
setlocal
cd /d "%~dp0"
if "%MSYS2%"=="" set "MSYS2=C:\msys64"
set "PATH=%MSYS2%\ucrt64\bin;%PATH%"
"%~dp0clinica-pet.exe" %*
