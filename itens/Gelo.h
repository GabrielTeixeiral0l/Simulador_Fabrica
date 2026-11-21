#ifndef SIMULADOR_GELO_H
#define SIMULADOR_GELO_H

#include "MateriaPrima.h"

class Gelo : public MateriaPrima {
public:
    Gelo() noexcept;
    ~Gelo() noexcept override;

    Item* clone() const override;
};

#endif // SIMULADOR_GELO_H
