#include "Fabrica.h"
#include "terreno/Solo.h"
#include "terreno/Cratera.h"
#include "terreno/Deposito.h"
#include "FerramentasAuxiliares.h"
#include <fstream>

using std::string;

Fabrica::Fabrica() noexcept
    : linhas(0), colunas(0), creditos(Settings::fabrica_creditos_iniciais), instante(1) {
}

Fabrica::~Fabrica() {
    libertarMatrizTerreno(grelha);
}

void Fabrica::libertarMatrizTerreno(Terreno* matriz[Settings::fabrica_max_linhas][Settings::fabrica_max_colunas]) noexcept {
    for (int l = 0; l < Settings::fabrica_max_linhas; ++l) {
        for (int c = 0; c < Settings::fabrica_max_colunas; ++c) {
            delete matriz[l][c];
            matriz[l][c] = nullptr;
        }
    }
}

void Fabrica::limparGrelha() {
    libertarMatrizTerreno(grelha);
    for (int l = 0; l < linhas; ++l) {
        for (int c = 0; c < colunas; ++c) {
            grelha[l][c] = new Solo();
        }
    }
}

bool Fabrica::estaDentroDosLimites(int linha, int coluna) const noexcept {
    return linha >= 0 && linha < linhas && coluna >= 0 && coluna < colunas;
}

void Fabrica::sortearPosicaoLivre(int& linha, int& coluna) const {
    do {
        linha = FerramentasAuxiliares::gerarInteiro(0, linhas - 1);
        coluna = FerramentasAuxiliares::gerarInteiro(0, colunas - 1);
    } while (grelha[linha][coluna] != nullptr && !grelha[linha][coluna]->isSolo());
}

void Fabrica::criarCrateras(int numCrateras) {
    int linha, coluna;
    for (int i = 0; i < numCrateras; ++i) {
        sortearPosicaoLivre(linha, coluna);
        delete grelha[linha][coluna];
        grelha[linha][coluna] = new Cratera();
    }
}

void Fabrica::criarDepositos(int numDepositos, const string& nome, char simbolo) {
    int linha, coluna;
    for (int i = 0; i < numDepositos; ++i) {
        sortearPosicaoLivre(linha, coluna);
        int qtd = FerramentasAuxiliares::gerarInteiro(Settings::deposito_quantidade_min, Settings::deposito_quantidade_max);
        delete grelha[linha][coluna];
        grelha[linha][coluna] = new Deposito(simbolo, nome, qtd);
    }
}

bool Fabrica::parseCoordenadas(const string& coord, int& linha, int& coluna) noexcept {
    if (!FerramentasAuxiliares::isCoordenada(coord)) {
        return false;
    }
    char l = coord[0], c = coord[1];
    linha = (l >= 'a' && l <= 'z') ? (l - 'a') : (l - 'A');
    coluna = (c >= 'a' && c <= 'z') ? (c - 'a') : (c - 'A');
    return true;
}

Terreno* Fabrica::obterTerrenoPorCoord(const string& coord) noexcept {
    int l, c;
    if (!parseCoordenadas(coord, l, c) || !estaDentroDosLimites(l, c)) {
        return nullptr;
    }
    return grelha[l][c];
}

