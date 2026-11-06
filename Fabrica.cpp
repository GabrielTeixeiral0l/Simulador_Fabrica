#include "Fabrica.h"
#include <fstream>
#include <random>

Fabrica::Fabrica(int numLinhas, int numColunas)
    : linhas(numLinhas), colunas(numColunas), creditos(Settings::fabrica_creditos_iniciais), instante(1) {
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

    for (int i = 0; i < Settings::fabrica_max_linhas; ++i) {
        for (int j = 0; j < Settings::fabrica_max_colunas; ++j) {
            grelha[i][j] = nullptr;
        }
    }

    gerarAleatoria(linhas, colunas);
}

Fabrica::~Fabrica() {
    limparGrelha();
}

void Fabrica::limparGrelha() noexcept {
    for (int l = 0; l < Settings::fabrica_max_linhas; ++l) {
        for (int c = 0; c < Settings::fabrica_max_colunas; ++c) {
            delete grelha[l][c];
            grelha[l][c] = nullptr;
        }
    }
}

bool Fabrica::estaDentroDosLimites(int linha, int coluna) const noexcept {
    return linha >= 0 && linha < linhas && coluna >= 0 && coluna < colunas;
}

int Fabrica::gerarNumeroAleatorio(int min, int max) {
    static std::random_device rd;
    static std::default_random_engine gerador(rd());
    std::uniform_int_distribution<int> distribuicao(min, max);
    return distribuicao(gerador);
}

void Fabrica::sortearPosicaoLivre(int& linha, int& coluna) const {
    do {
        linha = gerarNumeroAleatorio(0, linhas - 1);
        coluna = gerarNumeroAleatorio(0, colunas - 1);
    } while (grelha[linha][coluna] != nullptr);
}

void Fabrica::criarCrateras(int numCrateras) {
    int linha, coluna;
    for (int i = 0; i < numCrateras; ++i) {
        sortearPosicaoLivre(linha, coluna);
        grelha[linha][coluna] = new Cratera();
    }
}

void Fabrica::criarDepositos(int numDepositos, const std::string& nome, char simbolo) {
    int linha, coluna;
    for (int i = 0; i < numDepositos; ++i) {
        sortearPosicaoLivre(linha, coluna);
        int qtd = gerarNumeroAleatorio(Settings::deposito_quantidade_min, Settings::deposito_quantidade_max);
        grelha[linha][coluna] = new Deposito(nome, simbolo, qtd);
    }
}

bool Fabrica::gerarAleatoria(int numLinhas, int numColunas) {
    if (numLinhas < 1 || numLinhas > Settings::fabrica_max_linhas || numColunas < 1 || numColunas > Settings::fabrica_max_colunas) {
        return false;
    }

    limparGrelha();
    linhas = numLinhas;
    colunas = numColunas;
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

    for (int i = 0; i < linhas; ++i) {
        for (int j = 0; j < colunas; ++j) {
            if (grelha[i][j] == nullptr) {
                grelha[i][j] = new Solo();
            }
        }
    }

    return true;
}

bool Fabrica::carregarFicheiro(const std::string& nomeFicheiro) {
    std::ifstream fich(nomeFicheiro);
    if (!fich.is_open()) {
        return false;
    }

    int linhasFich, colunasFich;
    if (!(fich >> linhasFich >> colunasFich)) {
        return false;
    }

    if (linhasFich < 1 || linhasFich > Settings::fabrica_max_linhas || colunasFich < 1 || colunasFich > Settings::fabrica_max_colunas) {
        return false;
    }

    Terreno* temp[Settings::fabrica_max_linhas][Settings::fabrica_max_colunas];
    for (int i = 0; i < linhasFich; ++i) {
        for (int j = 0; j < colunasFich; ++j) {
            temp[i][j] = nullptr;
        }
    }

    bool sucesso = true;

    for (int i = 0; i < linhasFich && sucesso; ++i) {
        std::string linhaMapa;
        fich >> linhaMapa;
        if (linhaMapa.length() != static_cast<size_t>(colunasFich)) {
            sucesso = false;
            break;
        }

        for (int j = 0; j < colunasFich; ++j) {
            char ch = linhaMapa[j];
            int qtd = gerarNumeroAleatorio(Settings::deposito_quantidade_min, Settings::deposito_quantidade_max);

            if (ch == '.') {
                temp[i][j] = new Solo();
            } else if (ch == '#') {
                temp[i][j] = new Cratera();
            } else if (ch == '%') {
                temp[i][j] = new Deposito("Ferro", '%', qtd);
            } else if (ch == '$') {
                temp[i][j] = new Deposito("Silicio", '$', qtd);
            } else if (ch == '~') {
                temp[i][j] = new Deposito("Gelo", '~', qtd);
            } else {
                sucesso = false;
                break;
            }
        }
    }

    if (!sucesso) {
        for (int i = 0; i < linhasFich; ++i) {
            for (int j = 0; j < colunasFich; ++j) {
                delete temp[i][j];
            }
        }
        return false;
    }

    limparGrelha();
    linhas = linhasFich;
    colunas = colunasFich;
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
            if (grelha[l][c] != nullptr) {
                ecra.escrever(2 + l, 3 + c, grelha[l][c]->getSimbolo());
                // 2 + l: moldura + regua
                // 3 + c: moldura + regua + espaço
            }
        }
    }

    // Painel
    int colunaPainel = larguraFabrica + 1;
    ecra.desenharMoldura(0, colunaPainel, alturaTotal, larguraPainel);
    desenharPainel(ecra);
}

std::string Fabrica::getInfoPosicao(int linha, int coluna) const {
    if (!estaDentroDosLimites(linha, coluna) || grelha[linha][coluna] == nullptr) {
        return "Posicao fora dos limites da fabrica";
    }

    char lChar = 'a' + linha;
    char cChar = 'a' + coluna;
    std::string pos;
    pos += lChar;
    pos += cChar;

    return "Posicao " + pos + ": " + grelha[linha][coluna]->getDescricao();
}

std::string Fabrica::getInfoPosicao(const std::string& coordenadas) const {
    if (coordenadas.length() != 2) {
        return "Coordenadas invalidas (devem ter 2 letras, ex: ce)";
    }

    char lChar = coordenadas[0];
    char cChar = coordenadas[1];

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

const Terreno* Fabrica::getTerreno(int linha, int coluna) const noexcept {
    if (estaDentroDosLimites(linha, coluna)) {
        return grelha[linha][coluna];
    }
    return nullptr;
}
