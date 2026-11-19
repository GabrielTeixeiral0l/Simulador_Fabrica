#ifndef SIMULADOR_COMANDOEXECUTA_H
#define SIMULADOR_COMANDOEXECUTA_H

#include "Comando.h"
#include <string>

class ComandoExecuta : public Comando {
private:
    std::string ficheiro;
    std::string resto;

public:
    ComandoExecuta(std::string ficheiro, std::string resto = "") noexcept;
    ~ComandoExecuta() noexcept override = default;

    bool validar() const override;
    std::string getAjuda() const override;
    std::string executar(Fabrica& fabrica, Simulador& simulador) override;
};

#endif // SIMULADOR_COMANDOEXECUTA_H
