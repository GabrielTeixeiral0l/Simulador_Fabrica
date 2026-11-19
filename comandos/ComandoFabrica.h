#ifndef SIMULADOR_COMANDOFABRICA_H
#define SIMULADOR_COMANDOFABRICA_H

#include "Comando.h"
#include <string>

class ComandoFabrica : public Comando {
    std::string argLinhas;
    std::string argColunas;
    std::string resto;

public:
    ComandoFabrica(std::string argLinhas, std::string argColunas, std::string resto = "") noexcept;
    ~ComandoFabrica() noexcept override = default;

    bool validar() const override;
    std::string getAjuda() const override;
    std::string executar(Fabrica& fabrica, Simulador& simulador) override;
};

#endif // SIMULADOR_COMANDOFABRICA_H
