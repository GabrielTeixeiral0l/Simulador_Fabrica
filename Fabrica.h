#ifndef SIMULADOR_FABRICA_H
#define SIMULADOR_FABRICA_H

#include <string>
#include "Ecra.h"
#include "Settings.h"
#include "Terreno.h"

class Fabrica {
    int linhas;
    int colunas;
    int creditos;
    int instante;
    Terreno* grelha[Settings::fabrica_max_linhas][Settings::fabrica_max_colunas];

    void limparGrelha() noexcept;
    bool estaDentroDosLimites(int l, int c) const noexcept;
    int gerarNumeroAleatorio(int min, int max) const;
    void sortearPosicaoLivre(int& r, int& c) const;
    void criarCrateras(int numCrateras);
    void criarDepositos(int numDepositos, const std::string& nome, char simbolo);
    void desenharRegua(Ecra& ecra) const noexcept;
    void desenharPainel(Ecra& ecra) const;

public:
    explicit Fabrica(int l = Settings::fabrica_max_linhas, int c = Settings::fabrica_max_colunas);
    ~Fabrica();

    bool gerarAleatoria(int l, int c);
    bool carregarFicheiro(const std::string& nomeFicheiro);
    void desenhar(Ecra& ecra) const;

    std::string getInfoPosicao(int l, int c) const;
    std::string getInfoPosicao(const std::string& coords) const;

    int getLinhas() const noexcept;
    int getColunas() const noexcept;
    int getCreditos() const noexcept;
    int getInstante() const noexcept;
    const Terreno* getTerreno(int l, int c) const noexcept;
};

#endif // SIMULADOR_FABRICA_H
