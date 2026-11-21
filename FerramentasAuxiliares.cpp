#include "FerramentasAuxiliares.h"
#include <cstddef>
#include <random>

bool FerramentasAuxiliares::isLetra(char c) noexcept {
    return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z');
}

bool FerramentasAuxiliares::isCoordenada(const std::string& s) noexcept {
    return s.size() == 2 && isLetra(s[0]) && isLetra(s[1]);
}

bool FerramentasAuxiliares::isNumeroPositivo(const std::string& s) noexcept {
    if (s.empty() || s == "0") {
        return false;
    }
    for (std::size_t i = 0; i < s.size(); ++i) {
        if (s[i] < '0' || s[i] > '9') {
            return false;
        }
    }
    return true;
}

bool FerramentasAuxiliares::isNumeroNaoNegativo(const std::string& s) noexcept {
    if (s.empty()) {
        return false;
    }
    for (std::size_t i = 0; i < s.size(); ++i) {
        if (s[i] < '0' || s[i] > '9') {
            return false;
        }
    }
    return true;
}

int FerramentasAuxiliares::converterInteiro(const std::string& s) noexcept {
    int valor = 0;
    for (std::size_t i = 0; i < s.size(); ++i) {
        valor = valor * 10 + (s[i] - '0');
    }
    return valor;
}

int FerramentasAuxiliares::gerarInteiro(int min, int max) {
    static std::random_device rd;
    static std::default_random_engine gerador(rd());
    std::uniform_int_distribution<int> distribuicao(min, max);
    return distribuicao(gerador);
}

bool FerramentasAuxiliares::probabilidadeOcorre(int percentagem) {
    if (percentagem <= 0) {
        return false;
    }
    if (percentagem >= 100) {
        return true;
    }
    return gerarInteiro(0, 99) < percentagem;
}
