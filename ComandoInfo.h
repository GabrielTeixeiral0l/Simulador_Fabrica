#ifndef SIMULADOR_COMANDOINFO_H
#define SIMULADOR_COMANDOINFO_H

#include "Comando.h"
#include <string>

class ComandoInfo : public Comando {
private:
    std::string coordenadas;

public:
    explicit ComandoInfo(std::string coordenadas) noexcept;
    ~ComandoInfo() noexcept override = default;

    std::string executar(Fabrica& fabrica, Simulador& simulador) override;
};

#endif // SIMULADOR_COMANDOINFO_H
