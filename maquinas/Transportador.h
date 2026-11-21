#ifndef SIMULADOR_TRANSPORTADOR_H
#define SIMULADOR_TRANSPORTADOR_H

#include "Maquina.h"

class Transportador : public Maquina {
public:
    explicit Transportador(Orientacao orientacao = Orientacao::Este) noexcept;
    ~Transportador() noexcept override = default;

    char getSimbolo() const noexcept override;
    std::string getDescricao() const override;
    void operar(Fabrica& fabrica, int linha, int coluna) override;
};

#endif // SIMULADOR_TRANSPORTADOR_H
