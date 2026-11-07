#include "Ecra.h"
#include <iostream>

Ecra::Ecra(int numLinhas, int numColunas) noexcept
    : linhas(numLinhas), colunas(numColunas), linhaCursor(0), colunaCursor(0) {
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

bool Ecra::estaDentroDosLimites(int linha, int coluna) const noexcept {
    return linha >= 0 && linha < linhas && coluna >= 0 && coluna < colunas;
}

void Ecra::colocarCaractere(int linha, int coluna, char caractere) noexcept {
    if (estaDentroDosLimites(linha, coluna)) {
        buffer[linha][coluna] = caractere;
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

bool Ecra::gotoxy(int linha, int coluna) noexcept {
    if (estaDentroDosLimites(linha, coluna)) {
        linhaCursor = linha;
        colunaCursor = coluna;
        return true;
    }
    return false;
}

void Ecra::escrever(char caractere) noexcept {
    if (caractere == '\n') {
        linhaCursor++;
        colunaCursor = 0;
        return;
    }

    if (colunaCursor >= colunas) {
        linhaCursor++;
        colunaCursor = 0;
    }

    if (estaDentroDosLimites(linhaCursor, colunaCursor)) {
        buffer[linhaCursor][colunaCursor] = caractere;
        colunaCursor++;
    }
}

void Ecra::escrever(const std::string& texto) {
    for (int i = 0; i < texto.length(); ++i) {
        escrever(texto[i]);
    }
}

void Ecra::escrever(int linha, int coluna, char caractere) noexcept {
    if (gotoxy(linha, coluna)) {
        escrever(caractere);
    }
}

void Ecra::escrever(int linha, int coluna, const std::string& texto) {
    if (gotoxy(linha, coluna)) {
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

    for (int l = 0; l < linhas; ++l) {
        for (int c = 0; c < colunas; ++c) {
            saida += buffer[l][c];
        }
        saida += '\n';
    }

    std::cout << saida;
}

void Ecra::setDimensoes(int numLinhas, int numColunas) noexcept { // Forma de redefinir o tamanho do ecra
    if (numLinhas >= 1 && numLinhas <= Settings::ecra_max_linhas) {
        linhas = numLinhas;
    }
    if (numColunas >= 1 && numColunas <= Settings::ecra_max_colunas) {
        colunas = numColunas;
    }
}

char Ecra::getCaractere(int linha, int coluna) const noexcept {
    if (estaDentroDosLimites(linha, coluna)) {
        return buffer[linha][coluna];
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
