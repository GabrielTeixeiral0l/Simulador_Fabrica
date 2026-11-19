#ifndef SIMULADOR_FABRICA_H
#define SIMULADOR_FABRICA_H

#include <string>
#include "Settings.h"
#include "Terreno.h"

class Fabrica {
private:
    int linhas;
    int colunas;
    int creditos;
    int instante;
    Terreno* grelha[Settings::fabrica_max_linhas][Settings::fabrica_max_colunas];

    void inicializarGrelha() noexcept;
    void libertarGrelha() noexcept;
    void copiarDe(const Fabrica& outra);
    void limparGrelha();
    bool estaDentroDosLimites(int linha, int coluna) const noexcept;
    static int gerarNumeroAleatorio(int min, int max);
    void sortearPosicaoLivre(int& linha, int& coluna) const;
    void criarCrateras(int numCrateras);
    void criarDepositos(int numDepositos, const std::string& nome, char simbolo);

public:
    explicit Fabrica(int numLinhas = Settings::fabrica_max_linhas, int numColunas = Settings::fabrica_max_colunas);
    ~Fabrica();
    Fabrica(const Fabrica& outra);
    Fabrica& operator=(const Fabrica& outra);

    bool gerarAleatoria(int numLinhas, int numColunas);
    bool carregarFicheiro(const std::string& nomeFicheiro);

    std::string getInfoPosicao(int linha, int coluna) const;
    std::string getInfoPosicao(const std::string& coordenadas) const;

    int getLinhas() const noexcept;
    int getColunas() const noexcept;
    int getCreditos() const noexcept;
    int getInstante() const noexcept;
    const Terreno* getTerreno(int linha, int coluna) const noexcept;
};

#endif // SIMULADOR_FABRICA_H
