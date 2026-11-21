#ifndef SIMULADOR_KITHABITAT_H
#define SIMULADOR_KITHABITAT_H

#include "ProdutoRefinado.h"

class KitHabitat : public ProdutoRefinado {
public:
    KitHabitat() noexcept;
    ~KitHabitat() noexcept override;

    Item* clone() const override;
};

#endif // SIMULADOR_KITHABITAT_H
