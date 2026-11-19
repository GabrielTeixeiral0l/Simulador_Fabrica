#ifndef SIMULADOR_PERFURADORA_H
#define SIMULADOR_PERFURADORA_H

#include "Maquina.h"

class Perfuradora : public Maquina {
public:
    explicit Perfuradora(Orientacao orientacao = Orientacao::Norte) noexcept;
    ~Perfuradora() noexcept override = default;

    char getSimbolo() const noexcept override;
    std::string getDescricao() const override;
    void atuar(Fabrica& fabrica, int linha, int coluna) override;
};

#endif // SIMULADOR_PERFURADORA_H
