#ifndef SIMULADOR_SIMULADOR_H
#define SIMULADOR_SIMULADOR_H

#include "Fabrica.h"
#include "Ecra.h"
#include <string>

class Simulador {
private:
    Fabrica fabrica;
    Ecra ecra;

    void desenharRegua() noexcept;
    void desenharPainel();
    void desenharFabrica();

public:
    explicit Simulador(int numLinhas = Settings::fabrica_max_linhas, int numColunas = Settings::fabrica_max_colunas);
    ~Simulador() noexcept = default;

    void executar();
    bool carregarFicheiro(const std::string& nomeFicheiro);
};

#endif // SIMULADOR_SIMULADOR_H
