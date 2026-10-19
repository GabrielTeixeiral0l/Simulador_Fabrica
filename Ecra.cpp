#include "Ecra.h"
#include <iostream>

Ecra::Ecra(int l, int c) noexcept
    : linhas(l), colunas(c), linhaCursor(0), colunaCursor(0) {
    if (linhas < 1) {
        linhas = 1;
    } else if (linhas > Settings::ecra_max_linhas) {
        linhas = Settings::ecra_max_linhas;
    }

    if (colunas < 1) {
        colunas = 1;
    } else if (colunas > Settings::ecra_max_colunas) {
        colunas = Settings::ecra_max_colunas;
    }

    limpar();
}

bool Ecra::estaDentroDosLimites(int l, int c) const noexcept {
    return l >= 0 && l < linhas && c >= 0 && c < colunas;
}

void Ecra::colocarCaractere(int l, int c, char ch) noexcept {
    if (estaDentroDosLimites(l, c)) {
        buffer[l][c] = ch;
    }
}

void Ecra::limpar() noexcept {
    for (int l = 0; l < Settings::ecra_max_linhas; ++l) {
        for (int c = 0; c < Settings::ecra_max_colunas; ++c) {
            buffer[l][c] = ' ';
        }
    }
    linhaCursor = 0;
    colunaCursor = 0;
}

bool Ecra::gotoxy(int l, int c) noexcept {
    if (estaDentroDosLimites(l, c)) {
        linhaCursor = l;
        colunaCursor = c;
        return true;
    }
    return false;
}

void Ecra::escrever(char c) noexcept {
    if (c == '\n') {
        linhaCursor++;
        colunaCursor = 0;
        return;
    }

    if (colunaCursor >= colunas) {
        linhaCursor++;
        colunaCursor = 0;
    }

    if (estaDentroDosLimites(linhaCursor, colunaCursor)) {
        buffer[linhaCursor][colunaCursor] = c;
        colunaCursor++;
    }
}

void Ecra::escrever(const std::string& texto) {
    for (char c : texto) {
        escrever(c);
    }
}

void Ecra::escrever(int l, int c, char ch) noexcept {
    if (gotoxy(l, c)) {
        escrever(ch);
    }
}

void Ecra::escrever(int l, int c, const std::string& texto) {
    if (gotoxy(l, c)) {
        escrever(texto);
    }
}

void Ecra::desenharMoldura(int linhaInicio, int colunaInicio, int altura, int largura) noexcept {
    if (altura < 2 || largura < 2) {
        return;
    }

    int linhaFim = linhaInicio + altura - 1;
    int colunaFim = colunaInicio + largura - 1;

    for (int c = colunaInicio + 1; c < colunaFim; ++c) {
        colocarCaractere(linhaInicio, c, '-');
        colocarCaractere(linhaFim, c, '-');
    }

    for (int l = linhaInicio + 1; l < linhaFim; ++l) {
        colocarCaractere(l, colunaInicio, '|');
        colocarCaractere(l, colunaFim, '|');
    }

    colocarCaractere(linhaInicio, colunaInicio, '+');
    colocarCaractere(linhaInicio, colunaFim, '+');
    colocarCaractere(linhaFim, colunaInicio, '+');
    colocarCaractere(linhaFim, colunaFim, '+');
}

void Ecra::mostrar() const {
    std::string saida;
    saida.reserve(linhas * (colunas + 1));

    for (int l = 0; l < linhas; ++l) {
        for (int c = 0; c < colunas; ++c) {
            saida += buffer[l][c];
        }
        saida += '\n';
    }

    std::cout << saida;
}

char Ecra::getCaractere(int l, int c) const noexcept {
    if (estaDentroDosLimites(l, c)) {
        return buffer[l][c];
    }
    return ' ';
}

int Ecra::getLinhas() const noexcept {
    return linhas;
}

int Ecra::getColunas() const noexcept {
    return colunas;
}

int Ecra::getLinhaCursor() const noexcept {
    return linhaCursor;
}

int Ecra::getColunaCursor() const noexcept {
    return colunaCursor;
}