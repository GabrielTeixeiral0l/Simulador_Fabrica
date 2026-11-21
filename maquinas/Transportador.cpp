#include "Transportador.h"
#include "../Fabrica.h"
#include "../Settings.h"
#include "../itens/Item.h"

using std::string;

Transportador::Transportador(Orientacao orientacao) noexcept
    : Maquina(Settings::transportador_custo, orientacao), itemArmazenado(nullptr) {}

Transportador::~Transportador() noexcept {
    delete itemArmazenado;
}

char Transportador::getSimbolo() const noexcept {
    if (itemArmazenado != nullptr) {
        return itemArmazenado->getSimbolo();
    }
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
    string desc = "Transportador (direcao " + getOrientacaoNome() + ")";
    if (itemArmazenado != nullptr) {
        desc += " com " + itemArmazenado->getNome();
    }
    return desc;
}

bool Transportador::aceitaItem(Item* item) {
    if (itemArmazenado != nullptr || item == nullptr) {
        return false;
    }
    itemArmazenado = item;
    return true;
}

void Transportador::operar(Fabrica& fabrica, int linha, int coluna) {
    tentarEnviarItem(fabrica, linha, coluna, itemArmazenado);
}
