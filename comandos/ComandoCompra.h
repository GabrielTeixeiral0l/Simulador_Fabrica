#ifndef SIMULADOR_COMANDOCOMPRA_H
#define SIMULADOR_COMANDOCOMPRA_H

#include "Comando.h"
#include <sstream>
#include <string>

class ComandoCompra : public Comando {
    std::string tipo;
    std::string coordenada;
    std::string direcao;
    std::string resto;

public:
    ComandoCompra(std::string tipo, std::string coordenada, std::string direcao = "c", std::string resto = "") noexcept;
    ~ComandoCompra() noexcept override = default;
    static Comando* criarDeStream(std::istringstream& iss);

    bool validar() const override;
    std::string getAjudaSimples() const override;
    std::string getAjuda() const override;
    std::string executar(Fabrica& fabrica, Simulador& simulador) override;
};

#endif // SIMULADOR_COMANDOCOMPRA_H
