#ifndef SIMULADOR_COMANDOCOMPRA_H
#define SIMULADOR_COMANDOCOMPRA_H

#include "Comando.h"
#include <string>

class ComandoCompra : public Comando {
    std::string tipo;
    std::string coord;
    std::string dir;
    std::string resto;

public:
    ComandoCompra(std::string tipo, std::string coord, std::string dir = "c", std::string resto = "") noexcept;
    ~ComandoCompra() noexcept override = default;
    explicit ComandoCompra(bool);
    const char* getNome() const noexcept override;
    Comando* criarComArgs(std::istringstream& iss) const override;

    bool validar() const override;
    std::string getAjuda() const override;
    std::string executar(Fabrica& fabrica, Simulador& simulador) override;
};

#endif // SIMULADOR_COMANDOCOMPRA_H
