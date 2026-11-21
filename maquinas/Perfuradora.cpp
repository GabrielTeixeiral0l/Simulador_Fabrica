#include "Perfuradora.h"
#include "../Fabrica.h"
#include "../Settings.h"
#include "../FerramentasAuxiliares.h"
#include "../terreno/Deposito.h"
#include "../itens/MinerioFerro.h"
#include "../itens/SilicioBruto.h"
#include "../itens/Gelo.h"

using std::string;

Perfuradora::Perfuradora(Orientacao orientacao) noexcept
    : Maquina(Settings::perfuradora_custo, orientacao), itemArmazenado(nullptr), instantesPassados(0) {}

Perfuradora::~Perfuradora() noexcept {
    delete itemArmazenado;
}

char Perfuradora::getSimbolo() const noexcept {
    return 'P';
}

string Perfuradora::getDescricao() const {
    string desc = "Perfuradora (direcao " + getOrientacaoNome() + ")";
    if (itemArmazenado != nullptr) {
        desc += " com " + itemArmazenado->getNome();
    }
    return desc;
}

void Perfuradora::operar(Fabrica& fabrica, int linha, int coluna) {
    if (itemArmazenado != nullptr) {
        int destL = linha;
        int destC = coluna;
        Fabrica::getPosicaoAdjacente(linha, coluna, getOrientacao(), destL, destC);
        Terreno* destTerreno = fabrica.getTerreno(destL, destC);
        if (destTerreno != nullptr && destTerreno->getMaquina() != nullptr) {
            if (destTerreno->getMaquina()->aceitarItem(itemArmazenado)) {
                itemArmazenado = nullptr;
            }
        }
    }

    if (itemArmazenado != nullptr) {
        return;
    }

    ++instantesPassados;
    if (instantesPassados >= Settings::perfuradora_periodo) {
        instantesPassados = 0;
        Terreno* terrenoAtual = fabrica.getTerreno(linha, coluna);
        if (terrenoAtual != nullptr && terrenoAtual->getQuantidade() > 0) {
            Deposito* dep = dynamic_cast<Deposito*>(terrenoAtual);
            if (dep != nullptr && dep->extrair(1)) {
                Item* novoItem = nullptr;
                string nomeDep = dep->getNome();
                if (nomeDep == "Ferro") {
                    novoItem = new MinerioFerro();
                } else if (nomeDep == "Silicio") {
                    novoItem = new SilicioBruto();
                } else if (nomeDep == "Gelo") {
                    novoItem = new Gelo();
                }

                if (novoItem != nullptr) {
                    if (FerramentasAuxiliares::probabilidadeOcorre(Settings::perfuradora_prob_perda)) {
                        delete novoItem;
                    } else {
                        itemArmazenado = novoItem;
                        int destL = linha;
                        int destC = coluna;
                        Fabrica::getPosicaoAdjacente(linha, coluna, getOrientacao(), destL, destC);
                        Terreno* destTerreno = fabrica.getTerreno(destL, destC);
                        if (destTerreno != nullptr && destTerreno->getMaquina() != nullptr) {
                            if (destTerreno->getMaquina()->aceitarItem(itemArmazenado)) {
                                itemArmazenado = nullptr;
                            }
                        }
                    }
                }
            }
        }
    }
}
