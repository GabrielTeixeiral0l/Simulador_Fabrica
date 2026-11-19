#include "Refinaria.h"
#include "../Settings.h"

Refinaria::Refinaria(Orientacao orientacao) noexcept
    : Maquina(Settings::refinaria_custo, orientacao) {}

char Refinaria::getSimbolo() const noexcept {
    return 'R';
}

std::string Refinaria::getDescricao() const {
    return "Refinaria (direcao " + getOrientacaoNome() + ")";
}

void Refinaria::atuar(Fabrica&, int, int) {
    // Mecanismo base de atuacao iniciado para Checkpoint 2
}
