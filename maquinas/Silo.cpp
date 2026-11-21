#include "Silo.h"
#include "../Fabrica.h"
#include "../Settings.h"
#include <random>

using std::string;

Silo::Silo(Orientacao orientacao) noexcept
    : Maquina(Settings::silo_custo, orientacao) {}

char Silo::getSimbolo() const noexcept {
    return 'S';
}

string Silo::getDescricao() const {
    return armazenamento.getInfoEstado() + " (direcao " + getOrientacaoNome() + ")";
}

bool Silo::aceitarItem(const string& item) {
    return armazenamento.adicionarItem(item);
}

void Silo::operar(Fabrica& fabrica, int linha, int coluna) {
    if (armazenamento.getQuantidadeTotal() > 0 && Settings::silo_prob_perda > 0) {
        static std::random_device rd;
        static std::default_random_engine gen(rd());
        std::uniform_int_distribution<int> dist(0, 99);
        if (dist(gen) < Settings::silo_prob_perda) {
            string perdido;
            armazenamento.removerItemMaisAntigo(perdido);
        }
    }

    string maisAntigo;
    if (!armazenamento.obterItemMaisAntigo(maisAntigo)) {
        return;
    }

    int destL = linha, destC = coluna;
    Fabrica::getPosicaoAdjacente(linha, coluna, getOrientacao(), destL, destC);
    Terreno* destTerreno = fabrica.getTerreno(destL, destC);
    if (destTerreno != nullptr && destTerreno->getMaquina() != nullptr) {
        if (destTerreno->getMaquina()->aceitarItem(maisAntigo)) {
            armazenamento.removerItemMaisAntigo(maisAntigo);
        }
    }
}
