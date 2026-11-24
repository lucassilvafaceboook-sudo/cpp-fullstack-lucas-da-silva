#!/usr/bin/env bash
# build.sh - Compila o servidor (g++ / MSYS2 UCRT64 ou Linux).
#
# Uso:   ./build.sh           compila só o que mudou
#        ./build.sh limpar    apaga a pasta build/ e compila tudo de novo
#        ./build.sh rodar     compila e já executa o servidor
#
# Onde está a biblioteca do MariaDB? Este script tenta, nesta ordem:
#   1) mariadb_config   2) pkg-config libmariadb   3) variável MARIADB_DIR (pasta do Connector/C)
#   4) caminhos padrão do compilador (-lmariadb)
set -euo pipefail
cd "$(dirname "$0")"

SAIDA="build"
EXE="$SAIDA/servidor"
FLAGS=(-std=c++17 -O1 -Wall -Wextra -Ilibs -Isrc)
LIGACAO=()

case "$(uname -s)" in
  MINGW*|MSYS*|CYGWIN*)
    EXE="$EXE.exe"
    # httplib no Windows: versao minima do Windows, sockets e threads.
    FLAGS+=(-D_WIN32_WINNT=0x0A00)
    LIGACAO+=(-lws2_32 -pthread)
    ;;
  *)
    LIGACAO+=(-pthread)
    ;;
esac

if [[ "${1:-}" == "limpar" ]]; then
  rm -rf "$SAIDA"
  shift
fi

# --- localizar a biblioteca do MariaDB ---------------------------------------------------------------
if command -v mariadb_config >/dev/null 2>&1; then
  read -r -a MARIA_INC <<<"$(mariadb_config --include)"
  read -r -a MARIA_LIB <<<"$(mariadb_config --libs)"
elif command -v pkg-config >/dev/null 2>&1 && pkg-config --exists libmariadb; then
  read -r -a MARIA_INC <<<"$(pkg-config --cflags libmariadb)"
  read -r -a MARIA_LIB <<<"$(pkg-config --libs libmariadb)"
elif [[ -n "${MARIADB_DIR:-}" ]]; then
  # Layout do MariaDB Connector/C instalado pelo .msi: include/mariadb e lib/mariadb
  MARIA_INC=(-I"$MARIADB_DIR/include" -I"$MARIADB_DIR/include/mariadb")
  MARIA_LIB=(-L"$MARIADB_DIR/lib" -L"$MARIADB_DIR/lib/mariadb" -lmariadb)
elif printf '#if __has_include(<mariadb/mysql.h>)\n#elif __has_include(<mysql.h>)\n#else\n#error sem cabecalho\n#endif\nint main(){}\n' \
     | g++ -x c++ -fsyntax-only - >/dev/null 2>&1; then
  # Cabecalhos e biblioteca ja estao nos caminhos padrao do compilador (caso tipico do MSYS2 UCRT64).
  MARIA_INC=()
  MARIA_LIB=(-lmariadb)
else
  echo "ERRO: biblioteca do MariaDB (libmariadb) nao encontrada." >&2
  echo "  - MSYS2:  pacman -S mingw-w64-ucrt-x86_64-libmariadbclient" >&2
  echo "  - Ou defina MARIADB_DIR com a pasta do MariaDB Connector/C. Veja projetos/guia/01-preparar-ambiente.md" >&2
  exit 1
fi

mkdir -p "$SAIDA/obj"

# --- compilar o que mudou ------------------------------------------------------------------------------
# Um .o e refeito se o seu .cpp OU qualquer cabecalho de src/ for mais novo.
OBJETOS=()
PRECISA_LIGAR=0
[[ -f "$EXE" ]] || PRECISA_LIGAR=1
CABECALHO_NOVO=0
for h in src/*.hpp; do
  [[ -n "$(find "$h" -newer "$EXE" 2>/dev/null)" ]] && CABECALHO_NOVO=1
done

for fonte in src/*.cpp; do
  obj="$SAIDA/obj/$(basename "${fonte%.cpp}").o"
  OBJETOS+=("$obj")
  if [[ ! -f "$obj" || "$fonte" -nt "$obj" || "$CABECALHO_NOVO" == 1 ]]; then
    echo "Compilando $fonte ..."
    g++ "${FLAGS[@]}" "${MARIA_INC[@]}" -c "$fonte" -o "$obj"
    PRECISA_LIGAR=1
  fi
done

if [[ "$PRECISA_LIGAR" == 1 ]]; then
  echo "Ligando $EXE ..."
  g++ "${OBJETOS[@]}" -o "$EXE" "${MARIA_LIB[@]}" "${LIGACAO[@]}"
fi
echo "Pronto: $EXE"

if [[ "${1:-}" == "rodar" ]]; then
  exec "./$EXE"
fi
