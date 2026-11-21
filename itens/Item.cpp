#include "Item.h"
#include <utility>

using std::string;

Item::Item(string nome, char simbolo, int valor) noexcept
    : nome(std::move(nome)), simbolo(simbolo), valor(valor) {}

Item::~Item() noexcept = default;

string Item::getNome() const {
    return nome;
}

char Item::getSimbolo() const noexcept {
    return simbolo;
}

int Item::getValor() const noexcept {
    return valor;
}
