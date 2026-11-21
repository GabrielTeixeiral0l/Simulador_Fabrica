#ifndef SIMULADOR_COMANDOLPOSICAO_H
#define SIMULADOR_COMANDOLPOSICAO_H

#include "Comando.h"
#include <string>

class ComandoLPosicao : public Comando {
    std::string coord;
    std::string argRaio;
    std::string resto;

public:
    ComandoLPosicao(std::string coord, std::string argRaio = "", std::string resto = "") noexcept;
    ~ComandoLPosicao() noexcept override = default;
    static Comando* criarDeStream(std::istringstream& iss);

    bool validar() const override;
    std::string getAjuda() const override;
    static std::string ajuda();
    std::string executar(Fabrica& fabrica, Simulador& simulador) override;
};

#endif // SIMULADOR_COMANDOLPOSICAO_H
