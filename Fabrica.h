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
    Terreno grelha[Settings::fabrica_max_linhas][Settings::fabrica_max_colunas];

    void limparGrelha() noexcept;
    bool estaDentroDosLimites(int linha, int coluna) const noexcept;
    static int gerarNumeroAleatorio(int min, int max);
    void sortearPosicaoLivre(int& linha, int& coluna) const;
    void criarCrateras(int numCrateras);
    void criarDepositos(int numDepositos, const std::string& nome, char simbolo);
    void desenharRegua(Ecra& ecra) const noexcept;
    void desenharPainel(Ecra& ecra) const;

public:
    explicit Fabrica(int numLinhas = Settings::fabrica_max_linhas, int numColunas = Settings::fabrica_max_colunas);
    ~Fabrica() = default;

    bool gerarAleatoria(int numLinhas, int numColunas);
    bool carregarFicheiro(const std::string& nomeFicheiro);
    void desenhar(Ecra& ecra) const;

    std::string getInfoPosicao(int linha, int coluna) const;
    std::string getInfoPosicao(const std::string& coordenadas) const;

    int getLinhas() const noexcept;
    int getColunas() const noexcept;
    int getCreditos() const noexcept;
    int getInstante() const noexcept;
    const Terreno* getTerreno(int linha, int coluna) const noexcept;
};

#endif // SIMULADOR_FABRICA_H
