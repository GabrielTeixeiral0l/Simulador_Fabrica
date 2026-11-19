#ifndef SIMULADOR_FABRICA_H
#define SIMULADOR_FABRICA_H

#include <string>
#include "Settings.h"
#include "terreno/Terreno.h"
#include "Armazem.h"
#include "maquinas/Maquina.h"

class Fabrica {
    int linhas;
    int colunas;
    int creditos;
    int instante;
    Terreno* grelha[Settings::fabrica_max_linhas][Settings::fabrica_max_colunas];
    Armazem armazem;

    void inicializarGrelha() noexcept;
    void libertarGrelha() noexcept;
    void limparGrelha();
    bool estaDentroDosLimites(int linha, int coluna) const noexcept;
    static int gerarNumeroAleatorio(int min, int max);
    void sortearPosicaoLivre(int& linha, int& coluna) const;
    void criarCrateras(int numCrateras);
    void criarDepositos(int numDepositos, const std::string& nome, char simbolo);
    static bool parseCoordenadas(const std::string& coord, int& linha, int& coluna) noexcept;

public:
    explicit Fabrica(int numLinhas = Settings::fabrica_max_linhas, int numColunas = Settings::fabrica_max_colunas);
    ~Fabrica();
    Fabrica(const Fabrica&) = delete;
    Fabrica& operator=(const Fabrica&) = delete;

    bool gerarAleatoria(int numLinhas, int numColunas);
    bool carregarFicheiro(const std::string& nomeFicheiro);

    bool comprarMaquina(const std::string& tipo, const std::string& coord, char dir = 'c');
    bool venderMaquina(const std::string& coord);
    bool rodarMaquina(const std::string& coord);
    void avancarInstante(int n = 1);

    std::string getInfoPosicao(int linha, int coluna) const;
    std::string getInfoPosicao(const std::string& coordenadas) const;

    int getLinhas() const noexcept;
    int getColunas() const noexcept;
    int getCreditos() const noexcept;
    int getInstante() const noexcept;
    const Terreno* getTerreno(int linha, int coluna) const noexcept;
    Terreno* getTerreno(int linha, int coluna) noexcept;

    const Armazem& getSilo() const noexcept;
    Armazem& getSilo() noexcept;
};

#endif // SIMULADOR_FABRICA_H
