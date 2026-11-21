#ifndef SIMULADOR_COMANDOAJUDA_H
#define SIMULADOR_COMANDOAJUDA_H

#include "Comando.h"
#include <string>

class ComandoAjuda : public Comando {
    std::string comandoAlvo;
    std::string resto;

public:
    ComandoAjuda(std::string comandoAlvo = "", std::string resto = "") noexcept;
    ~ComandoAjuda() noexcept override = default;
    static Comando* criarDeStream(std::istringstream& iss);

    bool validar() const override;
    std::string getAjuda() const override;
    static std::string ajuda();
    std::string executar(Fabrica& fabrica, Simulador& simulador) override;
    bool requerFabrica() const noexcept override { return false; }
};

#endif // SIMULADOR_COMANDOAJUDA_H
