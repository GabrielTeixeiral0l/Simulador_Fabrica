#include "ComandoRoda.h"
#include "../Fabrica.h"
#include "../terreno/Solo.h"
#include "../maquinas/Maquina.h"
#include <utility>

ComandoRoda::ComandoRoda(std::string coord, std::string dir, std::string resto) noexcept
    : coord(std::move(coord)), dir(std::move(dir)), resto(std::move(resto)) {}

bool ComandoRoda::validar() const {
    if (!resto.empty() || coord.length() != 2) {
        return false;
    }
    char l = coord[0];
    char c = coord[1];
    if (!((l >= 'a' && l <= 'z') || (l >= 'A' && l <= 'Z')) ||
        !((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))) {
        return false;
    }

    if (!dir.empty()) {
        if (dir.length() != 1) {
            return false;
        }
        char d = dir[0];
        if (d != 'c' && d != 'b' && d != 'e' && d != 'd') {
            return false;
        }
    }
    return true;
}

std::string ComandoRoda::getAjuda() const {
    return "roda <lc> [dir]\n"
           "  Significado: Muda a direcao de saida da maquina em lc (para dir ou sentido horario se omitido).\n"
           "  Condicoes em que falha: posicao sem maquina ou argumentos invalidos.\n"
           "  Exemplo: roda ce b";
}

std::string ComandoRoda::executar(Fabrica& fabrica, Simulador&) {
    if (dir.empty()) {
        if (fabrica.rodarMaquina(coord)) {
            return "Maquina rodada em " + coord + ".";
        }
        return "Erro ao rodar maquina: nenhuma maquina presente na posicao " + coord + ".";
    }

    int l = (coord[0] >= 'a' && coord[0] <= 'z') ? (coord[0] - 'a') : (coord[0] - 'A');
    int c = (coord[1] >= 'a' && coord[1] <= 'z') ? (coord[1] - 'a') : (coord[1] - 'A');
    Solo* solo = dynamic_cast<Solo*>(fabrica.getTerreno(l, c));
    if (solo != nullptr && solo->getMaquina() != nullptr) {
        solo->getMaquina()->setOrientacao(Maquina::charParaOrientacao(dir[0]));
        return "Direcao da maquina em " + coord + " alterada para " + dir + ".";
    }
    return "Erro ao rodar maquina: nenhuma maquina presente na posicao " + coord + ".";
}
