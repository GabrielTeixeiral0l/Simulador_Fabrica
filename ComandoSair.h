#ifndef SIMULADOR_COMANDOSAIR_H
#define SIMULADOR_COMANDOSAIR_H

#include "Comando.h"

class ComandoSair : public Comando {
public:
    ComandoSair() noexcept = default;
    ~ComandoSair() noexcept override = default;

    std::string executar(Fabrica& fabrica, Simulador& simulador) override;
};

#endif // SIMULADOR_COMANDOSAIR_H
