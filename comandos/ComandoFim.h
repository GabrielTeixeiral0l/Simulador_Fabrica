#ifndef SIMULADOR_COMANDOFIM_H
#define SIMULADOR_COMANDOFIM_H

#include "Comando.h"
#include <string>

class ComandoFim : public Comando {
    std::string resto;

public:
    explicit ComandoFim(std::string resto = "") noexcept;
    ~ComandoFim() noexcept override = default;
    static Comando* criarDeStream(std::istringstream& iss);

    bool validar() const override;
    std::string getAjudaSimples() const override;
    std::string getAjuda() const override;
    static std::string ajuda();
    std::string executar(Fabrica& fabrica, Simulador& simulador) override;
    bool requerFabrica() const noexcept override { return false; }
};

#endif // SIMULADOR_COMANDOFIM_H
