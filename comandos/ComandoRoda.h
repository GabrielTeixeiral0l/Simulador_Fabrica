#ifndef SIMULADOR_COMANDORODA_H
#define SIMULADOR_COMANDORODA_H

#include "Comando.h"
#include <sstream>
#include <string>

class ComandoRoda : public Comando {
    std::string coordenada;
    std::string direcao;
    std::string resto;

public:
    ComandoRoda(std::string coordenada, std::string direcao = "", std::string resto = "") noexcept;
    ~ComandoRoda() noexcept override = default;
    static Comando* criarDeStream(std::istringstream& iss);

    bool validar() const override;
    std::string getAjudaSimples() const override;
    std::string getAjuda() const override;
    std::string executar(Fabrica& fabrica, Simulador& simulador) override;
};

#endif // SIMULADOR_COMANDORODA_H
