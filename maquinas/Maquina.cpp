#include "Perfuradora.h"
#include "Transportador.h"
#include "Refinaria.h"
#include "Oficina.h"
#include "Silo.h"
#include "Lancador.h"
#include "Maquina.h"

using std::string;

int Maquina::proximoId = 1;

Maquina::Maquina(int custo, Orientacao orientacao) noexcept
    : id(proximoId++), orientacao(orientacao), custo(custo), ativo(true) {}

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

Orientacao Maquina::charParaOrientacao(char c) noexcept {
    return Orientacao::deChar(c);
}

bool Maquina::aceitarItem(const std::string&) {
    return false;
}

Maquina* Maquina::criar(const std::string& tipo, Orientacao orientacao) {
    if (tipo == "p" || tipo == "perfuradora" || tipo == "P") return new Perfuradora(orientacao);
    if (tipo == "t" || tipo == "transportador" || tipo == "T") return new Transportador(orientacao);
    if (tipo == "r" || tipo == "refinaria" || tipo == "R") return new Refinaria(orientacao);
    if (tipo == "o" || tipo == "oficina" || tipo == "O") return new Oficina(orientacao);
    if (tipo == "s" || tipo == "silo" || tipo == "S") return new Silo(orientacao);
    if (tipo == "l" || tipo == "lancador" || tipo == "L") return new Lancador(orientacao);
    return nullptr;
}
