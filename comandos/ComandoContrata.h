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
    static Comando* criarDeStream(std::istringstream& iss);

    bool validar() const override;
    std::string getAjuda() const override;
    static std::string ajuda();
    std::string executar(Fabrica& fabrica, Simulador& simulador) override;
};

#endif // SIMULADOR_COMANDOCONTRATA_H
