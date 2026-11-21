#include "ComandoRecupera.h"
#include <utility>

using std::string;

ComandoRecupera::ComandoRecupera(string nome, string resto) noexcept
    : nome(std::move(nome)), resto(std::move(resto)) {}

bool ComandoRecupera::validar() const {
    return !nome.empty() && resto.empty();
}

string ComandoRecupera::getAjuda() const {
    return "recupera <nome>\n"
           "  Significado: Recupera a copia da fabrica associada ao nome indicado.\n"
           "  Condicoes em que falha: nome em falta ou snapshot inexistente.\n"
           "  Exemplo: recupera antes";
}

string ComandoRecupera::executar(Fabrica&, Simulador&) {
    return "Comando 'recupera' validado com sucesso (funcionalidade de snapshots reservada para a entrega final).";
}

ComandoRecupera::ComandoRecupera(bool) : Comando(true) {}

const char* ComandoRecupera::getNome() const noexcept {
    return "recupera";
}

Comando* ComandoRecupera::criarComArgs(std::istringstream& iss) const {
    std::string nome;
    std::string resto;
    iss >> nome >> resto;
    return new ComandoRecupera(nome, resto);
}

namespace {
    ComandoRecupera prototipo_ComandoRecupera(true);
}
