#ifndef SIMULADOR_COMANDOESTADO_H
#define SIMULADOR_COMANDOESTADO_H

#include "Comando.h"
#include <string>

class ComandoEstado : public Comando {
    std::string resto;

public:
    explicit ComandoEstado(std::string resto = "") noexcept;
    ~ComandoEstado() noexcept override = default;
    static Comando* criarDeStream(std::istringstream& iss);

    bool validar() const override;
    std::string getAjuda() const override;
    static std::string ajuda();
    std::string executar(Fabrica& fabrica, Simulador& simulador) override;
};

#endif // SIMULADOR_COMANDOESTADO_H
