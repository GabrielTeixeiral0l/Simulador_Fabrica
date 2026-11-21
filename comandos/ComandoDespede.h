#ifndef SIMULADOR_COMANDODESPEDE_H
#define SIMULADOR_COMANDODESPEDE_H

#include "Comando.h"
#include <sstream>
#include <string>

class ComandoDespede : public Comando {
    std::string idEngenheiro;
    std::string resto;

public:
    ComandoDespede(std::string idEngenheiro, std::string resto = "") noexcept;
    ~ComandoDespede() noexcept override = default;
    static Comando* criarDeStream(std::istringstream& iss);

    bool validar() const override;
    std::string getAjudaSimples() const override;
    std::string getAjuda() const override;
    std::string executar(Fabrica& fabrica, Simulador& simulador) override;
};

#endif // SIMULADOR_COMANDODESPEDE_H
