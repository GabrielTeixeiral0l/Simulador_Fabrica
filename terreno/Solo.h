#ifndef SIMULADOR_SOLO_H
#define SIMULADOR_SOLO_H

#include "Terreno.h"

class Solo : public Terreno {
    char getSimboloTerreno() const noexcept override;

public:
    Solo() noexcept = default;
    ~Solo() noexcept override = default;

    std::string getDescricao() const override;
    bool podeConstruir() const noexcept override;
};

#endif // SIMULADOR_SOLO_H
