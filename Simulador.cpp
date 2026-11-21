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

string Simulador::extrairResumoPainel(const string& texto) {
    string primeiraLinha;
    for (std::size_t i = 0; i < texto.size(); ++i) {
        if (texto[i] == '\n') {
            break;
        }
        primeiraLinha += texto[i];
    }
    return primeiraLinha;
}

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
    for (int coluna = 0; coluna < fabrica.getColunas(); ++coluna) {
        ecra.escrever(1, MARGEM_ESQ_GRELHA + coluna, static_cast<char>('A' + coluna));
    }
    for (int linha = 0; linha < fabrica.getLinhas(); ++linha) {
        ecra.escrever(MARGEM_TOPO_GRELHA + linha, 1, static_cast<char>('A' + linha));
    }
}

void Simulador::desenharGrelha() noexcept {
    for (int linha = 0; linha < fabrica.getLinhas(); ++linha) {
        for (int coluna = 0; coluna < fabrica.getColunas(); ++coluna) {
            const Terreno* terreno = fabrica.getTerreno(linha, coluna);
            char simbolo = (terreno != nullptr) ? terreno->getSimbolo() : ' ';
            ecra.escrever(MARGEM_TOPO_GRELHA + linha, MARGEM_ESQ_GRELHA + coluna, simbolo);
        }
    }
}

void Simulador::desenharPainel(int colunaPainel) {
    int colunaTexto = colunaPainel + MARGEM_LATERAL_PAINEL;
    int larguraUtil = LARGURA_PAINEL - (2 * MARGEM_LATERAL_PAINEL);

    ecra.escrever(1, colunaTexto, "Instante: " + std::to_string(fabrica.getInstante()));
    ecra.escrever(2, colunaTexto, "Creditos: " + std::to_string(fabrica.getCreditos()));
    ecra.escrever(3, colunaTexto, "Maquinas: " + std::to_string(fabrica.getNumMaquinas()));
    ecra.escrever(4, colunaTexto, "Engenheiros: 0");
    ecra.escrever(6, colunaTexto, "No ultimo instante:");
    ecra.escrever(7, colunaTexto, ultimaMensagem, larguraUtil);
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

void Simulador::atualizarEcra() {
    desenharFabrica();
    ecra.mostrar();
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

    if (cmd->requerFabrica() && fabrica.getLinhas() == 0) {
        delete cmd;
        ultimaMensagem = "Fabrica nao criada";
        return "Erro: a fabrica ainda nao foi criada. Use 'fabrica' ou 'carrega' primeiro.";
    }

    string resultado = cmd->executar(fabrica, *this);
    delete cmd;
    ultimaMensagem = extrairResumoPainel(resultado);
    return resultado;
}

void Simulador::parar() noexcept {
    emExecucao = false;
}

void Simulador::executar() {
    emExecucao = true;
    atualizarEcra();

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

        if (emExecucao) {
            atualizarEcra();
        }

        if (!resultado.empty()) {
            cout << resultado << '\n';
        }
    }
}