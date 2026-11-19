#ifndef SIMULADOR_COMANDORODA_H
#define SIMULADOR_COMANDORODA_H

#include "Comando.h"
#include <string>

class ComandoRoda : public Comando {
private:
    std::string coord;
    std::string dir;
    std::string resto;

public:
    ComandoRoda(std::string coord, std::string dir = "", std::string resto = "") noexcept;
    ~ComandoRoda() noexcept override = default;

    bool validar() const override;
    std::string getAjuda() const override;
    std::string executar(Fabrica& fabrica, Simulador& simulador) override;
};

#endif // SIMULADOR_COMANDORODA_H
