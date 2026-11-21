#include "ComandoRoda.h"
#include "../Fabrica.h"
#include <utility>

using std::string;

ComandoRoda::ComandoRoda(string coord, string dir, string resto) noexcept
    : coord(std::move(coord)), dir(std::move(dir)), resto(std::move(resto)) {}

bool ComandoRoda::validar() const {
    if (!resto.empty() || coord.length() != 2 || dir.length() != 1) return false;
    char l = coord[0], c = coord[1], d = dir[0];
    if (!((l >= 'a' && l <= 'z') || (l >= 'A' && l <= 'Z'))) return false;
    if (!((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))) return false;
    return d == 'c' || d == 'b' || d == 'e' || d == 'd';
}

string ComandoRoda::getAjuda() const {
    return "roda <lc> <dir>\n"
           "  Significado: Muda a direcao de saida da maquina em lc para dir (c, b, e, d).\n"
           "  Condicoes em que falha: posicao sem maquina ou argumentos invalidos.\n"
           "  Exemplo: roda ce b";
}

string ComandoRoda::executar(Fabrica& fabrica, Simulador&) {
    if (fabrica.rodarMaquina(coord, dir[0])) {
        return "Direcao da maquina em " + coord + " alterada para " + dir + ".";
    }
    return "Erro ao rodar maquina: nenhuma maquina presente na posicao " + coord + ".";
}

ComandoRoda::ComandoRoda(bool) : Comando(true) {}

const char* ComandoRoda::getNome() const noexcept {
    return "roda";
}

Comando* ComandoRoda::criarComArgs(std::istringstream& iss) const {
    std::string coord;
    std::string dir;
    std::string resto;
    iss >> coord;
    if (iss >> dir) { iss >> resto; }
    return new ComandoRoda(coord, dir, resto);
}

namespace {
    ComandoRoda prototipo_ComandoRoda(true);
}
