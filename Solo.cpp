#include "Solo.h"

Solo::Solo() noexcept
    : maquina(nullptr) {}

Solo::~Solo() noexcept {
    delete maquina;
    maquina = nullptr;
}

Solo::Solo(const Solo& outro)
    : Terreno(outro), maquina(outro.maquina != nullptr ? outro.maquina->clone() : nullptr) {}

Solo& Solo::operator=(const Solo& outro) {
    if (this != &outro) {
        delete maquina;
        maquina = (outro.maquina != nullptr) ? outro.maquina->clone() : nullptr;
    }
    return *this;
}

char Solo::getSimbolo() const noexcept {
    if (maquina != nullptr) {
        return maquina->getSimbolo();
    }
    return ' ';
}

std::string Solo::getDescricao() const {
    if (maquina != nullptr) {
        return "Solo com " + maquina->getDescricao();
    }
    return "Solo vazio";
}

bool Solo::podeConstruir() const noexcept {
    return maquina == nullptr;
}

Terreno* Solo::clone() const {
    return new Solo(*this);
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
