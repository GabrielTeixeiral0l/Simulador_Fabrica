#ifndef SIMULADOR_COMANDOAJUDA_H
#define SIMULADOR_COMANDOAJUDA_H

#include "Comando.h"
#include <string>

class ComandoAjuda : public Comando {
private:
    std::string comandoAlvo;
    std::string resto;

public:
    ComandoAjuda(std::string comandoAlvo = "", std::string resto = "") noexcept;
    ~ComandoAjuda() noexcept override = default;

    bool validar() const override;
    std::string getAjuda() const override;
    std::string executar(Fabrica& fabrica, Simulador& simulador) override;
};

#endif // SIMULADOR_COMANDOAJUDA_H
