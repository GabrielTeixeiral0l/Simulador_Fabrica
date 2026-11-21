#ifndef SIMULADOR_MATERIAPRIMA_H
#define SIMULADOR_MATERIAPRIMA_H

#include "Item.h"
#include <string>

class MateriaPrima : public Item {
protected:
    MateriaPrima(std::string nome, char simbolo, int valor) noexcept;

public:
    ~MateriaPrima() noexcept override;
};

#endif // SIMULADOR_MATERIAPRIMA_H
