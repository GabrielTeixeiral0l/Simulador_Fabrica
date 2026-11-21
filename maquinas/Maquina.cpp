#include "Maquina.h"
#include "Perfuradora.h"
#include "Transportador.h"
#include "Refinaria.h"
#include "Oficina.h"
#include "Silo.h"
#include "Lancador.h"

using std::string;

int Maquina::proximoId = 1;

Maquina::Maquina(int custo, Orientacao orientacao) noexcept
    : id(proximoId++), orientacao(orientacao), custo(custo), ativo(true) {}

Maquina::~Maquina() noexcept = default;

void Maquina::rodar() noexcept {
    orientacao.rodar();
}

void Maquina::setOrientacao(Orientacao novaOrientacao) noexcept {
    orientacao = novaOrientacao;
}

Orientacao Maquina::getOrientacao() const noexcept {
    return orientacao;
}

char Maquina::getOrientacaoChar() const noexcept {
    return orientacao.getDirecao();
}

string Maquina::getOrientacaoNome() const {
    return orientacao.getNome();
}

int Maquina::getId() const noexcept {
    return id;
}

int Maquina::getCusto() const noexcept {
    return custo;
}

bool Maquina::isAtivo() const noexcept {
    return ativo;
}

void Maquina::setAtivo(bool estado) noexcept {
    ativo = estado;
}

bool Maquina::aceitarItem(Item*) {
    return false;
}

Orientacao Maquina::charParaOrientacao(char c) noexcept {
    switch (c) {
        case 'c': return Orientacao(Orientacao::Norte);
        case 'b': return Orientacao(Orientacao::Sul);
        case 'e': return Orientacao(Orientacao::Oeste);
        case 'd': return Orientacao(Orientacao::Este);
        default: return Orientacao(Orientacao::Norte);
    }
}

Maquina* Maquina::criar(const string& tipo, Orientacao orientacao) {
    if (tipo == "p") return new Perfuradora(orientacao);
    if (tipo == "t") return new Transportador(orientacao);
    if (tipo == "r") return new Refinaria(orientacao);
    if (tipo == "o") return new Oficina(orientacao);
    if (tipo == "s") return new Silo(orientacao);
    if (tipo == "l") return new Lancador(orientacao);
    return nullptr;
}
