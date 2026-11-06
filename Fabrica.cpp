#include "Fabrica.h"
#include <fstream>
#include <random>

Fabrica::Fabrica(int l, int c)
    : linhas(l), colunas(c), creditos(Settings::fabrica_creditos_iniciais), instante(1) {
    if (linhas < 1) {
        linhas = 1;
    } else if (linhas > Settings::fabrica_max_linhas) {
        linhas = Settings::fabrica_max_linhas;
    }

    if (colunas < 1) {
        colunas = 1;
    } else if (colunas > Settings::fabrica_max_colunas) {
        colunas = Settings::fabrica_max_colunas;
    }

    limparGrelha();
    gerarAleatoria(linhas, colunas);
}

void Fabrica::limparGrelha() noexcept {
    for (int l = 0; l < Settings::fabrica_max_linhas; ++l) {
        for (int c = 0; c < Settings::fabrica_max_colunas; ++c) {
            grelha[l][c] = Terreno::criarSolo();
        }
    }
}

bool Fabrica::estaDentroDosLimites(int l, int c) const noexcept {
    return l >= 0 && l < linhas && c >= 0 && c < colunas;
}

int Fabrica::gerarNumeroAleatorio(int min, int max) {
    static std::random_device rd;
    static std::default_random_engine gerador(rd());
    std::uniform_int_distribution<int> distribuicao(min, max);
    return distribuicao(gerador);
}

void Fabrica::sortearPosicaoLivre(int& l, int& c) const {
    do {
        l = gerarNumeroAleatorio(0, linhas - 1);
        c = gerarNumeroAleatorio(0, colunas - 1);
    } while (grelha[l][c].getSimbolo() != ' ');
}

void Fabrica::criarCrateras(int numCrateras) {
    int l, c;
    for (int i = 0; i < numCrateras; ++i) {
        sortearPosicaoLivre(l, c);
        grelha[l][c] = Terreno::criarCratera();
    }
}

void Fabrica::criarDepositos(int numDepositos, const std::string& nome, char simbolo) {
    int l, c;
    for (int i = 0; i < numDepositos; ++i) {
        sortearPosicaoLivre(l, c);
        int qtd = gerarNumeroAleatorio(Settings::deposito_quantidade_min, Settings::deposito_quantidade_max);
        grelha[l][c] = Terreno::criarDeposito(simbolo, nome, qtd);
    }
}

bool Fabrica::gerarAleatoria(int l, int c) {
    if (l < 1 || l > Settings::fabrica_max_linhas || c < 1 || c > Settings::fabrica_max_colunas) {
        return false;
    }

    limparGrelha();
    linhas = l;
    colunas = c;
    creditos = Settings::fabrica_creditos_iniciais;
    instante = 1;

    int totalCelulas = linhas * colunas;
    int celulasNecessarias = Settings::fabrica_num_crateras
                           + Settings::fabrica_num_depositos_ferro
                           + Settings::fabrica_num_depositos_silicio
                           + Settings::fabrica_num_depositos_gelo;

    if (totalCelulas >= celulasNecessarias) { // Para não entrar em loop infinito
        criarCrateras(Settings::fabrica_num_crateras);
        criarDepositos(Settings::fabrica_num_depositos_ferro, "Ferro", '%');
        criarDepositos(Settings::fabrica_num_depositos_silicio, "Silicio", '$');
        criarDepositos(Settings::fabrica_num_depositos_gelo, "Gelo", '~');
    }

    return true;
}

bool Fabrica::carregarFicheiro(const std::string& nomeFicheiro) {
    std::ifstream fich(nomeFicheiro);
    if (!fich.is_open()) {
        return false;
    }

    int l, c;
    if (!(fich >> l >> c)) {
        return false;
    }

    if (l < 1 || l > Settings::fabrica_max_linhas || c < 1 || c > Settings::fabrica_max_colunas) {
        return false;
    }

    Terreno temp[Settings::fabrica_max_linhas][Settings::fabrica_max_colunas];

    for (int i = 0; i < l; ++i) {
        std::string linhaMapa;
        fich >> linhaMapa;
        if (linhaMapa.length() != static_cast<size_t>(c)) {
            return false;
        }

        for (int j = 0; j < c; ++j) {
            char ch = linhaMapa[j];
            int qtd = gerarNumeroAleatorio(Settings::deposito_quantidade_min, Settings::deposito_quantidade_max);

            if (ch == '.') {
                temp[i][j] = Terreno::criarSolo();
            } else if (ch == '#') {
                temp[i][j] = Terreno::criarCratera();
            } else if (ch == '%') {
                temp[i][j] = Terreno::criarDeposito('%', "Ferro", qtd);
            } else if (ch == '$') {
                temp[i][j] = Terreno::criarDeposito('$', "Silicio", qtd);
            } else if (ch == '~') {
                temp[i][j] = Terreno::criarDeposito('~', "Gelo", qtd);
            } else {
                return false;
            }
        }
    }

    limparGrelha();
    linhas = l;
    colunas = c;
    creditos = Settings::fabrica_creditos_iniciais;
    instante = 1;

    for (int i = 0; i < linhas; ++i) {
        for (int j = 0; j < colunas; ++j) {
            grelha[i][j] = temp[i][j];
        }
    }

    return true;
}

