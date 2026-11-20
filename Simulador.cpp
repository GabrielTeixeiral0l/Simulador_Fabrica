#include "Simulador.h"
#include "comandos/Comando.h"
#include <iostream>

using std::string;
using std::cout;
using std::cin;

static const int MARGEM_ESQ_GRELHA = 3;
static const int MARGEM_TOPO_GRELHA = 2;
static const int LARGURA_PAINEL = 30;
static const int ALTURA_PAINEL = 12;
static const int MARGEM_LATERAL_PAINEL = 2; // 1 borda '|' + 1 espaco interior

Simulador::Simulador()
    : fabrica(), ecra(), emExecucao(false), ultimaMensagem("Simulacao iniciada") {}

void Simulador::desenharEcraInicial() {
    const int larguraAviso = 46;
    ecra.setDimensoes(ALTURA_PAINEL, larguraAviso);
    ecra.desenharMoldura(0, 0, ALTURA_PAINEL, larguraAviso);

    ecra.escrever(2, 3, "Nenhuma fabrica ativa.");
    ecra.escrever(4, 3, "Use um dos seguintes comandos:");
    ecra.escrever(5, 5, "fabrica <linhas> <colunas>");
    ecra.escrever(6, 5, "carrega <ficheiro>");
    ecra.escrever(9, 3, "Estado: " + ultimaMensagem, 35);
}

void Simulador::desenharRegua() noexcept {
    for (int c = 0; c < fabrica.getColunas(); ++c) {
        ecra.escrever(1, MARGEM_ESQ_GRELHA + c, static_cast<char>('A' + c));
    }
    for (int l = 0; l < fabrica.getLinhas(); ++l) {
        ecra.escrever(MARGEM_TOPO_GRELHA + l, 1, static_cast<char>('A' + l));
    }
}

void Simulador::desenharGrelha() noexcept {
    for (int l = 0; l < fabrica.getLinhas(); ++l) {
        for (int c = 0; c < fabrica.getColunas(); ++c) {
            const Terreno* terreno = fabrica.getTerreno(l, c);
            char simbolo = (terreno != nullptr) ? terreno->getSimbolo() : ' ';
            ecra.escrever(MARGEM_TOPO_GRELHA + l, MARGEM_ESQ_GRELHA + c, simbolo);
        }
    }
}

void Simulador::desenharPainel(int colunaPainel) {
    int colTexto = colunaPainel + MARGEM_LATERAL_PAINEL;
    int larguraUtil = LARGURA_PAINEL - (2 * MARGEM_LATERAL_PAINEL);
    ecra.escrever(1, colTexto, "Instante: " + std::to_string(fabrica.getInstante()));
    ecra.escrever(2, colTexto, "Creditos: " + std::to_string(fabrica.getCreditos()));
    ecra.escrever(3, colTexto, "Maquinas: " + std::to_string(fabrica.getNumMaquinas()));
    ecra.escrever(4, colTexto, "Engenheiros: 0");
    ecra.escrever(6, colTexto, "No ultimo instante:");

    ecra.escrever(7, colTexto, ultimaMensagem, larguraUtil);
}

void Simulador::desenharFabrica() {
    ecra.limpar();

    int linhas = fabrica.getLinhas();
    int colunas = fabrica.getColunas();
    if (linhas == 0 || colunas == 0) {
        desenharEcraInicial();
        return;
    }

    int alturaCaixa = MARGEM_TOPO_GRELHA + linhas + 1;
    int larguraCaixa = MARGEM_ESQ_GRELHA + colunas + 1;
    int alturaTotal = (alturaCaixa > ALTURA_PAINEL) ? alturaCaixa : ALTURA_PAINEL;
    int colunaPainel = larguraCaixa + 1;

    ecra.setDimensoes(alturaTotal, colunaPainel + LARGURA_PAINEL);

    ecra.desenharMoldura(0, 0, alturaTotal, larguraCaixa);
    desenharRegua();
    desenharGrelha();

    ecra.desenharMoldura(0, colunaPainel, alturaTotal, LARGURA_PAINEL);
    desenharPainel(colunaPainel);
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
