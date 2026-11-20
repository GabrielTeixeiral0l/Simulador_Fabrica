#include "Simulador.h"
#include "comandos/Comando.h"
#include <iostream>

using std::string;
using std::cout;
using std::cin;

Simulador::Simulador()
    : fabrica(), ecra(), emExecucao(false), ultimaMensagem("Simulacao iniciada") {}

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
    ecra.escrever(3, colunaPainel + 2, "Maquinas: " + std::to_string(fabrica.getNumMaquinas()));
    ecra.escrever(4, colunaPainel + 2, "Engenheiros: 0");
    ecra.escrever(6, colunaPainel + 2, "No ultimo instante:");
    string msgPainel = ultimaMensagem;
    std::size_t posQuebra = msgPainel.find('\n');
    if (posQuebra != string::npos) msgPainel = msgPainel.substr(0, posQuebra);
    if (msgPainel.length() > 26) msgPainel = msgPainel.substr(0, 26);
    ecra.escrever(7, colunaPainel + 2, msgPainel);
}

void Simulador::desenharFabrica() {
    ecra.limpar();

    int linhas = fabrica.getLinhas();
    int colunas = fabrica.getColunas();

    if (linhas == 0 || colunas == 0) {
        const int larguraAviso = 46;
        const int alturaAviso = 12;
        ecra.setDimensoes(alturaAviso, larguraAviso);
        ecra.desenharMoldura(0, 0, alturaAviso, larguraAviso);
        ecra.escrever(2, 3, "Nenhuma fabrica ativa.");
        ecra.escrever(4, 3, "Use um dos seguintes comandos:");
        ecra.escrever(5, 5, "fabrica <linhas> <colunas>");
        ecra.escrever(6, 5, "carrega <ficheiro>");
        string msg = ultimaMensagem;
        std::size_t pos = msg.find('\n');
        if (pos != string::npos) msg = msg.substr(0, pos);
        if (msg.length() > 40) msg = msg.substr(0, 40);
        ecra.escrever(9, 3, "Estado: " + msg);
        return;
    }

    int alturaFabrica = linhas + 3;
    int larguraFabrica = colunas + 4;

    const int alturaPainel = 12;
    const int larguraPainel = 30;

    int alturaTotal = (alturaFabrica > alturaPainel ? alturaFabrica : alturaPainel);
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

string Simulador::processarLinha(const string& linha) {
    if (linha.empty()) {
        return "";
    }

    Comando* cmd = Comando::criar(linha);
    if (cmd == nullptr) {
        ultimaMensagem = "Comando desconhecido";
        return "Comando desconhecido: " + linha + " (escreva 'ajuda' para listar os comandos).";
    }

    if (!cmd->validar()) {
        string erroMsg = "Parametros invalidos para o comando.\nAjuda:\n" + cmd->getAjuda();
        delete cmd;
        ultimaMensagem = "Erro de parametros";
        return erroMsg;
    }

    string resultado = cmd->executar(fabrica, *this);
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

    string linha;
    while (emExecucao) {
        cout << "\nComando: ";
        if (!std::getline(cin, linha)) {
            break;
        }

        if (linha.empty()) {
            continue;
        }

        string resultado = processarLinha(linha);
        if (!resultado.empty()) {
            cout << resultado << '\n';
        }

        if (emExecucao) {
            desenharFabrica();
            ecra.mostrar();
        }
    }
}

bool Simulador::carregarFicheiro(const string& nomeFicheiro) {
    return fabrica.carregarFicheiro(nomeFicheiro);
}
