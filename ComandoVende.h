#ifndef SIMULADOR_COMANDOVENDE_H
#define SIMULADOR_COMANDOVENDE_H

#include "Comando.h"
#include <string>

class ComandoVende : public Comando {
    std::string coord;
    std::string resto;

public:
    ComandoVende(std::string coord, std::string resto = "") noexcept;
    ~ComandoVende() noexcept override = default;

    bool validar() const override;
    std::string getAjuda() const override;
    std::string executar(Fabrica& fabrica, Simulador& simulador) override;
};

#endif // SIMULADOR_COMANDOVENDE_H
