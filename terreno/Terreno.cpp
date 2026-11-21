#include "Terreno.h"

Terreno::Terreno() noexcept
    : maquina(nullptr) {}

Terreno::~Terreno() noexcept {
    delete maquina;
    maquina = nullptr;
}

char Terreno::getSimbolo() const noexcept {
    if (maquina != nullptr) {
        return maquina->getSimbolo();
    }
    return getSimboloTerreno();
}

bool Terreno::podeConstruir() const noexcept {
    return false;
}

bool Terreno::extrair(int) noexcept {
    return false;
}

int Terreno::getQuantidade() const noexcept {
    return 0;
}

bool Terreno::colocarMaquina(Maquina* novaMaquina) noexcept {
    if (maquina != nullptr || novaMaquina == nullptr || !podeConstruir()) {
        return false;
    }
    maquina = novaMaquina;
    return true;
}

Maquina* Terreno::removerMaquina() noexcept {
    Maquina* rem = maquina;
    maquina = nullptr;
    return rem;
}

const Maquina* Terreno::getMaquina() const noexcept {
    return maquina;
}

Maquina* Terreno::getMaquina() noexcept {
    return maquina;
}


bool Terreno::isSolo() const noexcept {
    return false;
}
