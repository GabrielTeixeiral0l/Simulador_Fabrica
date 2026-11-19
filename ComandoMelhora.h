#ifndef SIMULADOR_COMANDOMELHORA_H
#define SIMULADOR_COMANDOMELHORA_H

#include "Comando.h"
#include <string>

class ComandoMelhora : public Comando {
private:
    std::string coord;
    std::string resto;

public:
    ComandoMelhora(std::string coord, std::string resto = "") noexcept;
    ~ComandoMelhora() noexcept override = default;

    bool validar() const override;
    std::string getAjuda() const override;
    std::string executar(Fabrica& fabrica, Simulador& simulador) override;
};

#endif // SIMULADOR_COMANDOMELHORA_H
