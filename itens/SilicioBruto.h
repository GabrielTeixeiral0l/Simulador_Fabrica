#ifndef SIMULADOR_SILICIOBRUTO_H
#define SIMULADOR_SILICIOBRUTO_H

#include "MateriaPrima.h"

class SilicioBruto : public MateriaPrima {
public:
    SilicioBruto() noexcept;
    ~SilicioBruto() noexcept override;

    Item* duplicar() const override;
};

#endif // SIMULADOR_SILICIOBRUTO_H
