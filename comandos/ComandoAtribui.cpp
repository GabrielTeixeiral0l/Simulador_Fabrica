#include "ComandoAtribui.h"

#include <sstream>
#include <utility>

using std::string;

static bool isLetra(char c) noexcept {
    return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z');
}

ComandoAtribui::ComandoAtribui(string idEngenheiro, string coord, string resto) noexcept
    : idEngenheiro(std::move(idEngenheiro)), coord(std::move(coord)), resto(std::move(resto)) {}

bool ComandoAtribui::validar() const {
    if (!resto.empty() || coord.size() != 2) {
        return false;
    }
    if (!isLetra(coord[0]) || !isLetra(coord[1])) {
        return false;
    }
    // TODO: validar id do engenheiro quando existirem engenheiros
    return !idEngenheiro.empty();
}

string ComandoAtribui::getAjudaSimples() const {
    return "atribui <id> <lc>";
}

string ComandoAtribui::getAjuda() const {
    return getAjudaSimples() + "\n"
           "  Significado: Atribui o engenheiro com numero id a maquina na posicao lc.\n"
           "  Condicoes em que falha: id invalido, posicao invalida ou sem maquina.\n"
           "  Exemplo: atribui 2 hr";
}

string ComandoAtribui::executar(Fabrica&, Simulador&) {
    return ""; // TODO
}

Comando* ComandoAtribui::criarDeStream(std::istringstream& iss) {
    string id;
    string coord;
    string resto;
    iss >> id >> coord >> resto;
    return new ComandoAtribui(id, coord, resto);
}