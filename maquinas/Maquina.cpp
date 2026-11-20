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
