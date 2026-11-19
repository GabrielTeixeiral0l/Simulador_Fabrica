#include "Perfuradora.h"
#include "../Settings.h"

Perfuradora::Perfuradora(Orientacao orientacao) noexcept
    : Maquina(Settings::perfuradora_custo, orientacao) {}

char Perfuradora::getSimbolo() const noexcept {
    return 'P';
}

std::string Perfuradora::getDescricao() const {
    return "Perfuradora (direcao " + getOrientacaoNome() + ")";
}

void Perfuradora::atuar(Fabrica&, int, int) {
    // Mecanismo base de atuacao iniciado para Checkpoint 2
}
