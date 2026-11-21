#ifndef SIMULADOR_ARMAZEM_H
#define SIMULADOR_ARMAZEM_H

#include <string>
#include "itens/Item.h"

class Armazem {
    Item** itens;
    int quantidade;

public:
    Armazem() noexcept;
    ~Armazem();
    Armazem(const Armazem& outro);
    Armazem& operator=(const Armazem& outro);

    void libertarItens() noexcept;
    bool adicionarItem(Item* item);
    Item* obterItemMaisAntigo() const noexcept;
    bool removerItemMaisAntigo(Item*& itemRemovido);
    bool descartarItemMaisAntigo() noexcept;

    int getQuantidadeTotal() const noexcept;
    int getQuantidadePorTipo(const std::string& nome) const noexcept;
    std::string getInfoEstado() const;
};

#endif // SIMULADOR_ARMAZEM_H
