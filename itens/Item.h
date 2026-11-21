#ifndef SIMULADOR_ITEM_H
#define SIMULADOR_ITEM_H

#include <string>

class Item {
    std::string nome;
    char simbolo;
    int valor;

protected:
    Item(std::string nome, char simbolo, int valor) noexcept;

public:
    virtual ~Item() noexcept;

    std::string getNome() const;
    char getSimbolo() const noexcept;
    int getValor() const noexcept;

    virtual Item* clone() const = 0;
};

#endif // SIMULADOR_ITEM_H
