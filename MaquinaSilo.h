#ifndef SIMULADOR_MAQUINASILO_H
#define SIMULADOR_MAQUINASILO_H

#include "Maquina.h"

class MaquinaSilo : public Maquina {
public:
    explicit MaquinaSilo(Orientacao orientacao = Orientacao::Este) noexcept;
    ~MaquinaSilo() noexcept override = default;

    char getSimbolo() const noexcept override;
    std::string getDescricao() const override;
    void atuar(Fabrica& fabrica, int linha, int coluna) override;
};

#endif // SIMULADOR_MAQUINASILO_H
