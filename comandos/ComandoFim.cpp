#include "ComandoFim.h"
#include "../Simulador.h"

#include <sstream>
#include <utility>

using std::string;

ComandoFim::ComandoFim(string resto) noexcept
    : resto(std::move(resto)) {}

bool ComandoFim::validar() const {
    return resto.empty();
}

string ComandoFim::getAjudaSimples() const {
    return "fim";
}

string ComandoFim::getAjuda() const {
    return getAjudaSimples() + "\n"
           "  Significado: Encerra a simulacao e o programa de forma limpa.\n"
           "  Condicoes em que falha: argumentos extra inesperados.\n"
           "  Exemplo: fim";
}

string ComandoFim::executar(Fabrica&, Simulador& simulador) {
    simulador.parar();
    return "FIM";
}

Comando* ComandoFim::criarDeStream(std::istringstream& iss) {
    string resto;
    iss >> resto;
    return new ComandoFim(resto);
}

bool ComandoFim::requerFabrica() const noexcept {
    return false;
}
