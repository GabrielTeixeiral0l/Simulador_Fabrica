#ifndef SIMULADOR_FABRICA_H
#define SIMULADOR_FABRICA_H

#include <string>
#include "Settings.h"
#include "terreno/Terreno.h"
#include "maquinas/Maquina.h"

class Fabrica {
    int linhas;
    int colunas;
    int creditos;
    int instante;
    Terreno* grelha[Settings::fabrica_max_linhas][Settings::fabrica_max_colunas]{};

    static void libertarMatrizTerreno(Terreno* matriz[Settings::fabrica_max_linhas][Settings::fabrica_max_colunas]) noexcept;
    void limparGrelha();
    bool estaDentroDosLimites(int linha, int coluna) const noexcept;
    void sortearPosicaoLivre(int& linha, int& coluna) const;
    void criarCrateras(int numeroCrateras);
    void criarDepositos(int numeroDepositos, const std::string& nome, char simbolo);
    static bool parseCoordenadas(const std::string& coordenadas, int& linha, int& coluna) noexcept;
    Terreno* obterTerrenoPorCoord(const std::string& coordenadas) noexcept;

public:
    Fabrica() noexcept;
    ~Fabrica();
    Fabrica(const Fabrica&) = delete;
    Fabrica& operator=(const Fabrica&) = delete;

    bool gerarAleatoria(int numeroLinhas, int numeroColunas);
    bool carregarFicheiro(const std::string& nomeFicheiro);

    bool comprarMaquina(const std::string& tipoMaquina, const std::string& coordenadas, char orientacao = 'c');
    bool venderMaquina(const std::string& coordenadas);
    bool rodarMaquina(const std::string& coordenadas, char orientacao);

    void avancarInstante(int numeroInstantes = 1);

    void adicionarCreditos(int valor) noexcept;
    static void getPosicaoAdjacente(int linha, int coluna, const Orientacao& orientacao, int& linhaDestino, int& colunaDestino) noexcept;

    std::string getInfoPosicao(int linha, int coluna) const;
    std::string getInfoPosicao(const std::string& coordenadas) const;
    std::string getInfoMaquinas() const;

    int getLinhas() const noexcept;
    int getColunas() const noexcept;
    int getCreditos() const noexcept;
    int getInstante() const noexcept;
    int getNumMaquinas() const noexcept;
    const Terreno* getTerreno(int linha, int coluna) const noexcept;
    Terreno* getTerreno(int linha, int coluna) noexcept;
};

#endif // SIMULADOR_FABRICA_H