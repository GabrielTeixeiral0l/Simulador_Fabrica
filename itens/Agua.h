#ifndef SIMULADOR_AGUA_H
#define SIMULADOR_AGUA_H

#include "ProdutoRefinado.h"

class Agua : public ProdutoRefinado {
public:
    Agua() noexcept;
    ~Agua() noexcept override;

    Item* clone() const override;
};

#endif // SIMULADOR_AGUA_H
