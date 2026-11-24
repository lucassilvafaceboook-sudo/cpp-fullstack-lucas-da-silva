// Atividade I4 - Classe template Par<A, B>
#include <iostream>
#include <string>

// TODO: template <typename A, typename B> class Par
//       (primeiro_, segundo_, construtor, primeiro(), segundo(), inverter())
template <typename A, typename B>
class Par {
public:
    Par(const A& primeiro, const B& segundo) : primeiro_(primeiro), segundo_(segundo) {}
    const A& primeiro() const { return primeiro_; }
    const B& segundo() const { return segundo_; }
    // TODO: Par<B, A> inverter() const

private:
    A primeiro_;
    B segundo_;
};

// TODO: template <typename A, typename B> void mostrar(const Par<A, B>& par)

// O main já está pronto: descomente as linhas quando as peças estiverem prontas.
int main() {
    Par<int, std::string> a(7, "sete");
    // mostrar(a);
    // mostrar(a.inverter());

    std::cout << std::boolalpha;
    Par<double, bool> b(2.5, true);
    // mostrar(b);
    (void)a;
    (void)b;
    return 0;
}
