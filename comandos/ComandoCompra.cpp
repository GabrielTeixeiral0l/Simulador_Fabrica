#include "ComandoCompra.h"
#include "../FerramentasAuxiliares.h"
#include "../Fabrica.h"

#include <sstream>
#include <utility>

using std::string;

ComandoCompra::ComandoCompra(string tipo, string coordenada, string direcao, string resto) noexcept
    : tipo(std::move(tipo)), coordenada(std::move(coordenada)), direcao(std::move(direcao)), resto(std::move(resto)) {}

bool ComandoCompra::validar() const {
    if (!resto.empty() || !FerramentasAuxiliares::isCoordenada(coordenada)) {
        return false;
    }
    if (tipo != "p" && tipo != "t" && tipo != "r" && tipo != "o" && tipo != "s" && tipo != "l") {
        return false;
    }
    if (direcao.length() != 1) {
        return false;
    }
    char d = direcao[0];
    return (d == 'c' || d == 'b' || d == 'e' || d == 'd');
}

string ComandoCompra::getAjudaSimples() const {
    return "compra <tipo> <lc> <dir>";
}

string ComandoCompra::getAjuda() const {
    return getAjudaSimples() + "\n"
           "  Significado: Compra maquina do tipo indicado (p, t, r, o, s, l) na posicao lc e direcao dir (c, b, e, d).\n"
           "  Condicoes em que falha: tipo invalido, posicao invalida/ocupada/cratera, falta de creditos ou direcao invalida.\n"
           "  Exemplo: compra t ce d";
}

string ComandoCompra::executar(Fabrica& fabrica, Simulador&) {
    char d = direcao.empty() ? 'c' : direcao[0];
    if (fabrica.comprarMaquina(tipo, coordenada, d)) {
        return "Maquina '" + tipo + "' comprada na posicao " + coordenada + ".";
    }
    return "Erro ao comprar maquina: posicao ocupada, invalida ou creditos insuficientes.";
}

Comando* ComandoCompra::criarDeStream(std::istringstream& iss) {
    string tipo;
    string coordenada;
    string direcao;
    string resto;
    iss >> tipo >> coordenada >> direcao >> resto;
    return new ComandoCompra(tipo, coordenada, direcao, resto);
}
