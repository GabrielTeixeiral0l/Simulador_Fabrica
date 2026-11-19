#include "MaquinaSilo.h"
#include "Settings.h"

MaquinaSilo::MaquinaSilo(Orientacao orientacao) noexcept
    : Maquina(Settings::silo_custo, orientacao) {}

char MaquinaSilo::getSimbolo() const noexcept {
    return 'S';
}

std::string MaquinaSilo::getDescricao() const {
    return "Silo (direcao " + getOrientacaoNome() + ")";
}

void MaquinaSilo::atuar([[maybe_unused]] Fabrica& fabrica, [[maybe_unused]] int linha, [[maybe_unused]] int coluna) {
    // Mecanismo base de atuacao iniciado para Checkpoint 2
}

Maquina* MaquinaSilo::clone() const {
    return new MaquinaSilo(*this);
}
