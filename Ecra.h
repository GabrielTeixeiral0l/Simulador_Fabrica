#ifndef SIMULADOR_ECRA_H
#define SIMULADOR_ECRA_H

#include <string>
#include "Settings.h"

class Ecra {
    char buffer[Settings::ecra_max_linhas][Settings::ecra_max_colunas];
    int linhas;
    int colunas;
    int linhaCursor;
    int colunaCursor;

    bool estaDentroDosLimites(int l, int c) const noexcept;
    void colocarCaractere(int l, int c, char ch) noexcept;

public:
    explicit Ecra(int l = Settings::ecra_max_linhas, int c = Settings::ecra_max_colunas) noexcept;

    void limpar() noexcept;
    bool gotoxy(int l, int c) noexcept;
    void escrever(char c) noexcept;
    void escrever(const std::string& texto);
    void escrever(int l, int c, char ch) noexcept;
    void escrever(int l, int c, const std::string& texto);
    void desenharMoldura(int linhaInicio, int colunaInicio, int altura, int largura) noexcept;
    void mostrar() const;

    char getCaractere(int l, int c) const noexcept;
    int getLinhas() const noexcept;
    int getColunas() const noexcept;
    int getLinhaCursor() const noexcept;
    int getColunaCursor() const noexcept;
};

#endif // SIMULADOR_ECRA_H
