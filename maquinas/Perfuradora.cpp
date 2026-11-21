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
    tentarEnviarItem(fabrica, linha, coluna, itemArmazenado);

    if (itemArmazenado != nullptr) {
        return;
    }

    ++instantesPassados;
    if (instantesPassados < Settings::perfuradora_periodo) {
        return;
    }
    instantesPassados = 0;

    Terreno* terrenoAtual = fabrica.getTerreno(linha, coluna);
    if (terrenoAtual == nullptr) {
        return;
    }

    Item* novoItem = terrenoAtual->extrairItem();
    if (novoItem == nullptr) {
        return;
    }

    if (FerramentasAuxiliares::probabilidadeOcorre(Settings::perfuradora_prob_perda)) {
        delete novoItem;
        return;
    }

    itemArmazenado = novoItem;
    tentarEnviarItem(fabrica, linha, coluna, itemArmazenado);
}