/* Atividade F1 - Primeiro programa compilado com avisos
    
 TODO: registre aqui a saída de `g++ --version`
    "g++.exe (Rev4, Built by MSYS2 project) 16.2.0"

 TODO: registre aqui o comando de compilação que você usou
    "g++ -std=c++17 -Wall -Wextra f1_primeiro_programa.cpp -o f1.exe
    .\f1.exe"
    
 TODO: explique em uma ou duas frases a diferença entre editor, compilador e IDE
    O editor serve apenas para escrever e modificar o codigo-fonte, enquanto o
    compilador traduz esse codigo para um executavel que o computador entende.
    Ja a IDE reune editor, compilador, depurador e outras ferramentas de apoio
    em um unico ambiente integrado.
    */

#include <iostream>

int main() {
    std::cout << "Ola, mundo!\n";
    std::cout << "Lucas da Silva Macuxi\n";
    std::cout << "C++: eficiencia com abstracao.\n";

    return 0;
}
