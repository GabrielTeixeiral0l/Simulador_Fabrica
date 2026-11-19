#include "Oficina.h"
#include "Settings.h"

Oficina::Oficina(Orientacao orientacao) noexcept
    : Maquina(Settings::oficina_custo, orientacao) {}

char Oficina::getSimbolo() const noexcept {
    return 'O';
}

std::string Oficina::getDescricao() const {
    return "Oficina (direcao " + getOrientacaoNome() + ")";
}

void Oficina::atuar([[maybe_unused]] Fabrica& fabrica, [[maybe_unused]] int linha, [[maybe_unused]] int coluna) {
    // Mecanismo base de atuacao iniciado para Checkpoint 2
}

Maquina* Oficina::clone() const {
    return new Oficina(*this);
}
