#include "Silo.h"
#include "../Settings.h"

Silo::Silo(Orientacao orientacao) noexcept
    : Maquina(Settings::silo_custo, orientacao) {}

char Silo::getSimbolo() const noexcept {
    return 'S';
}

std::string Silo::getDescricao() const {
    return "Armazem (direcao " + getOrientacaoNome() + ")";
}

void Silo::atuar(Fabrica&, int, int) {
    // Mecanismo base de atuacao iniciado para Checkpoint 2
}
