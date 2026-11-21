#ifndef SIMULADOR_COMANDOEXECUTA_H
#define SIMULADOR_COMANDOEXECUTA_H

#include "Comando.h"
#include <string>

class ComandoExecuta : public Comando {
    std::string ficheiro;
    std::string resto;

public:
    ComandoExecuta(std::string ficheiro, std::string resto = "") noexcept;
    ~ComandoExecuta() noexcept override = default;
    explicit ComandoExecuta(bool);
    const char* getNome() const noexcept override;
    Comando* criarComArgs(std::istringstream& iss) const override;

    bool validar() const override;
    std::string getAjuda() const override;
    std::string executar(Fabrica& fabrica, Simulador& simulador) override;
    bool requerFabrica() const noexcept override { return false; }
};

#endif // SIMULADOR_COMANDOEXECUTA_H
