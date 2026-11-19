#include "Transportador.h"
#include "Settings.h"

Transportador::Transportador(Orientacao orientacao) noexcept
    : Maquina(Settings::transportador_custo, orientacao) {}

char Transportador::getSimbolo() const noexcept {
    switch (getOrientacao()) {
        case Orientacao::Norte:
            return '^';
        case Orientacao::Este:
            return '>';
        case Orientacao::Sul:
            return 'v';
        case Orientacao::Oeste:
            return '<';
    }
    return '>';
}

std::string Transportador::getDescricao() const {
    return "Transportador (direcao " + getOrientacaoNome() + ")";
}

void Transportador::atuar([[maybe_unused]] Fabrica& fabrica, [[maybe_unused]] int linha, [[maybe_unused]] int coluna) {
    // Mecanismo base de atuacao iniciado para Checkpoint 2
}

Maquina* Transportador::clone() const {
    return new Transportador(*this);
}
