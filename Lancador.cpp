#include "Lancador.h"
#include "Settings.h"

Lancador::Lancador(Orientacao orientacao) noexcept
    : Maquina(Settings::lancador_custo, orientacao) {}

char Lancador::getSimbolo() const noexcept {
    return 'L';
}

std::string Lancador::getDescricao() const {
    return "Lancador (direcao " + getOrientacaoNome() + ")";
}

void Lancador::atuar(Fabrica&, int, int) {
    // Mecanismo base de atuacao iniciado para Checkpoint 2
}
