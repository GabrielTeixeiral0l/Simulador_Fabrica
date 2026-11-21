#ifndef SIMULADOR_COMANDODESPEDE_H
#define SIMULADOR_COMANDODESPEDE_H

#include "Comando.h"
#include <string>

class ComandoDespede : public Comando {
    std::string argId;
    std::string resto;

public:
    ComandoDespede(std::string argId, std::string resto = "") noexcept;
    ~ComandoDespede() noexcept override = default;
    explicit ComandoDespede(bool);
    const char* getNome() const noexcept override;
    Comando* criarComArgs(std::istringstream& iss) const override;

    bool validar() const override;
    std::string getAjuda() const override;
    std::string executar(Fabrica& fabrica, Simulador& simulador) override;
};

#endif // SIMULADOR_COMANDODESPEDE_H
