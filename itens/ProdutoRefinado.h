#ifndef SIMULADOR_PRODUTOREFINADO_H
#define SIMULADOR_PRODUTOREFINADO_H

#include "Item.h"
#include <string>

class ProdutoRefinado : public Item {
protected:
    ProdutoRefinado(std::string nome, char simbolo, int valor) noexcept;

public:
    ~ProdutoRefinado() noexcept override;
};

#endif // SIMULADOR_PRODUTOREFINADO_H
