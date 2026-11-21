#include "ComandoFim.h"
#include "../Simulador.h"
#include <utility>

using std::string;

ComandoFim::ComandoFim(string resto) noexcept
    : resto(std::move(resto)) {}

bool ComandoFim::validar() const {
    return resto.empty();
}

string ComandoFim::getAjuda() const {
    return "fim\n"
           "  Significado: Encerra a simulacao e o programa de forma limpa.\n"
           "  Condicoes em que falha: argumentos extra inesperados.\n"
           "  Exemplo: fim";
}

string ComandoFim::executar(Fabrica&, Simulador& simulador) {
    simulador.parar();
    return "A encerrar o simulador com saida limpa...";
}

Comando* ComandoFim::criarDeStream(std::istringstream& iss) {
    std::string resto;
    iss >> resto;
    return new ComandoFim(resto);
}