void Fabrica::desenharRegua(Ecra& ecra) const noexcept {
    for (int c = 0; c < colunas; ++c) {
        char letraCol = 'A' + c;
        ecra.escrever(1, 3 + c, letraCol); // linha 1: a 0 é a da moldura, coluna 3 + c: 1 da moldura + 1 da coluna da regua das linhas + 1 onde começa + c que é a posição
    }

    for (int l = 0; l < linhas; ++l) {
        char letraLin = 'A' + l;
        ecra.escrever(2 + l, 1, letraLin); // Mesma lógica das colunas (2 em vez de 3 porque um caracter não é um quadrado, tem mais altura do que largura)
    }
}

void Fabrica::desenharPainel(Ecra& ecra) const {
    int colunaPainel = colunas + 6; // colunas + 3 (borda esquerda da moldura + Régua vertical + espaçamento + 1 (borda direita da fábrica) + 2 (espaçamento entre molduras)

    ecra.escrever(1, colunaPainel + 2, "Instante: " + std::to_string(instante)); // colunaPainel é onde fica o "|" da moldura + 2 (Espaçamento de 1 + onde vai escrever)
    ecra.escrever(2, colunaPainel + 2, "Creditos: " + std::to_string(creditos));

    // completar mais tarde
    ecra.escrever(3, colunaPainel + 2, "Maquinas: 0");
    ecra.escrever(4, colunaPainel + 2, "Engenheiros: 0");
    ecra.escrever(6, colunaPainel + 2, "No ultimo instante:");
    ecra.escrever(7, colunaPainel + 2, "Simulacao iniciada");
}

void Fabrica::desenhar(Ecra& ecra) const {
    ecra.limpar();

    int alturaFabrica = linhas + 3;  // +2 das bordas (topo/fundo) +1 da régua de colunas
    int larguraFabrica = colunas + 4; // +2 das bordas (esq/dir) +1 da régua +1 do espaço

    const int alturaPainel = 12;
    const int larguraPainel = 30;

    int alturaTotal = (alturaFabrica > alturaPainel) ? alturaFabrica : alturaPainel;
    int larguraTotal = larguraFabrica + 1 + larguraPainel;

    ecra.setDimensoes(alturaTotal, larguraTotal);

    // Mapa
    ecra.desenharMoldura(0, 0, alturaTotal, larguraFabrica);
    desenharRegua(ecra);

    for (int l = 0; l < linhas; ++l) {
        for (int c = 0; c < colunas; ++c) {
            ecra.escrever(2 + l, 3 + c, grelha[l][c].getSimbolo());
        }
    }

    // Painel
    int colunaPainel = larguraFabrica + 1;
    ecra.desenharMoldura(0, colunaPainel, alturaTotal, larguraPainel);
    desenharPainel(ecra);
}

std::string Fabrica::getInfoPosicao(int l, int c) const {
    if (!estaDentroDosLimites(l, c)) {
        return "Posicao fora dos limites da fabrica";
    }

    char lChar = 'a' + l;
    char cChar = 'a' + c;
    std::string pos;
    pos += lChar;
    pos += cChar;

    return "Posicao " + pos + ": " + grelha[l][c].getDescricao();
}

std::string Fabrica::getInfoPosicao(const std::string& coords) const {
    if (coords.length() != 2) {
        return "Coordenadas invalidas (devem ter 2 letras, ex: ce)";
    }

    char lChar = coords[0];
    char cChar = coords[1];

    int l = (lChar >= 'a' && lChar <= 'z') ? (lChar - 'a') : (lChar - 'A');
    int c = (cChar >= 'a' && cChar <= 'z') ? (cChar - 'a') : (cChar - 'A');

    return getInfoPosicao(l, c);
}

int Fabrica::getLinhas() const noexcept {
    return linhas;
}

int Fabrica::getColunas() const noexcept {
    return colunas;
}

int Fabrica::getCreditos() const noexcept {
    return creditos;
}

int Fabrica::getInstante() const noexcept {
    return instante;
}

const Terreno* Fabrica::getTerreno(int l, int c) const noexcept {
    if (estaDentroDosLimites(l, c)) {
        return &grelha[l][c];
    }
    return nullptr;
}
