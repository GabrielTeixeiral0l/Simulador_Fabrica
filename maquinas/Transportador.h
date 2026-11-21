#ifndef SIMULADOR_TRANSPORTADOR_H
#define SIMULADOR_TRANSPORTADOR_H

#include "Maquina.h"

class Item;

class Transportador : public Maquina {
    Item* itemArmazenado;

public:
    explicit Transportador(Orientacao orientacao = Orientacao::Este) noexcept;
    ~Transportador() noexcept override;

    char getSimbolo() const noexcept override;
    std::string getDescricao() const override;
    bool aceitaItem(Item* item) override;
    void operar(Fabrica& fabrica, int linha, int coluna) override;
};

#endif // SIMULADOR_TRANSPORTADOR_H
