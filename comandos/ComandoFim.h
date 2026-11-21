#ifndef SIMULADOR_COMANDOFIM_H
#define SIMULADOR_COMANDOFIM_H

#include "Comando.h"
#include <string>

class ComandoFim : public Comando {
    std::string resto;

public:
    explicit ComandoFim(std::string resto = "") noexcept;
    ~ComandoFim() noexcept override = default;
    explicit ComandoFim(bool);
    const char* getNome() const noexcept override;
    Comando* criarComArgs(std::istringstream& iss) const override;

    bool validar() const override;
    std::string getAjuda() const override;
    std::string executar(Fabrica& fabrica, Simulador& simulador) override;
    bool requerFabrica() const noexcept override { return false; }
};

#endif // SIMULADOR_COMANDOFIM_H
