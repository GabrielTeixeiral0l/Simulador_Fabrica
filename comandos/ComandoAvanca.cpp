#include "ComandoAvanca.h"
#include "FerramentasAuxiliares.h"
#include "../Fabrica.h"

#include <sstream>
#include <utility>

using std::string;

ComandoAvanca::ComandoAvanca(string instantes, string resto) noexcept
    : instantes(std::move(instantes)), resto(std::move(resto)) {}

bool ComandoAvanca::validar() const {
    if (!resto.empty()) {
        return false;
    }
    if (instantes.empty()) {
        return true;
    }
    return FerramentasAuxiliares::isNumeroPositivo(instantes);
}

string ComandoAvanca::getAjudaSimples() const {
    return "avanca [n]";
}

string ComandoAvanca::getAjuda() const {
    return getAjudaSimples() + "\n"
           "  Significado: Avanca n instantes no tempo da simulacao (1 por omissao).\n"
           "  Condicoes em que falha: n nao numerico ou n < 1.\n"
           "  Exemplo: avanca 10";
}

string ComandoAvanca::executar(Fabrica& fabrica, Simulador&) {
    int passos = instantes.empty() ? 1 : FerramentasAuxiliares::converterInteiro(instantes);
    fabrica.avancarInstante(passos);
    return "Avancados " + std::to_string(passos) + " instante(s). Instante atual: " +
           std::to_string(fabrica.getInstante()) + ".";
}

Comando* ComandoAvanca::criarDeStream(std::istringstream& iss) {
    string instantes;
    string resto;
    if (iss >> instantes) {
        iss >> resto;
    }
    return new ComandoAvanca(instantes, resto);
}
