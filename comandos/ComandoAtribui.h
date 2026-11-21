#ifndef SIMULADOR_COMANDOATRIBUI_H
#define SIMULADOR_COMANDOATRIBUI_H

#include "Comando.h"
#include <string>

class ComandoAtribui : public Comando {
    std::string argId;
    std::string coord;
    std::string resto;

public:
    ComandoAtribui(std::string argId, std::string coord, std::string resto = "") noexcept;
    ~ComandoAtribui() noexcept override = default;
    explicit ComandoAtribui(bool);
    const char* getNome() const noexcept override;
    Comando* criarComArgs(std::istringstream& iss) const override;

    bool validar() const override;
    std::string getAjuda() const override;
    std::string executar(Fabrica& fabrica, Simulador& simulador) override;
};

#endif // SIMULADOR_COMANDOATRIBUI_H
