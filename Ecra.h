#ifndef SIMULADOR_ECRA_H
#define SIMULADOR_ECRA_H

#include <string>
#include "Settings.h"

class Ecra {
    char buffer[Settings::ecra_max_linhas][Settings::ecra_max_colunas]{};
    int linhas;
    int colunas;
    int linhaCursor;
    int colunaCursor;

    bool estaDentroDosLimites(int linha, int coluna) const noexcept;
    void colocarCaractere(int linha, int coluna, char caractere) noexcept;

public:
    explicit Ecra(int numLinhas = Settings::ecra_max_linhas, int numColunas = Settings::ecra_max_colunas) noexcept;

    void limpar() noexcept;
    bool gotoxy(int linha, int coluna) noexcept;
    void escrever(char caractere) noexcept;
    void escrever(const std::string& texto);
    void escrever(int linha, int coluna, char caractere) noexcept;
    void escrever(int linha, int coluna, const std::string& texto);
    void desenharMoldura(int linhaInicio, int colunaInicio, int altura, int largura) noexcept;
    void mostrar() const;

    void setDimensoes(int numLinhas, int numColunas) noexcept;

    char getCaractere(int linha, int coluna) const noexcept;
    int getLinhas() const noexcept;
    int getColunas() const noexcept;
    int getLinhaCursor() const noexcept;
    int getColunaCursor() const noexcept;
};

#endif // SIMULADOR_ECRA_H
