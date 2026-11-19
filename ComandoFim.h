#ifndef SIMULADOR_COMANDOFIM_H
#define SIMULADOR_COMANDOFIM_H

#include "Comando.h"
#include <string>

class ComandoFim : public Comando {
private:
    std::string resto;

public:
    explicit ComandoFim(std::string resto = "") noexcept;
    ~ComandoFim() noexcept override = default;

    bool validar() const override;
    std::string getAjuda() const override;
    std::string executar(Fabrica& fabrica, Simulador& simulador) override;
};

#endif // SIMULADOR_COMANDOFIM_H
