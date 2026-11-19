#ifndef SIMULADOR_COMANDOCRIA_H
#define SIMULADOR_COMANDOCRIA_H

#include "Comando.h"

class ComandoCria : public Comando {
private:
    int linhas;
    int colunas;

public:
    ComandoCria(int linhas, int colunas) noexcept;
    ~ComandoCria() noexcept override = default;

    std::string executar(Fabrica& fabrica, Simulador& simulador) override;
};

#endif // SIMULADOR_COMANDOCRIA_H
