#include "Solo.h"

char Solo::getSimboloTerreno() const noexcept { return ' '; }

std::string Solo::getDescricao() const {
    const Maquina* m = getMaquina();
    return m != nullptr ? "Solo com " + m->getDescricao() : "Solo vazio";
}

bool Solo::podeConstruir() const noexcept {
    return getMaquina() == nullptr;
}

bool Solo::isSolo() const noexcept {
    return true;
}