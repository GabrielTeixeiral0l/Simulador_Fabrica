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

void Lancador::atuar([[maybe_unused]] Fabrica& fabrica, [[maybe_unused]] int linha, [[maybe_unused]] int coluna) {
    // Mecanismo base de atuacao iniciado para Checkpoint 2
}

Maquina* Lancador::clone() const {
    return new Lancador(*this);
}
