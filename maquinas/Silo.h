#ifndef SIMULADOR_SILO_H
#define SIMULADOR_SILO_H

#include "Maquina.h"
#include "../Armazem.h"

class Silo : public Maquina {
    Armazem armazenamento;

public:
    explicit Silo(Orientacao orientacao = Orientacao::Este) noexcept;
    ~Silo() noexcept override;

    char getSimbolo() const noexcept override;
    std::string getDescricao() const override;
    bool aceitaItem(Item* item) override;
    void operar(Fabrica& fabrica, int linha, int coluna) override;
};

#endif // SIMULADOR_SILO_H
