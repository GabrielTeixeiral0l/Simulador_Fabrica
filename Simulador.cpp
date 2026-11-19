#include "Simulador.h"
#include <iostream>
#include <algorithm>

Simulador::Simulador(int numLinhas, int numColunas)
    : fabrica(numLinhas, numColunas), ecra() {}

void Simulador::desenharRegua() noexcept {
    int colunas = fabrica.getColunas();
    int linhas = fabrica.getLinhas();

    for (int c = 0; c < colunas; ++c) {
        char letraCol = static_cast<char>('A' + c);
        ecra.escrever(1, 3 + c, letraCol);
    }

    for (int l = 0; l < linhas; ++l) {
        char letraLin = static_cast<char>('A' + l);
        ecra.escrever(2 + l, 1, letraLin);
    }
}

void Simulador::desenharPainel() {
    int colunas = fabrica.getColunas();
    int colunaPainel = colunas + 6;

    ecra.escrever(1, colunaPainel + 2, "Instante: " + std::to_string(fabrica.getInstante()));
    ecra.escrever(2, colunaPainel + 2, "Creditos: " + std::to_string(fabrica.getCreditos()));
    ecra.escrever(3, colunaPainel + 2, "Maquinas: 0");
    ecra.escrever(4, colunaPainel + 2, "Engenheiros: 0");
    ecra.escrever(6, colunaPainel + 2, "No ultimo instante:");
    ecra.escrever(7, colunaPainel + 2, "Simulacao iniciada");
}

void Simulador::desenharFabrica() {
    ecra.limpar();

    int linhas = fabrica.getLinhas();
    int colunas = fabrica.getColunas();

    int alturaFabrica = linhas + 3;
    int larguraFabrica = colunas + 4;

    const int alturaPainel = 12;
    const int larguraPainel = 30;

    int alturaTotal = std::max(alturaFabrica, alturaPainel);
    int larguraTotal = larguraFabrica + 1 + larguraPainel;

    ecra.setDimensoes(alturaTotal, larguraTotal);

    ecra.desenharMoldura(0, 0, alturaTotal, larguraFabrica);
    desenharRegua();

    for (int l = 0; l < linhas; ++l) {
        for (int c = 0; c < colunas; ++c) {
            const Terreno* terreno = fabrica.getTerreno(l, c);
            char simbolo = (terreno != nullptr) ? terreno->getSimbolo() : ' ';
            ecra.escrever(2 + l, 3 + c, simbolo);
        }
    }

    int colunaPainel = larguraFabrica + 1;
    ecra.desenharMoldura(0, colunaPainel, alturaTotal, larguraPainel);
    desenharPainel();
}

void Simulador::executar() {
    desenharFabrica();
    ecra.mostrar();
    std::cout << '\n';
    std::cout << fabrica.getInfoPosicao("aa") << '\n';
}

bool Simulador::carregarFicheiro(const std::string& nomeFicheiro) {
    return fabrica.carregarFicheiro(nomeFicheiro);
}
