#ifndef SIMULADOR_H
#define SIMULADOR_H

#include "Fabrica.h"
#include "Ecra.h"
#include <string>

class Simulador {
private:
    Fabrica fabrica;
    Ecra ecra;
    bool emExecucao;
    std::string ultimaMensagem;

    void desenharEcraInicial();
    void desenharRegua() noexcept;
    void desenharGrelha() noexcept;
    void desenharPainel(int colunaPainel);
    void desenharFabrica();
    static std::string extrairResumoPainel(const std::string& texto);

public:
    Simulador();

    void atualizarEcra();
    std::string processarLinha(const std::string& linha);
    void parar() noexcept;
    void executar();
};

#endif // SIMULADOR_H