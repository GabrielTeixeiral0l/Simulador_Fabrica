#ifndef SIMULADOR_SIMULADOR_H
#define SIMULADOR_SIMULADOR_H

#include "Fabrica.h"
#include "Ecra.h"
#include <string>

class Simulador {
    Fabrica fabrica;
    Ecra ecra;
    bool emExecucao;
    std::string ultimaMensagem;

    void desenharEcraInicial();
    void desenharRegua() noexcept;
    void desenharGrelha() noexcept;
    void desenharPainel(int colunaPainel);
    void desenharFabrica();

public:
    Simulador();

    void executar();
    std::string processarLinha(const std::string& linha);
    void parar() noexcept;
    bool carregarFicheiro(const std::string& nomeFicheiro);
};

#endif // SIMULADOR_SIMULADOR_H
