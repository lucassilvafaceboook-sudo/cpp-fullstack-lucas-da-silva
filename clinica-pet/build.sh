#!/usr/bin/env bash
# Compila a API. Uso: ./build.sh   (gera ./clinica-pet ou clinica-pet.exe)
# Linux (Debian/Ubuntu): sudo apt install g++ libmariadb-dev libssl-dev
# Windows (MSYS2 UCRT64): pacman -S mingw-w64-ucrt-x86_64-gcc mingw-w64-ucrt-x86_64-libmariadbclient mingw-w64-ucrt-x86_64-openssl
#
# Cada .cpp vira um .o em build/ e só é recompilado quando ele (ou um .hpp) muda.
set -e
cd "$(dirname "$0")"

# Onde estão os cabeçalhos e a biblioteca do MariaDB
if command -v mariadb_config >/dev/null 2>&1; then
  MARIADB_INC=$(mariadb_config --include)
  MARIADB_LIB=$(mariadb_config --libs)
else
  MARIADB_INC="-I/usr/include/mariadb"
  MARIADB_LIB="-lmariadb"
fi

EXTRA=""
SAIDA="clinica-pet"
case "$(uname -s)" in
  MINGW*|MSYS*|CYGWIN*)
    EXTRA="-lws2_32 -lcrypt32"; SAIDA="clinica-pet.exe"
    # No Git Bash, os caminhos "/ucrt64/..." do MSYS2 ficam em C:/msys64/ucrt64
    if [ ! -d /ucrt64 ] && [ -d /c/msys64/ucrt64 ]; then
      MARIADB_INC=${MARIADB_INC//\/ucrt64/\/c\/msys64\/ucrt64}
      MARIADB_LIB=${MARIADB_LIB//\/ucrt64/\/c\/msys64\/ucrt64}
    fi ;;
  *) EXTRA="-pthread" ;;
esac

FLAGS="-std=c++17 -Wall -Wextra -O2 -Isrc -isystem libs $MARIADB_INC"
# -isystem libs: avisos das bibliotecas de terceiros não contam; os do nosso código sim (-Wall -Wextra)

mkdir -p build
HEADERS=$(ls src/*.hpp)
pids=()
for cpp in src/*.cpp; do
  obj="build/$(basename "${cpp%.cpp}").o"
  precisa=0
  [ ! -f "$obj" ] || [ "$cpp" -nt "$obj" ] && precisa=1
  for h in $HEADERS; do [ "$h" -nt "$obj" ] && precisa=1; done
  if [ "$precisa" = 1 ]; then
    echo "Compilando $cpp"
    g++ $FLAGS -c "$cpp" -o "$obj" &
    pids+=($!)
  fi
done
falhou=0
for p in "${pids[@]}"; do wait "$p" || falhou=1; done
[ "$falhou" = 0 ] || { echo "Falhou a compilação."; exit 1; }

echo "Ligando $SAIDA"
g++ build/*.o $MARIADB_LIB -lcrypto $EXTRA -o "$SAIDA"
echo "Pronto: ./$SAIDA"
