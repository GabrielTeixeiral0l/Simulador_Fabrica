#include "Orientacao.h"

using std::string;

Orientacao::Orientacao(char dir) noexcept {
    if (dir == Norte || dir == Este || dir == Sul || dir == Oeste) {
        direcao = dir;
    } else {
        direcao = Norte;
    }
}

char Orientacao::getDirecao() const noexcept {
    return direcao;
}

string Orientacao::getNome() const {
    switch (direcao) {
        case Norte: return "Cima";
        case Este:  return "Direita";
        case Sul:   return "Baixo";
        case Oeste: return "Esquerda";
        default:    return "Cima";
    }
}

void Orientacao::rodar() noexcept {
    switch (direcao) {
        case Norte: direcao = Este; break;
        case Este:  direcao = Sul; break;
        case Sul:   direcao = Oeste; break;
        case Oeste: direcao = Norte; break;
    }
}

int Orientacao::getPassoLinha() const noexcept {
    if (direcao == Norte) return -1;
    if (direcao == Sul)   return 1;
    return 0;
}

int Orientacao::getPassoColuna() const noexcept {
    if (direcao == Este)  return 1;
    if (direcao == Oeste) return -1;
    return 0;
}

bool Orientacao::igualA(const Orientacao& outra) const noexcept {
    return direcao == outra.direcao;
}

Orientacao Orientacao::deChar(char c) noexcept {
    switch (c) {
        case 'c': case 'C': case '^': return Orientacao(Norte);
        case 'd': case 'D': case '>': return Orientacao(Este);
        case 'b': case 'B': case 'v': case 'V': return Orientacao(Sul);
        case 'e': case 'E': case '<': return Orientacao(Oeste);
        default: return Orientacao(Norte);
    }
}
