#include "Simulador.h"
#include "Comando.h"
#include <iostream>
#include <algorithm>

Simulador::Simulador(int numLinhas, int numColunas)
    : fabrica(numLinhas, numColunas), ecra(), emExecucao(false), ultimaMensagem("Simulacao iniciada") {}

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
    ecra.escrever(7, colunaPainel + 2, ultimaMensagem);
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

std::string Simulador::processarLinha(const std::string& linha) {
    if (linha.empty()) {
        return "";
    }

    Comando* cmd = Comando::criar(linha);
    if (cmd == nullptr) {
        ultimaMensagem = "Comando invalido";
        return "Comando desconhecido ou argumentos invalidos: " + linha;
    }

    std::string resultado = cmd->executar(fabrica, *this);
    delete cmd;

    ultimaMensagem = resultado;
    return resultado;
}

void Simulador::parar() noexcept {
    emExecucao = false;
}

void Simulador::executar() {
    emExecucao = true;
    desenharFabrica();
    ecra.mostrar();

    std::string linha;
    while (emExecucao) {
        std::cout << "\nComando: ";
        if (!std::getline(std::cin, linha)) {
            break;
        }

        if (linha.empty()) {
            continue;
        }

        std::string resultado = processarLinha(linha);
        if (!resultado.empty()) {
            std::cout << resultado << '\n';
        }

        if (emExecucao) {
            desenharFabrica();
            ecra.mostrar();
        }
    }
}

bool Simulador::carregarFicheiro(const std::string& nomeFicheiro) {
    return fabrica.carregarFicheiro(nomeFicheiro);
}
