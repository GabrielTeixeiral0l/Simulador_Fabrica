#ifndef SIMULADOR_LANCADOR_H
#define SIMULADOR_LANCADOR_H

#include "Maquina.h"

class Lancador : public Maquina {
public:
    explicit Lancador(Orientacao orientacao = Orientacao::Norte) noexcept;
    ~Lancador() noexcept override = default;

    char getSimbolo() const noexcept override;
    std::string getDescricao() const override;
    void atuar(Fabrica& fabrica, int linha, int coluna) override;
    Maquina* clone() const override;
};

#endif // SIMULADOR_LANCADOR_H
