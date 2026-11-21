#ifndef SIMULADOR_COMANDOLPOSICAO_H
#define SIMULADOR_COMANDOLPOSICAO_H

#include "Comando.h"
#include <sstream>
#include <string>

class ComandoLPosicao : public Comando {
    std::string coordenada;
    std::string raio;
    std::string resto;

public:
    ComandoLPosicao(std::string coordenada, std::string raio = "", std::string resto = "") noexcept;
    ~ComandoLPosicao() noexcept override = default;
    static Comando* criarDeStream(std::istringstream& iss);

    bool validar() const override;
    std::string getAjudaSimples() const override;
    std::string getAjuda() const override;
    std::string executar(Fabrica& fabrica, Simulador& simulador) override;
};

#endif // SIMULADOR_COMANDOLPOSICAO_H
