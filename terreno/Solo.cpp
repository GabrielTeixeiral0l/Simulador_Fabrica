#include "Solo.h"

using std::string;

Solo::Solo() noexcept
    : maquina(nullptr) {}

Solo::~Solo() noexcept {
    delete maquina;
    maquina = nullptr;
}

char Solo::getSimbolo() const noexcept {
    if (maquina != nullptr) {
        return maquina->getSimbolo();
    }
    return ' ';
}

string Solo::getDescricao() const {
    if (maquina != nullptr) {
        return "Solo com " + maquina->getDescricao();
    }
    return "Solo vazio";
}

bool Solo::podeConstruir() const noexcept {
    return maquina == nullptr;
}

bool Solo::colocarMaquina(Maquina* novaMaquina) noexcept {
    if (maquina != nullptr || novaMaquina == nullptr) {
        return false;
    }
    maquina = novaMaquina;
    return true;
}

Maquina* Solo::removerMaquina() noexcept {
    Maquina* rem = maquina;
    maquina = nullptr;
    return rem;
}

const Maquina* Solo::getMaquina() const noexcept {
    return maquina;
}

Maquina* Solo::getMaquina() noexcept {
    return maquina;
}
