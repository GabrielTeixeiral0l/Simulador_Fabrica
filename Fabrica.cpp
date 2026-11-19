#include "Fabrica.h"
#include "Solo.h"
#include "Cratera.h"
#include "Deposito.h"
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

    inicializarGrelha();
    gerarAleatoria(linhas, colunas);
}

Fabrica::~Fabrica() {
    libertarGrelha();
}

Fabrica::Fabrica(const Fabrica& outra)
    : linhas(outra.linhas), colunas(outra.colunas), creditos(outra.creditos), instante(outra.instante) {
    inicializarGrelha();
    copiarDe(outra);
}

Fabrica& Fabrica::operator=(const Fabrica& outra) {
    if (this != &outra) {
        libertarGrelha();
        linhas = outra.linhas;
        colunas = outra.colunas;
        creditos = outra.creditos;
        instante = outra.instante;
        copiarDe(outra);
    }
    return *this;
}

void Fabrica::inicializarGrelha() noexcept {
    for (int l = 0; l < Settings::fabrica_max_linhas; ++l) {
        for (int c = 0; c < Settings::fabrica_max_colunas; ++c) {
            grelha[l][c] = nullptr;
        }
    }
}

void Fabrica::libertarGrelha() noexcept {
    for (int l = 0; l < Settings::fabrica_max_linhas; ++l) {
        for (int c = 0; c < Settings::fabrica_max_colunas; ++c) {
            delete grelha[l][c];
            grelha[l][c] = nullptr;
        }
    }
}

void Fabrica::copiarDe(const Fabrica& outra) {
    for (int l = 0; l < Settings::fabrica_max_linhas; ++l) {
        for (int c = 0; c < Settings::fabrica_max_colunas; ++c) {
            if (outra.grelha[l][c] != nullptr) {
                grelha[l][c] = outra.grelha[l][c]->clone();
            } else {
                grelha[l][c] = nullptr;
            }
        }
    }
}

void Fabrica::limparGrelha() {
    for (int l = 0; l < Settings::fabrica_max_linhas; ++l) {
        for (int c = 0; c < Settings::fabrica_max_colunas; ++c) {
            delete grelha[l][c];
            grelha[l][c] = new Solo();
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
    } while (grelha[linha][coluna] != nullptr && grelha[linha][coluna]->getSimbolo() != ' ');
}

void Fabrica::criarCrateras(int numCrateras) {
    int linha, coluna;
    for (int i = 0; i < numCrateras; ++i) {
        sortearPosicaoLivre(linha, coluna);
        delete grelha[linha][coluna];
        grelha[linha][coluna] = new Cratera();
    }
}

void Fabrica::criarDepositos(int numDepositos, const std::string& nome, char simbolo) {
    int linha, coluna;
    for (int i = 0; i < numDepositos; ++i) {
        sortearPosicaoLivre(linha, coluna);
        int qtd = gerarNumeroAleatorio(Settings::deposito_quantidade_min, Settings::deposito_quantidade_max);
        delete grelha[linha][coluna];
        grelha[linha][coluna] = new Deposito(simbolo, nome, qtd);
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

    if (totalCelulas >= celulasNecessarias) {
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

    int linhasFich, colunasFich;
    if (!(fich >> linhasFich >> colunasFich)) {
        return false;
    }

    if (linhasFich < 1 || linhasFich > Settings::fabrica_max_linhas || colunasFich < 1 || colunasFich > Settings::fabrica_max_colunas) {
        return false;
    }

    Terreno* temp[Settings::fabrica_max_linhas][Settings::fabrica_max_colunas];
    for (int i = 0; i < Settings::fabrica_max_linhas; ++i) {
        for (int j = 0; j < Settings::fabrica_max_colunas; ++j) {
            temp[i][j] = nullptr;
        }
    }

    auto limparTemp = [&]() {
        for (int i = 0; i < Settings::fabrica_max_linhas; ++i) {
            for (int j = 0; j < Settings::fabrica_max_colunas; ++j) {
                delete temp[i][j];
                temp[i][j] = nullptr;
            }
        }
    };

    for (int i = 0; i < linhasFich; ++i) {
        std::string linhaMapa;
        fich >> linhaMapa;
        if (static_cast<int>(linhaMapa.length()) != colunasFich) {
            limparTemp();
            return false;
        }

        for (int j = 0; j < colunasFich; ++j) {
            char ch = linhaMapa[j];
            int qtd = gerarNumeroAleatorio(Settings::deposito_quantidade_min, Settings::deposito_quantidade_max);

            if (ch == '.') {
                temp[i][j] = new Solo();
            } else if (ch == '#') {
                temp[i][j] = new Cratera();
            } else if (ch == '%') {
                temp[i][j] = new Deposito('%', "Ferro", qtd);
            } else if (ch == '$') {
                temp[i][j] = new Deposito('$', "Silicio", qtd);
            } else if (ch == '~') {
                temp[i][j] = new Deposito('~', "Gelo", qtd);
            } else {
                limparTemp();
                return false;
            }
        }
    }

    limparGrelha();
    linhas = linhasFich;
    colunas = colunasFich;
    creditos = Settings::fabrica_creditos_iniciais;
    instante = 1;

    for (int i = 0; i < linhas; ++i) {
        for (int j = 0; j < colunas; ++j) {
            delete grelha[i][j];
            grelha[i][j] = temp[i][j];
            temp[i][j] = nullptr;
        }
    }

    limparTemp();
    return true;
}

std::string Fabrica::getInfoPosicao(int linha, int coluna) const {
    if (!estaDentroDosLimites(linha, coluna)) {
        return "Posicao fora dos limites da fabrica";
    }

    char lChar = 'a' + linha;
    char cChar = 'a' + coluna;
    std::string pos;
    pos += lChar;
    pos += cChar;

    if (grelha[linha][coluna] == nullptr) {
        return "Posicao " + pos + ": Vazia";
    }

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
