#include "ComandoLPosicao.h"
#include "../Fabrica.h"
#include <sstream>
#include <utility>

using std::string;

ComandoLPosicao::ComandoLPosicao(string coord, string argRaio, string resto) noexcept
    : coord(std::move(coord)), argRaio(std::move(argRaio)), resto(std::move(resto)) {}

bool ComandoLPosicao::validar() const {
    if (!resto.empty() || coord.length() != 2) {
        return false;
    }
    char l = coord[0];
    char c = coord[1];
    if (!((l >= 'a' && l <= 'z') || (l >= 'A' && l <= 'Z')) ||
        !((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))) {
        return false;
    }

    if (!argRaio.empty()) {
        try {
            size_t idx;
            int r = std::stoi(argRaio, &idx);
            return idx == argRaio.length() && r >= 0;
        } catch (...) {
            return false;
        }
    }
    return true;
}

string ComandoLPosicao::getAjuda() const {
    return "lposicao <lc> [n]\n"
           "  Significado: Mostra informacao detalhada da posicao lc (ou quadrado centrado de raio n).\n"
           "  Condicoes em que falha: coordenadas invalidas, n negativo/invalido ou argumentos extra.\n"
           "  Exemplo: lposicao df 2";
}

string ComandoLPosicao::executar(Fabrica& fabrica, Simulador&) {
    if (argRaio.empty()) {
        return fabrica.getInfoPosicao(coord);
    }

    int centroL = (coord[0] >= 'a' && coord[0] <= 'z') ? (coord[0] - 'a') : (coord[0] - 'A');
    int centroC = (coord[1] >= 'a' && coord[1] <= 'z') ? (coord[1] - 'a') : (coord[1] - 'A');
    int raio = std::stoi(argRaio);

    std::ostringstream oss;
    oss << "Informacao de posicoes (raio " << raio << " em torno de " << coord << "):\n";
    for (int l = centroL - raio; l <= centroL + raio; ++l) {
        for (int c = centroC - raio; c <= centroC + raio; ++c) {
            if (l >= 0 && l < fabrica.getLinhas() && c >= 0 && c < fabrica.getColunas()) {
                oss << "  " << fabrica.getInfoPosicao(l, c) << "\n";
            }
        }
    }
    return oss.str();
}
