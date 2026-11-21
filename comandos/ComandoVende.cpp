#include "ComandoVende.h"
#include "FerramentasAuxiliares.h"
#include "../Fabrica.h"

#include <sstream>
#include <utility>

using std::string;

ComandoVende::ComandoVende(string coordenada, string resto) noexcept
    : coordenada(std::move(coordenada)), resto(std::move(resto)) {}

bool ComandoVende::validar() const {
    return resto.empty() && FerramentasAuxiliares::isCoordenada(coordenada);
}

string ComandoVende::getAjudaSimples() const {
    return "vende <lc>";
}

string ComandoVende::getAjuda() const {
    return getAjudaSimples() + "\n"
           "  Significado: Vende a maquina na posicao indicada, recuperando 50% do custo.\n"
           "  Condicoes em que falha: posicao sem maquina ou coordenadas invalidas.\n"
           "  Exemplo: vende ce";
}

string ComandoVende::executar(Fabrica& fabrica, Simulador&) {
    if (fabrica.venderMaquina(coordenada)) {
        return "Maquina vendida na posicao " + coordenada + ".";
    }
    return "Erro ao vender maquina: nenhuma maquina presente na posicao " + coordenada + ".";
}

Comando* ComandoVende::criarDeStream(std::istringstream& iss) {
    string coordenada;
    string resto;
    iss >> coordenada >> resto;
    return new ComandoVende(coordenada, resto);
}
