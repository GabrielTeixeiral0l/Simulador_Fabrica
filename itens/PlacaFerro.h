#ifndef SIMULADOR_PLACAFERRO_H
#define SIMULADOR_PLACAFERRO_H

#include "ProdutoRefinado.h"

class PlacaFerro : public ProdutoRefinado {
public:
    PlacaFerro() noexcept;
    ~PlacaFerro() noexcept override;

    Item* clone() const override;
};

#endif // SIMULADOR_PLACAFERRO_H
