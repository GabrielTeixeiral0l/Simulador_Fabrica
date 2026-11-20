#include "Fabrica.h"
#include "terreno/Solo.h"
#include "terreno/Cratera.h"
#include "terreno/Deposito.h"
#include <fstream>
#include <random>

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
    } while (grelha[linha][coluna] != nullptr && !grelha[linha][coluna]->podeConstruir());
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
        int qtd = gerarNumeroAleatorio(Settings::deposito_quantidade_min, Settings::deposito_quantidade_max);
        delete grelha[linha][coluna];
        grelha[linha][coluna] = new Deposito(simbolo, nome, qtd);
    }
}

bool Fabrica::parseCoordenadas(const string& coord, int& linha, int& coluna) noexcept {
    if (coord.length() != 2) return false;
    char l = coord[0], c = coord[1];
    if (!((l >= 'a' && l <= 'z') || (l >= 'A' && l <= 'Z'))) return false;
    if (!((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))) return false;
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
            int qtd = gerarNumeroAleatorio(Settings::deposito_quantidade_min, Settings::deposito_quantidade_max);

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

bool Fabrica::comprarMaquina(const string& tipo, const string& coord, char dir) {
    Terreno* terreno = obterTerrenoPorCoord(coord);
    if (terreno == nullptr || !terreno->podeConstruir()) {
        return false;
    }

    Maquina* novaMaquina = Maquina::criar(tipo, Maquina::charParaOrientacao(dir));
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

    Maquina* maq = terreno->removerMaquina();
    if (maq == nullptr) {
        return false;
    }

    creditos += (maq->getCusto() * Settings::maquina_percentagem_venda) / 100;
    delete maq;
    return true;
}

bool Fabrica::rodarMaquina(const string& coord, char dir) {
    if (dir != 'c' && dir != 'b' && dir != 'e' && dir != 'd') {
        return false;
    }
    Terreno* terreno = obterTerrenoPorCoord(coord);
    if (terreno == nullptr || terreno->getMaquina() == nullptr) {
        return false;
    }
    terreno->getMaquina()->setOrientacao(Maquina::charParaOrientacao(dir));
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
                if (grelha[l][c] != nullptr) {
                    Maquina* maq = grelha[l][c]->getMaquina();
                    if (maq != nullptr && maq->isAtivo()) {
                        maq->atuar(*this, l, c);
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

    string pos;
    pos += static_cast<char>('a' + linha);
    pos += static_cast<char>('a' + coluna);

    if (grelha[linha][coluna] == nullptr) {
        return "Posicao " + pos + ": Vazia";
    }

    const Maquina* maq = grelha[linha][coluna]->getMaquina();
    if (maq != nullptr) {
        return "Posicao " + pos + ": " + grelha[linha][coluna]->getDescricao() + " [ID: " + std::to_string(maq->getId()) + "]";
    }

    return "Posicao " + pos + ": " + grelha[linha][coluna]->getDescricao();
}

string Fabrica::getInfoPosicao(const string& coordenadas) const {
    int l, c;
    if (!parseCoordenadas(coordenadas, l, c)) {
        return "Coordenadas invalidas (devem ter 2 letras, ex: ce)";
    }
    return getInfoPosicao(l, c);
}

int Fabrica::getLinhas() const noexcept { return linhas; }
int Fabrica::getColunas() const noexcept { return colunas; }
int Fabrica::getCreditos() const noexcept { return creditos; }
int Fabrica::getInstante() const noexcept { return instante; }

int Fabrica::getNumMaquinas() const noexcept {
    int total = 0;
    for (int l = 0; l < linhas; ++l) {
        for (int c = 0; c < colunas; ++c) {
            if (grelha[l][c] != nullptr && grelha[l][c]->getMaquina() != nullptr) {
                ++total;
            }
        }
    }
    return total;
}

const Terreno* Fabrica::getTerreno(int linha, int coluna) const noexcept {
    return estaDentroDosLimites(linha, coluna) ? grelha[linha][coluna] : nullptr;
}

Terreno* Fabrica::getTerreno(int linha, int coluna) noexcept {
    return estaDentroDosLimites(linha, coluna) ? grelha[linha][coluna] : nullptr;
}

bool Fabrica::alterarEstadoMaquina(int id, bool ativo) noexcept {
    for (int l = 0; l < linhas; ++l) {
        for (int c = 0; c < colunas; ++c) {
            if (grelha[l][c] != nullptr && grelha[l][c]->getMaquina() != nullptr && grelha[l][c]->getMaquina()->getId() == id) {
                grelha[l][c]->getMaquina()->setAtivo(ativo);
                return true;
            }
        }
    }
    return false;
}

bool Fabrica::ativarMaquina(int id) noexcept {
    return alterarEstadoMaquina(id, true);
}

bool Fabrica::desativarMaquina(int id) noexcept {
    return alterarEstadoMaquina(id, false);
}

void Fabrica::adicionarCreditos(int valor) noexcept {
    if (valor > 0) creditos += valor;
}

bool Fabrica::substituirPorSolo(int linha, int coluna) {
    if (!estaDentroDosLimites(linha, coluna) || grelha[linha][coluna] == nullptr) return false;
    Maquina* maq = grelha[linha][coluna]->removerMaquina();
    delete grelha[linha][coluna];
    grelha[linha][coluna] = new Solo();
    if (maq != nullptr) grelha[linha][coluna]->colocarMaquina(maq);
    return true;
}

void Fabrica::getPosicaoAdjacente(int linha, int coluna, const Orientacao& dir, int& destLinha, int& destColuna) noexcept {
    destLinha = linha + dir.getPassoLinha();
    destColuna = coluna + dir.getPassoColuna();
}

string Fabrica::getInfoMaquinas() const {
    string res;
    for (int l = 0; l < linhas; ++l) {
        for (int c = 0; c < colunas; ++c) {
            if (grelha[l][c] != nullptr && grelha[l][c]->getMaquina() != nullptr) {
                if (!res.empty()) res += '\n';
                res += getInfoPosicao(l, c);
            }
        }
    }
    return res.empty() ? "Nenhuma maquina na fabrica" : res;
}
