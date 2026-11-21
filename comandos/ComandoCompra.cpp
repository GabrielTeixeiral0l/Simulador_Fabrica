#include "ComandoCompra.h"
#include "../Fabrica.h"
#include <utility>

using std::string;

ComandoCompra::ComandoCompra(string tipo, string coord, string dir, string resto) noexcept
    : tipo(std::move(tipo)), coord(std::move(coord)), dir(std::move(dir)), resto(std::move(resto)) {}

bool ComandoCompra::validar() const {
    if (!resto.empty() || coord.length() != 2) {
        return false;
    }
    char l = coord[0];
    char c = coord[1];
    if (!((l >= 'a' && l <= 'z') || (l >= 'A' && l <= 'Z')) ||
        !((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))) {
        return false;
    }

    if (tipo != "p" && tipo != "t" && tipo != "r" && tipo != "o" && tipo != "s" && tipo != "l") {
        return false;
    }

    if (dir.length() != 1) {
        return false;
    }
    char d = dir[0];
    return (d == 'c' || d == 'b' || d == 'e' || d == 'd');
}

string ComandoCompra::getAjuda() const {
    return "compra <tipo> <lc> <dir>\n"
           "  Significado: Compra maquina do tipo indicado (p, t, r, o, s, l) na posicao lc e direcao dir (c, b, e, d).\n"
           "  Condicoes em que falha: tipo invalido, posicao invalida/ocupada/cratera, falta de creditos ou direcao invalida.\n"
           "  Exemplo: compra t ce d";
}

string ComandoCompra::executar(Fabrica& fabrica, Simulador&) {
    char d = dir.empty() ? 'c' : dir[0];
    if (fabrica.comprarMaquina(tipo, coord, d)) {
        return "Maquina '" + tipo + "' comprada na posicao " + coord + ".";
    }
    return "Erro ao comprar maquina: posicao ocupada, invalida ou creditos insuficientes.";
}

Comando* ComandoCompra::criarDeStream(std::istringstream& iss) {
    std::string tipo;
    std::string coord;
    std::string dir;
    std::string resto;
    iss >> tipo >> coord >> dir >> resto;
    return new ComandoCompra(tipo, coord, dir, resto);
}
