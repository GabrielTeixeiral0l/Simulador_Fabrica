#ifndef SIMULADOR_COMANDOCONTRATA_H
#define SIMULADOR_COMANDOCONTRATA_H

#include "Comando.h"
#include <string>

class ComandoContrata : public Comando {
    std::string nome;
    std::string resto;

public:
    ComandoContrata(std::string nome, std::string resto = "") noexcept;
    ~ComandoContrata() noexcept override = default;
    explicit ComandoContrata(bool);
    const char* getNome() const noexcept override;
    Comando* criarComArgs(std::istringstream& iss) const override;

    bool validar() const override;
    std::string getAjuda() const override;
    std::string executar(Fabrica& fabrica, Simulador& simulador) override;
};

#endif // SIMULADOR_COMANDOCONTRATA_H
