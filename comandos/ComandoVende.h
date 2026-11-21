#ifndef SIMULADOR_COMANDOVENDE_H
#define SIMULADOR_COMANDOVENDE_H

#include "Comando.h"
#include <sstream>
#include <string>

class ComandoVende : public Comando {
    std::string coordenada;
    std::string resto;

public:
    ComandoVende(std::string coordenada, std::string resto = "") noexcept;
    ~ComandoVende() noexcept override = default;
    static Comando* criarDeStream(std::istringstream& iss);

    bool validar() const override;
    std::string getAjudaSimples() const override;
    std::string getAjuda() const override;
    std::string executar(Fabrica& fabrica, Simulador& simulador) override;
};

#endif // SIMULADOR_COMANDOVENDE_H
