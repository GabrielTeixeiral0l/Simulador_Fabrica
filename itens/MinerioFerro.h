#ifndef SIMULADOR_MINERIOFERRO_H
#define SIMULADOR_MINERIOFERRO_H

#include "MateriaPrima.h"

class MinerioFerro : public MateriaPrima {
public:
    MinerioFerro() noexcept;
    ~MinerioFerro() noexcept override;

    Item* clone() const override;
};

#endif // SIMULADOR_MINERIOFERRO_H
