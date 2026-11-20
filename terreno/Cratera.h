#ifndef SIMULADOR_CRATERA_H
#define SIMULADOR_CRATERA_H

#include "Terreno.h"

class Cratera : public Terreno {
    char getSimboloTerreno() const noexcept override;

public:
    Cratera() noexcept = default;
    ~Cratera() noexcept override = default;

    std::string getDescricao() const override;
};

#endif // SIMULADOR_CRATERA_H
