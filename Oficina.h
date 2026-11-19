#ifndef SIMULADOR_OFICINA_H
#define SIMULADOR_OFICINA_H

#include "Maquina.h"

class Oficina : public Maquina {
public:
    explicit Oficina(Orientacao orientacao = Orientacao::Este) noexcept;
    ~Oficina() noexcept override = default;

    char getSimbolo() const noexcept override;
    std::string getDescricao() const override;
    void atuar(Fabrica& fabrica, int linha, int coluna) override;
    Maquina* clone() const override;
};

#endif // SIMULADOR_OFICINA_H
