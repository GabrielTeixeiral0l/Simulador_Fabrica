#ifndef SIMULADOR_SILICIOPURO_H
#define SIMULADOR_SILICIOPURO_H

#include "ProdutoRefinado.h"

class SilicioPuro : public ProdutoRefinado {
public:
    SilicioPuro() noexcept;
    ~SilicioPuro() noexcept override;

    Item* clone() const override;
};

#endif // SIMULADOR_SILICIOPURO_H
