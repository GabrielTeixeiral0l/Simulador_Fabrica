#ifndef SIMULADOR_FERRAMENTASAUXILIARES_H
#define SIMULADOR_FERRAMENTASAUXILIARES_H

#include <string>

class FerramentasAuxiliares {
public:
    FerramentasAuxiliares() = delete;

    static bool isLetra(char c) noexcept;
    static bool isCoordenada(const std::string& s) noexcept;
    static bool isNumeroPositivo(const std::string& s) noexcept;
    static bool isNumeroNaoNegativo(const std::string& s) noexcept;
    static int converterInteiro(const std::string& s) noexcept;

    static int gerarInteiro(int min, int max);
    static bool probabilidadeOcorre(int percentagem);
};

#endif // SIMULADOR_FERRAMENTASAUXILIARES_H
