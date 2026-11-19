#ifndef SIMULADOR_COMANDOEXEC_H
#define SIMULADOR_COMANDOEXEC_H

#include "Comando.h"
#include <string>

class ComandoExec : public Comando {
private:
    std::string nomeFicheiro;

public:
    explicit ComandoExec(std::string nomeFicheiro) noexcept;
    ~ComandoExec() noexcept override = default;

    std::string executar(Fabrica& fabrica, Simulador& simulador) override;
};

#endif // SIMULADOR_COMANDOEXEC_H
