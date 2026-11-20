#include "Oficina.h"
#include "../Settings.h"

using std::string;

Oficina::Oficina(Orientacao orientacao) noexcept
    : Maquina(Settings::oficina_custo, orientacao) {}

char Oficina::getSimbolo() const noexcept {
    return 'O';
}

string Oficina::getDescricao() const {
    return "Oficina (direcao " + getOrientacaoNome() + ")";
}

void Oficina::atuar(Fabrica&, int, int) {
    // Mecanismo base de atuacao iniciado para Checkpoint 2
}
