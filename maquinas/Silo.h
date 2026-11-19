#ifndef SIMULADOR_SILO_H
#define SIMULADOR_SILO_H

#include "Maquina.h"

class Silo : public Maquina {
public:
    explicit Silo(Orientacao orientacao = Orientacao::Este) noexcept;
    ~Silo() noexcept override = default;

    char getSimbolo() const noexcept override;
    std::string getDescricao() const override;
    void atuar(Fabrica& fabrica, int linha, int coluna) override;
};

#endif // SIMULADOR_SILO_H
