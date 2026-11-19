#ifndef SIMULADOR_COMANDO_H
#define SIMULADOR_COMANDO_H

#include <string>

class Fabrica;
class Simulador;

class Comando {
public:
    Comando() noexcept = default;
    virtual ~Comando() noexcept = default;

    virtual std::string executar(Fabrica& fabrica, Simulador& simulador) = 0;

    static Comando* criar(const std::string& linhaComando);
};

#endif // SIMULADOR_COMANDO_H
