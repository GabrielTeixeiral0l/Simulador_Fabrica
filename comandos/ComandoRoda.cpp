#include "ComandoRoda.h"
#include "../FerramentasAuxiliares.h"
#include "../Fabrica.h"

#include <sstream>
#include <utility>

using std::string;

ComandoRoda::ComandoRoda(string coordenada, string direcao, string resto) noexcept
    : coordenada(std::move(coordenada)), direcao(std::move(direcao)), resto(std::move(resto)) {}

bool ComandoRoda::validar() const {
    if (!resto.empty() || !FerramentasAuxiliares::isCoordenada(coordenada) || direcao.length() != 1) {
        return false;
    }
    char d = direcao[0];
    return d == 'c' || d == 'b' || d == 'e' || d == 'd';
}

string ComandoRoda::getAjudaSimples() const {
    return "roda <lc> <dir>";
}

string ComandoRoda::getAjuda() const {
    return getAjudaSimples() + "\n"
           "  Significado: Muda a direcao de saida da maquina em lc para dir (c, b, e, d).\n"
           "  Condicoes em que falha: posicao sem maquina ou argumentos invalidos.\n"
           "  Exemplo: roda ce b";
}

string ComandoRoda::executar(Fabrica& fabrica, Simulador&) {
    if (fabrica.rodarMaquina(coordenada, direcao[0])) {
        return "Direcao da maquina em " + coordenada + " alterada para " + direcao + ".";
    }
    return "Erro ao rodar maquina: nenhuma maquina presente na posicao " + coordenada + ".";
}

Comando* ComandoRoda::criarDeStream(std::istringstream& iss) {
    string coordenada;
    string direcao;
    string resto;
    iss >> coordenada;
    if (iss >> direcao) {
        iss >> resto;
    }
    return new ComandoRoda(coordenada, direcao, resto);
}
