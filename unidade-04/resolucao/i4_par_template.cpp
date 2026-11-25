// Atividade I4 - Classe template Par<A, B>
#include <iostream>
#include <string>

template <typename A, typename B>
class Par {
public:
    Par(const A& primeiro, const B& segundo) : primeiro_(primeiro), segundo_(segundo) {}
    const A& primeiro() const { return primeiro_; }
    const B& segundo() const { return segundo_; }
    Par<B, A> inverter() const { return Par<B, A>(segundo_, primeiro_); }

private:
    A primeiro_;
    B segundo_;
};

template <typename A, typename B>
void mostrar(const Par<A, B>& par) {
    std::cout << "Par(" << par.primeiro() << ", " << par.segundo() << ")\n";
}

// O main ja esta pronto: linhas descomentadas.
int main() {
    Par<int, std::string> a(7, "sete");
    mostrar(a);
    mostrar(a.inverter());

    std::cout << std::boolalpha;
    Par<double, bool> b(2.5, true);
    mostrar(b);
    return 0;
}