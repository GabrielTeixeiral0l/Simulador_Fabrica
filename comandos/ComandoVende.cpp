#include "ComandoVende.h"
#include "../Fabrica.h"
#include <utility>

using std::string;

ComandoVende::ComandoVende(string coord, string resto) noexcept
    : coord(std::move(coord)), resto(std::move(resto)) {}

bool ComandoVende::validar() const {
    if (!resto.empty() || coord.length() != 2) {
        return false;
    }
    char l = coord[0];
    char c = coord[1];
    return (((l >= 'a' && l <= 'z') || (l >= 'A' && l <= 'Z')) &&
            ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z')));
}

string ComandoVende::getAjuda() const {
    return "vende <lc>\n"
           "  Significado: Vende a maquina na posicao indicada, recuperando 50% do custo.\n"
           "  Condicoes em que falha: posicao sem maquina ou coordenadas invalidas.\n"
           "  Exemplo: vende ce";
}

string ComandoVende::executar(Fabrica& fabrica, Simulador&) {
    if (fabrica.venderMaquina(coord)) {
        return "Maquina vendida na posicao " + coord + ".";
    }
    return "Erro ao vender maquina: nenhuma maquina presente na posicao " + coord + ".";
}
