#ifndef SIMULADOR_COMANDOMELHORA_H
#define SIMULADOR_COMANDOMELHORA_H

#include "Comando.h"
#include <sstream>
#include <string>

class ComandoMelhora : public Comando {
    std::string coordenada;
    std::string resto;

public:
    ComandoMelhora(std::string coordenada, std::string resto = "") noexcept;
    ~ComandoMelhora() noexcept override = default;
    static Comando* criarDeStream(std::istringstream& iss);

    bool validar() const override;
    std::string getAjudaSimples() const override;
    std::string getAjuda() const override;
    std::string executar(Fabrica& fabrica, Simulador& simulador) override;
};

#endif // SIMULADOR_COMANDOMELHORA_H
