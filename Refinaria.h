#ifndef SIMULADOR_REFINARIA_H
#define SIMULADOR_REFINARIA_H

#include "Maquina.h"

class Refinaria : public Maquina {
public:
    explicit Refinaria(Orientacao orientacao = Orientacao::Este) noexcept;
    ~Refinaria() noexcept override = default;

    char getSimbolo() const noexcept override;
    std::string getDescricao() const override;
    void atuar(Fabrica& fabrica, int linha, int coluna) override;
    Maquina* clone() const override;
};

#endif // SIMULADOR_REFINARIA_H
