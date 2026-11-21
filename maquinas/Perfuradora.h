#ifndef SIMULADOR_PERFURADORA_H
#define SIMULADOR_PERFURADORA_H

#include "Maquina.h"

class Item;

class Perfuradora : public Maquina {
    Item* itemArmazenado;
    int instantesPassados;

public:
    explicit Perfuradora(Orientacao orientacao = Orientacao::Norte) noexcept;
    ~Perfuradora() noexcept override;

    char getSimbolo() const noexcept override;
    std::string getDescricao() const override;
    void operar(Fabrica& fabrica, int linha, int coluna) override;
};

#endif // SIMULADOR_PERFURADORA_H
