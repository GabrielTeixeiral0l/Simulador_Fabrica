#include "ComandoAvanca.h"
#include "../Fabrica.h"
#include <utility>

ComandoAvanca::ComandoAvanca(std::string argN, std::string resto) noexcept
    : argN(std::move(argN)), resto(std::move(resto)) {}

bool ComandoAvanca::validar() const {
    if (!resto.empty()) {
        return false;
    }
    if (argN.empty()) {
        return true;
    }
    try {
        size_t idx;
        int n = std::stoi(argN, &idx);
        return idx == argN.length() && n >= 1;
    } catch (...) {
        return false;
    }
}

std::string ComandoAvanca::getAjuda() const {
    return "avanca [n]\n"
           "  Significado: Avanca n instantes no tempo da simulacao (1 por omissao).\n"
           "  Condicoes em que falha: n nao numerico ou n < 1.\n"
           "  Exemplo: avanca 10";
}

std::string ComandoAvanca::executar(Fabrica& fabrica, Simulador&) {
    int n = argN.empty() ? 1 : std::stoi(argN);
    fabrica.avancarInstante(n);
    return "Avancados " + std::to_string(n) + " instante(s). Instante atual: " + std::to_string(fabrica.getInstante()) + ".";
}