bool Fabrica::gerarAleatoria(int numLinhas, int numColunas) {
    if (numLinhas < 1 || numLinhas > Settings::fabrica_max_linhas || numColunas < 1 || numColunas > Settings::fabrica_max_colunas) {
        return false;
    }

    linhas = numLinhas;
    colunas = numColunas;
    limparGrelha();
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

bool Fabrica::carregarFicheiro(const string& nomeFicheiro) {
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

    Terreno* temp[Settings::fabrica_max_linhas][Settings::fabrica_max_colunas]{};

    for (int i = 0; i < linhasFich; ++i) {
        string linhaMapa;
        fich >> linhaMapa;
        if (static_cast<int>(linhaMapa.length()) != colunasFich) {
            libertarMatrizTerreno(temp);
            return false;
        }

        for (int j = 0; j < colunasFich; ++j) {
            char ch = linhaMapa[j];
            int qtd = FerramentasAuxiliares::gerarInteiro(Settings::deposito_quantidade_min, Settings::deposito_quantidade_max);

            if (ch == '.') temp[i][j] = new Solo();
            else if (ch == '#') temp[i][j] = new Cratera();
            else if (ch == '%') temp[i][j] = new Deposito('%', "Ferro", qtd);
            else if (ch == '$') temp[i][j] = new Deposito('$', "Silicio", qtd);
            else if (ch == '~') temp[i][j] = new Deposito('~', "Gelo", qtd);
            else {
                libertarMatrizTerreno(temp);
                return false;
            }
        }
    }

    libertarMatrizTerreno(grelha);
    linhas = linhasFich;
    colunas = colunasFich;
    creditos = Settings::fabrica_creditos_iniciais;
    instante = 1;

    for (int i = 0; i < linhas; ++i) {
        for (int j = 0; j < colunas; ++j) {
            grelha[i][j] = temp[i][j];
            temp[i][j] = nullptr;
        }
    }

    return true;
}

bool Fabrica::comprarMaquina(const string& tipo, const string& coord, char direcao) {
    Terreno* terreno = obterTerrenoPorCoord(coord);
    if (terreno == nullptr || !terreno->podeConstruir()) {
        return false;
    }

    Maquina* novaMaquina = Maquina::criar(tipo, Maquina::charParaOrientacao(direcao));
    if (novaMaquina == nullptr) {
        return false;
    }

    if (creditos < novaMaquina->getCusto()) {
        delete novaMaquina;
        return false;
    }

    creditos -= novaMaquina->getCusto();
    terreno->colocarMaquina(novaMaquina);
    return true;
}

bool Fabrica::venderMaquina(const string& coord) {
    Terreno* terreno = obterTerrenoPorCoord(coord);
    if (terreno == nullptr) {
        return false;
    }

    Maquina* maquina = terreno->removerMaquina();
    if (maquina == nullptr) {
        return false;
    }

    creditos += (maquina->getCusto() * Settings::maquina_percentagem_venda) / 100;
    delete maquina;
    return true;
}

bool Fabrica::rodarMaquina(const string& coord, char direcao) {
    if (direcao != 'c' && direcao != 'b' && direcao != 'e' && direcao != 'd') {
        return false;
    }

    Terreno* terreno = obterTerrenoPorCoord(coord);
    Maquina* maquina = (terreno != nullptr) ? terreno->getMaquina() : nullptr;
    if (maquina == nullptr) {
        return false;
    }

    maquina->setOrientacao(Maquina::charParaOrientacao(direcao));
    return true;
}

void Fabrica::avancarInstante(int numInstantes) {
    if (numInstantes < 1) {
        return;
    }

    for (int passo = 0; passo < numInstantes; ++passo) {
        ++instante;
        for (int linha = 0; linha < linhas; ++linha) {
            for (int coluna = 0; coluna < colunas; ++coluna) {
                if (grelha[linha][coluna] != nullptr) {
                    Maquina* maquina = grelha[linha][coluna]->getMaquina();
                    if (maquina != nullptr && maquina->isAtivo()) {
                        maquina->operar(*this, linha, coluna);
                    }
                }
            }
        }
    }
}

string Fabrica::getInfoPosicao(int linha, int coluna) const {
    if (!estaDentroDosLimites(linha, coluna)) {
        return "Posicao fora dos limites da fabrica";
    }

    string rotuloPosicao;
    if (linha >= 0 && linha <= 25 && coluna >= 0 && coluna <= 25) {
        rotuloPosicao += static_cast<char>('a' + linha);
        rotuloPosicao += static_cast<char>('a' + coluna);
    } else {
        rotuloPosicao = "(" + std::to_string(linha) + "," + std::to_string(coluna) + ")";
    }

    const Terreno* terreno = grelha[linha][coluna];
    if (terreno == nullptr) {
        return "Posicao " + rotuloPosicao + ": Vazia";
    }

    string descricao = terreno->getDescricao();
    const Maquina* maquina = terreno->getMaquina();
    if (maquina != nullptr) {
        descricao += " [ID: " + std::to_string(maquina->getId()) + "]";
    }

    return "Posicao " + rotuloPosicao + ": " + descricao;
}

string Fabrica::getInfoPosicao(const string& coordenadas) const {
    int linha = 0;
    int coluna = 0;
    if (!parseCoordenadas(coordenadas, linha, coluna)) {
        return "Coordenadas invalidas (devem ter 2 letras, ex: ce)";
    }
    return getInfoPosicao(linha, coluna);
}

int Fabrica::getLinhas() const noexcept { return linhas; }
int Fabrica::getColunas() const noexcept { return colunas; }
int Fabrica::getCreditos() const noexcept { return creditos; }
int Fabrica::getInstante() const noexcept { return instante; }

int Fabrica::getNumMaquinas() const noexcept {
    int numMaquinas = 0;
    for (int linha = 0; linha < linhas; ++linha) {
        for (int coluna = 0; coluna < colunas; ++coluna) {
            if (grelha[linha][coluna] != nullptr && grelha[linha][coluna]->getMaquina() != nullptr) {
                ++numMaquinas;
            }
        }
    }
    return numMaquinas;
}

const Terreno* Fabrica::getTerreno(int linha, int coluna) const noexcept {
    return estaDentroDosLimites(linha, coluna) ? grelha[linha][coluna] : nullptr;
}

Terreno* Fabrica::getTerreno(int linha, int coluna) noexcept {
    return estaDentroDosLimites(linha, coluna) ? grelha[linha][coluna] : nullptr;
}

void Fabrica::adicionarCreditos(int valor) noexcept {
    creditos += valor;
    if (creditos < 0) {
        creditos = 0;
    }
}

void Fabrica::getPosicaoAdjacente(int linha, int coluna, const Orientacao& orientacao, int& linhaDestino, int& colunaDestino) noexcept {
    linhaDestino = linha + orientacao.getPassoLinha();
    colunaDestino = coluna + orientacao.getPassoColuna();
}

string Fabrica::getInfoMaquinas() const {
    string resultado;
    for (int linha = 0; linha < linhas; ++linha) {
        for (int coluna = 0; coluna < colunas; ++coluna) {
            if (grelha[linha][coluna] != nullptr && grelha[linha][coluna]->getMaquina() != nullptr) {
                if (!resultado.empty()) {
                    resultado += '\n';
                }
                resultado += getInfoPosicao(linha, coluna);
            }
        }
    }
    return resultado.empty() ? "Nenhuma maquina na fabrica" : resultado;
}