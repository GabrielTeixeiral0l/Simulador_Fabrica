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
    static Comando* criarDeStream(std::istringstream& iss);

    bool validar() const override;
    std::string getAjuda() const override;
    static std::string ajuda();
    std::string executar(Fabrica& fabrica, Simulador& simulador) override;
    bool requerFabrica() const noexcept override { return false; }
};

#endif // SIMULADOR_COMANDOEXECUTA_H
