#include "ComandoRecupera.h"

#include <sstream>
#include <utility>

using std::string;

ComandoRecupera::ComandoRecupera(string nome, string resto) noexcept
    : nome(std::move(nome)), resto(std::move(resto)) {}

bool ComandoRecupera::validar() const {
    return !nome.empty() && resto.empty();
}

string ComandoRecupera::getAjudaSimples() const {
    return "recupera <nome>";
}

string ComandoRecupera::getAjuda() const {
    return getAjudaSimples() + "\n"
           "  Significado: Recupera a copia da fabrica associada ao nome indicado.\n"
           "  Condicoes em que falha: nome em falta ou snapshot inexistente.\n"
           "  Exemplo: recupera antes";
}

string ComandoRecupera::executar(Fabrica&, Simulador&) {
    return ""; // TODO
}

Comando* ComandoRecupera::criarDeStream(std::istringstream& iss) {
    string nome;
    string resto;
    iss >> nome >> resto;
    return new ComandoRecupera(nome, resto);
}
