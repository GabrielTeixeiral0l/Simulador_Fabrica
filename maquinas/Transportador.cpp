#include "Transportador.h"
#include "../Settings.h"

using std::string;

Transportador::Transportador(Orientacao orientacao) noexcept
    : Maquina(Settings::transportador_custo, orientacao) {}

char Transportador::getSimbolo() const noexcept {
    switch (getOrientacaoChar()) {
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

string Transportador::getDescricao() const {
    return "Transportador (direcao " + getOrientacaoNome() + ")";
}

void Transportador::operar(Fabrica&, int, int) {
    // Mecanismo base de atuacao iniciado para Checkpoint 2
}
