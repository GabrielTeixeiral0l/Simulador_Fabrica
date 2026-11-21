#ifndef SIMULADOR_COMANDOEXECUTA_H
#define SIMULADOR_COMANDOEXECUTA_H

#include "Comando.h"
#include <sstream>
#include <string>

class ComandoExecuta : public Comando {
    std::string nomeFicheiro;
    std::string resto;

public:
    ComandoExecuta(std::string nomeFicheiro, std::string resto = "") noexcept;
    ~ComandoExecuta() noexcept override = default;
    static Comando* criarDeStream(std::istringstream& iss);

    bool validar() const override;
    std::string getAjudaSimples() const override;
    std::string getAjuda() const override;
    std::string executar(Fabrica& fabrica, Simulador& simulador) override;
    bool requerFabrica() const noexcept override;
};

#endif // SIMULADOR_COMANDOEXECUTA_H
