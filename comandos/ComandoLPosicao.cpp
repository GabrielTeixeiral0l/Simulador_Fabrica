#include "ComandoLPosicao.h"
#include "FerramentasAuxiliares.h"
#include "../Fabrica.h"

#include <sstream>
#include <utility>

using std::string;

ComandoLPosicao::ComandoLPosicao(string coordenada, string raio, string resto) noexcept
    : coordenada(std::move(coordenada)), raio(std::move(raio)), resto(std::move(resto)) {}

bool ComandoLPosicao::validar() const {
    if (!resto.empty() || !FerramentasAuxiliares::isCoordenada(coordenada)) {
        return false;
    }
    if (!raio.empty()) {
        return FerramentasAuxiliares::isNumeroNaoNegativo(raio);
    }
    return true;
}

string ComandoLPosicao::getAjudaSimples() const {
    return "lposicao <lc> [n]";
}

string ComandoLPosicao::getAjuda() const {
    return getAjudaSimples() + "\n"
           "  Significado: Mostra informacao detalhada da posicao lc (ou quadrado centrado de raio n).\n"
           "  Condicoes em que falha: coordenadas invalidas, n negativo/invalido ou argumentos extra.\n"
           "  Exemplo: lposicao df 2";
}

string ComandoLPosicao::executar(Fabrica& fabrica, Simulador&) {
    if (raio.empty()) {
        return fabrica.getInfoPosicao(coordenada);
    }

    int centroL = (coordenada[0] >= 'a' && coordenada[0] <= 'z') ? (coordenada[0] - 'a') : (coordenada[0] - 'A');
    int centroC = (coordenada[1] >= 'a' && coordenada[1] <= 'z') ? (coordenada[1] - 'a') : (coordenada[1] - 'A');
    int r = FerramentasAuxiliares::converterInteiro(raio);

    std::ostringstream oss;
    oss << "Informacao de posicoes (raio " << r << " em torno de " << coordenada << "):\n";
    for (int l = centroL - r; l <= centroL + r; ++l) {
        for (int c = centroC - r; c <= centroC + r; ++c) {
            if (l >= 0 && l < fabrica.getLinhas() && c >= 0 && c < fabrica.getColunas()) {
                oss << "  " << fabrica.getInfoPosicao(l, c) << "\n";
            }
        }
    }
    return oss.str();
}

Comando* ComandoLPosicao::criarDeStream(std::istringstream& iss) {
    string coordenada;
    string raio;
    string resto;
    iss >> coordenada;
    if (iss >> raio) {
        iss >> resto;
    }
    return new ComandoLPosicao(coordenada, raio, resto);
}
