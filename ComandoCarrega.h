#ifndef SIMULADOR_COMANDOCARREGA_H
#define SIMULADOR_COMANDOCARREGA_H

#include "Comando.h"
#include <string>

class ComandoCarrega : public Comando {
private:
    std::string nomeFicheiro;

public:
    explicit ComandoCarrega(std::string nomeFicheiro) noexcept;
    ~ComandoCarrega() noexcept override = default;

    std::string executar(Fabrica& fabrica, Simulador& simulador) override;
};

#endif // SIMULADOR_COMANDOCARREGA_H
