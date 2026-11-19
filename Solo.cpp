#include "Solo.h"

char Solo::getSimbolo() const noexcept {
    return ' ';
}

std::string Solo::getDescricao() const {
    return "Solo vazio";
}

bool Solo::podeConstruir() const noexcept {
    return true;
}

Terreno* Solo::clone() const {
    return new Solo(*this);
}
