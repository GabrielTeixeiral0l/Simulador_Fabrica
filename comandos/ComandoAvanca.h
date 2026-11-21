#ifndef SIMULADOR_COMANDOAVANCA_H
#define SIMULADOR_COMANDOAVANCA_H

#include "Comando.h"
#include <string>

class ComandoAvanca : public Comando {
    std::string argN;
    std::string resto;

public:
    ComandoAvanca(std::string argN = "", std::string resto = "") noexcept;
    ~ComandoAvanca() noexcept override = default;
    static Comando* criarDeStream(std::istringstream& iss);

    bool validar() const override;
    std::string getAjudaSimples() const override;
    std::string getAjuda() const override;
    static std::string ajuda();
    std::string executar(Fabrica& fabrica, Simulador& simulador) override;
};

#endif // SIMULADOR_COMANDOAVANCA_H
