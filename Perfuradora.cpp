#include "Perfuradora.h"
#include "Settings.h"

Perfuradora::Perfuradora(Orientacao orientacao) noexcept
    : Maquina(Settings::perfuradora_custo, orientacao) {}

char Perfuradora::getSimbolo() const noexcept {
    return 'P';
}

std::string Perfuradora::getDescricao() const {
    return "Perfuradora (direcao " + getOrientacaoNome() + ")";
}

void Perfuradora::atuar([[maybe_unused]] Fabrica& fabrica, [[maybe_unused]] int linha, [[maybe_unused]] int coluna) {
    // Mecanismo base de atuacao iniciado para Checkpoint 2
}

Maquina* Perfuradora::clone() const {
    return new Perfuradora(*this);
}
