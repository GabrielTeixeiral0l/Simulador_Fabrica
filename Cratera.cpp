#include "Cratera.h"

char Cratera::getSimbolo() const noexcept {
    return '#';
}

std::string Cratera::getDescricao() const {
    return "Cratera";
}

Terreno* Cratera::clone() const {
    return new Cratera(*this);
}
