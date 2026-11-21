#include "ComandoMelhora.h"
#include "../FerramentasAuxiliares.h"

#include <sstream>
#include <utility>

using std::string;

ComandoMelhora::ComandoMelhora(string coordenada, string resto) noexcept
    : coordenada(std::move(coordenada)), resto(std::move(resto)) {}

bool ComandoMelhora::validar() const {
    return resto.empty() && FerramentasAuxiliares::isCoordenada(coordenada);
}

string ComandoMelhora::getAjudaSimples() const {
    return "melhora <lc>";
}

string ComandoMelhora::getAjuda() const {
    return getAjudaSimples() + "\n"
           "  Significado: Melhora a maquina na posicao lc pagando o respetivo custo.\n"
           "  Condicoes em que falha: posicao sem maquina ou coordenadas invalidas.\n"
           "  Exemplo: melhora hi";
}

string ComandoMelhora::executar(Fabrica&, Simulador&) {
    return ""; // TODO
}

Comando* ComandoMelhora::criarDeStream(std::istringstream& iss) {
    string coordenada;
    string resto;
    iss >> coordenada >> resto;
    return new ComandoMelhora(coordenada, resto);
}
