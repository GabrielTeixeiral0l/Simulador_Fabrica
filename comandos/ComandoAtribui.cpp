#include "ComandoAtribui.h"
#include "../FerramentasAuxiliares.h"

#include <sstream>
#include <utility>

using std::string;

ComandoAtribui::ComandoAtribui(string idEngenheiro, string coordenada, string resto) noexcept
    : idEngenheiro(std::move(idEngenheiro)), coordenada(std::move(coordenada)), resto(std::move(resto)) {}

bool ComandoAtribui::validar() const {
    return resto.empty() &&
           FerramentasAuxiliares::isCoordenada(coordenada) &&
           FerramentasAuxiliares::isNumeroPositivo(idEngenheiro);
}

string ComandoAtribui::getAjudaSimples() const {
    return "atribui <id> <lc>";
}

string ComandoAtribui::getAjuda() const {
    return getAjudaSimples() + "\n"
           "  Significado: Atribui o engenheiro com numero id a maquina na posicao lc.\n"
           "  Condicoes em que falha: id invalido, posicao invalida ou sem maquina.\n"
           "  Exemplo: atribui 2 hr";
}

string ComandoAtribui::executar(Fabrica&, Simulador&) {
    return ""; // TODO
}

Comando* ComandoAtribui::criarDeStream(std::istringstream& iss) {
    string idEngenheiro;
    string coordenada;
    string resto;
    iss >> idEngenheiro >> coordenada >> resto;
    return new ComandoAtribui(idEngenheiro, coordenada, resto);
}
