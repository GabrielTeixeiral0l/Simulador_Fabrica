#include "Silo.h"
#include "../Fabrica.h"
#include "../Settings.h"
#include "../FerramentasAuxiliares.h"

using std::string;

Silo::Silo(Orientacao orientacao) noexcept
    : Maquina(Settings::silo_custo, orientacao) {}

Silo::~Silo() noexcept = default;

char Silo::getSimbolo() const noexcept {
    return 'S';
}

string Silo::getDescricao() const {
    return armazenamento.getInfoEstado() + " (direcao " + getOrientacaoNome() + ")";
}

bool Silo::aceitaItem(Item* item) {
    return armazenamento.adicionarItem(item);
}

void Silo::operar(Fabrica& fabrica, int linha, int coluna) {
    if (armazenamento.getQuantidadeTotal() > 0 && FerramentasAuxiliares::probabilidadeOcorre(Settings::silo_prob_perda)) {
        armazenamento.descartarItemMaisAntigo();
    }

    Item* maisAntigo = armazenamento.obterItemMaisAntigo();
    if (maisAntigo == nullptr) {
        return;
    }

    int linhaDestino = linha;
    int colunaDestino = coluna;
    Fabrica::getPosicaoAdjacente(linha, coluna, getOrientacao(), linhaDestino, colunaDestino);

    Terreno* terrenoDestino = fabrica.getTerreno(linhaDestino, colunaDestino);
    if (terrenoDestino == nullptr || terrenoDestino->getMaquina() == nullptr) {
        return;
    }

    if (terrenoDestino->getMaquina()->aceitaItem(maisAntigo)) {
        Item* transferido = nullptr;
        armazenamento.removerItemMaisAntigo(transferido);
    }
}
