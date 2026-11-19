#include "Maquina.h"

int Maquina::proximoId = 1;

Maquina::Maquina(int custo, Orientacao orientacao) noexcept
    : id(proximoId++), orientacao(orientacao), custo(custo), ativo(true) {}

void Maquina::rodar() noexcept {
    switch (orientacao) {
        case Orientacao::Norte:
            orientacao = Orientacao::Este;
            break;
        case Orientacao::Este:
            orientacao = Orientacao::Sul;
            break;
        case Orientacao::Sul:
            orientacao = Orientacao::Oeste;
            break;
        case Orientacao::Oeste:
            orientacao = Orientacao::Norte;
            break;
    }
}

void Maquina::setOrientacao(Orientacao novaOrientacao) noexcept {
    orientacao = novaOrientacao;
}

Maquina::Orientacao Maquina::getOrientacao() const noexcept {
    return orientacao;
}

char Maquina::getOrientacaoChar() const noexcept {
    switch (orientacao) {
        case Orientacao::Norte:
            return 'c';
        case Orientacao::Este:
            return 'd';
        case Orientacao::Sul:
            return 'b';
        case Orientacao::Oeste:
            return 'e';
    }
    return 'c';
}

std::string Maquina::getOrientacaoNome() const {
    switch (orientacao) {
        case Orientacao::Norte:
            return "Cima";
        case Orientacao::Este:
            return "Direita";
        case Orientacao::Sul:
            return "Baixo";
        case Orientacao::Oeste:
            return "Esquerda";
    }
    return "Cima";
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

Maquina::Orientacao Maquina::charParaOrientacao(char c) {
    switch (c) {
        case 'c':
        case 'C':
        case '^':
            return Orientacao::Norte;
        case 'd':
        case 'D':
        case '>':
            return Orientacao::Este;
        case 'b':
        case 'B':
        case 'v':
        case 'V':
            return Orientacao::Sul;
        case 'e':
        case 'E':
        case '<':
            return Orientacao::Oeste;
        default:
            return Orientacao::Norte;
    }
}
