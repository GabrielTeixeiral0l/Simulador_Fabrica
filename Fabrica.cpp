#include "Fabrica.h"
#include "terreno/Solo.h"
#include "terreno/Cratera.h"
#include "terreno/Deposito.h"
#include "maquinas/Perfuradora.h"
#include "maquinas/Transportador.h"
#include "maquinas/Refinaria.h"
#include "maquinas/Oficina.h"
#include "maquinas/Silo.h"
#include "maquinas/Lancador.h"
#include <fstream>
#include <random>

Fabrica::Fabrica() noexcept
    : linhas(0), colunas(0), creditos(Settings::fabrica_creditos_iniciais), instante(1), armazem() {
    inicializarGrelha();
}

Fabrica::~Fabrica() {
    libertarGrelha();
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

void Fabrica::limparGrelha() {
    for (int l = 0; l < Settings::fabrica_max_linhas; ++l) {
        for (int c = 0; c < Settings::fabrica_max_colunas; ++c) {
            delete grelha[l][c];
            grelha[l][c] = new Solo();
        }
    }
}

void Fabrica::limparGrelhaTemp(Terreno* temp[Settings::fabrica_max_linhas][Settings::fabrica_max_colunas]) noexcept {
    for (int i=0;i<Settings::fabrica_max_linhas;++i) for (int j=0;j<Settings::fabrica_max_colunas;++j) { delete temp[i][j]; temp[i][j]=nullptr; }
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

bool Fabrica::sortearPosicaoLivre(int& linha, int& coluna) const {
    for (int t=0;t<linhas*colunas*4;++t) { int l=gerarNumeroAleatorio(0,linhas-1), c=gerarNumeroAleatorio(0,colunas-1); if (!grelha[l][c] || grelha[l][c]->getSimbolo()==' ') { linha=l; coluna=c; return true; } }
    for (int l=0;l<linhas;++l) for (int c=0;c<colunas;++c) if (!grelha[l][c] || grelha[l][c]->getSimbolo()==' ') { linha=l; coluna=c; return true; }
    return false;
}

void Fabrica::criarCrateras(int numCrateras) {
    int linha, coluna;
    for (int i = 0; i < numCrateras; ++i) {
        if (!sortearPosicaoLivre(linha, coluna)) break;
        delete grelha[linha][coluna];
        grelha[linha][coluna] = new Cratera();
    }
}

void Fabrica::criarDepositos(int numDepositos, const std::string& nome, char simbolo) {
    int linha, coluna;
    for (int i = 0; i < numDepositos; ++i) {
        if (!sortearPosicaoLivre(linha, coluna)) break;
        int qtd = gerarNumeroAleatorio(Settings::deposito_quantidade_min, Settings::deposito_quantidade_max);
        delete grelha[linha][coluna];
        grelha[linha][coluna] = new Deposito(simbolo, nome, qtd);
    }
}

bool Fabrica::parseCoordenadas(const std::string& coord, int& linha, int& coluna) noexcept {
    if (coord.length() != 2) {
        return false;
    }
    char lChar = coord[0];
    char cChar = coord[1];
    linha = (lChar >= 'a' && lChar <= 'z') ? (lChar - 'a') : (lChar - 'A');
    coluna = (cChar >= 'a' && cChar <= 'z') ? (cChar - 'a') : (cChar - 'A');
    return true;
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

    for (int i = 0; i < linhasFich; ++i) {
        std::string linhaMapa;
        fich >> linhaMapa;
        if (static_cast<int>(linhaMapa.length()) != colunasFich) {
            limparGrelhaTemp(temp);
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
                limparGrelhaTemp(temp);
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

    limparGrelhaTemp(temp);
    return true;
}

bool Fabrica::comprarMaquina(const std::string& tipo, const std::string& coord, char dir) {
    int l, c;
    if (!parseCoordenadas(coord, l, c) || !estaDentroDosLimites(l, c)) {
        return false;
    }

    Solo* solo = dynamic_cast<Solo*>(grelha[l][c]);
    if (solo == nullptr || !solo->podeConstruir()) {
        return false;
    }

    Orientacao orientacao = Maquina::charParaOrientacao(dir);
    Maquina* novaMaquina = nullptr;

    if (tipo == "p" || tipo == "perfuradora" || tipo == "P") {
        novaMaquina = new Perfuradora(orientacao);
    } else if (tipo == "t" || tipo == "transportador" || tipo == "T") {
        novaMaquina = new Transportador(orientacao);
    } else if (tipo == "r" || tipo == "refinaria" || tipo == "R") {
        novaMaquina = new Refinaria(orientacao);
    } else if (tipo == "o" || tipo == "oficina" || tipo == "O") {
        novaMaquina = new Oficina(orientacao);
    } else if (tipo == "s" || tipo == "silo" || tipo == "S") {
        novaMaquina = new Silo(orientacao);
    } else if (tipo == "l" || tipo == "lancador" || tipo == "L") {
        novaMaquina = new Lancador(orientacao);
    } else {
        return false;
    }

    if (creditos < novaMaquina->getCusto()) {
        delete novaMaquina;
        return false;
    }

    creditos -= novaMaquina->getCusto();
    solo->colocarMaquina(novaMaquina);
    return true;
}

bool Fabrica::venderMaquina(const std::string& coord) {
    int l, c;
    if (!parseCoordenadas(coord, l, c) || !estaDentroDosLimites(l, c)) {
        return false;
    }

    Solo* solo = dynamic_cast<Solo*>(grelha[l][c]);
    if (solo == nullptr) {
        return false;
    }

    Maquina* maq = solo->removerMaquina();
    if (maq == nullptr) {
        return false;
    }

    int reembolso = (maq->getCusto() * Settings::maquina_percentagem_venda) / 100;
    creditos += reembolso;
    delete maq;
    return true;
}

bool Fabrica::rodarMaquina(const std::string& coord) {
    int l, c;
    if (!parseCoordenadas(coord, l, c) || !estaDentroDosLimites(l, c)) {
        return false;
    }

    Solo* solo = dynamic_cast<Solo*>(grelha[l][c]);
    if (solo == nullptr) {
        return false;
    }

    Maquina* maq = solo->getMaquina();
    if (maq == nullptr) {
        return false;
    }

    maq->rodar();
    return true;
}

void Fabrica::avancarInstante(int n) {
    if (n < 1) {
        return;
    }

    for (int passo = 0; passo < n; ++passo) {
        ++instante;
        for (int l = 0; l < linhas; ++l) {
            for (int c = 0; c < colunas; ++c) {
                Solo* solo = dynamic_cast<Solo*>(grelha[l][c]);
                if (solo != nullptr) {
                    Maquina* maq = solo->getMaquina();
                    if (maq != nullptr && maq->isAtivo()) {
                        maq->atuar(*this, l, c);
                    }
                }
            }
        }
    }
}

std::string Fabrica::getInfoPosicao(int linha, int coluna) const {
    if (!estaDentroDosLimites(linha, coluna)) {
        return "Posicao fora dos limites da fabrica";
    }

    char lChar = static_cast<char>('a' + linha);
    char cChar = static_cast<char>('a' + coluna);
    std::string pos;
    pos += lChar;
    pos += cChar;

    if (grelha[linha][coluna] == nullptr) {
        return "Posicao " + pos + ": Vazia";
    }

    const Solo* solo = dynamic_cast<const Solo*>(grelha[linha][coluna]);
    if (solo != nullptr && solo->getMaquina() != nullptr) {
        const Maquina* maq = solo->getMaquina();
        return "Posicao " + pos + ": Solo com " + maq->getDescricao() + " [ID: " + std::to_string(maq->getId()) + "]";
    }

    return "Posicao " + pos + ": " + grelha[linha][coluna]->getDescricao();
}

std::string Fabrica::getInfoPosicao(const std::string& coordenadas) const {
    int l, c;
    if (!parseCoordenadas(coordenadas, l, c)) {
        return "Coordenadas invalidas (devem ter 2 letras, ex: ce)";
    }
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

int Fabrica::getNumMaquinas() const noexcept {
    int total = 0;
    for (int l = 0; l < linhas; ++l) {
        for (int c = 0; c < colunas; ++c) {
            const Solo* solo = dynamic_cast<const Solo*>(grelha[l][c]);
            if (solo != nullptr && solo->getMaquina() != nullptr) {
                ++total;
            }
        }
    }
    return total;
}

const Terreno* Fabrica::getTerreno(int linha, int coluna) const noexcept {
    if (estaDentroDosLimites(linha, coluna)) {
        return grelha[linha][coluna];
    }
    return nullptr;
}

Terreno* Fabrica::getTerreno(int linha, int coluna) noexcept {
    if (estaDentroDosLimites(linha, coluna)) {
        return grelha[linha][coluna];
    }
    return nullptr;
}

const Armazem& Fabrica::getArmazem() const noexcept {
    return armazem;
}

Armazem& Fabrica::getArmazem() noexcept {
    return armazem;
}
