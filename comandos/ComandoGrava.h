#ifndef SIMULADOR_COMANDOGRAVA_H
#define SIMULADOR_COMANDOGRAVA_H

#include "Comando.h"
#include <string>

class ComandoGrava : public Comando {
    std::string nome;
    std::string resto;

public:
    ComandoGrava(std::string nome, std::string resto = "") noexcept;
    ~ComandoGrava() noexcept override = default;
    static Comando* criarDeStream(std::istringstream& iss);

    bool validar() const override;
    std::string getAjudaSimples() const override;
    std::string getAjuda() const override;
    static std::string ajuda();
    std::string executar(Fabrica& fabrica, Simulador& simulador) override;
};

#endif // SIMULADOR_COMANDOGRAVA_H
