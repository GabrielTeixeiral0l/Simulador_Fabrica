#ifndef SIMULADOR_CRATERA_H
#define SIMULADOR_CRATERA_H

#include "Terreno.h"

class Cratera : public Terreno {
public:
    Cratera() noexcept = default;
    ~Cratera() noexcept override = default;

    char getSimbolo() const noexcept override;
    std::string getDescricao() const override;
    Terreno* clone() const override;
};

#endif // SIMULADOR_CRATERA_H
