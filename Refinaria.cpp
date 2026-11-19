#include "Refinaria.h"
#include "Settings.h"

Refinaria::Refinaria(Orientacao orientacao) noexcept
    : Maquina(Settings::refinaria_custo, orientacao) {}

char Refinaria::getSimbolo() const noexcept {
    return 'R';
}

std::string Refinaria::getDescricao() const {
    return "Refinaria (direcao " + getOrientacaoNome() + ")";
}

void Refinaria::atuar([[maybe_unused]] Fabrica& fabrica, [[maybe_unused]] int linha, [[maybe_unused]] int coluna) {
    // Mecanismo base de atuacao iniciado para Checkpoint 2
}

Maquina* Refinaria::clone() const {
    return new Refinaria(*this);
}
