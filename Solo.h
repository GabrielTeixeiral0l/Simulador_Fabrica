#ifndef SIMULADOR_SOLO_H
#define SIMULADOR_SOLO_H

#include "Terreno.h"

class Solo : public Terreno {
public:
    Solo() noexcept = default;
    ~Solo() noexcept override = default;

    char getSimbolo() const noexcept override;
    std::string getDescricao() const override;
    bool podeConstruir() const noexcept override;
    Terreno* clone() const override;
};

#endif // SIMULADOR_SOLO_H
