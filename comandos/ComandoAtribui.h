#ifndef SIMULADOR_COMANDOATRIBUI_H
#define SIMULADOR_COMANDOATRIBUI_H

#include "Comando.h"
#include <sstream>
#include <string>

class ComandoAtribui : public Comando {
    std::string idEngenheiro;
    std::string coordenada;
    std::string resto;

public:
    ComandoAtribui(std::string idEngenheiro, std::string coordenada, std::string resto = "") noexcept;
    ~ComandoAtribui() noexcept override = default;
    static Comando* criarDeStream(std::istringstream& iss);

    bool validar() const override;
    std::string getAjudaSimples() const override;
    std::string getAjuda() const override;
    std::string executar(Fabrica& fabrica, Simulador& simulador) override;
};

#endif // SIMULADOR_COMANDOATRIBUI_H
