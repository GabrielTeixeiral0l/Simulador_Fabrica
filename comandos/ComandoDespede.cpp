#include "ComandoDespede.h"
#include "FerramentasAuxiliares.h"

#include <sstream>
#include <utility>

using std::string;

ComandoDespede::ComandoDespede(string idEngenheiro, string resto) noexcept
    : idEngenheiro(std::move(idEngenheiro)), resto(std::move(resto)) {}

bool ComandoDespede::validar() const {
    return resto.empty() && FerramentasAuxiliares::isNumeroPositivo(idEngenheiro);
}

string ComandoDespede::getAjudaSimples() const {
    return "despede <id>";
}

string ComandoDespede::getAjuda() const {
    return getAjudaSimples() + "\n"
           "  Significado: Despede o engenheiro com o id indicado, cessando o pagamento de salario.\n"
           "  Condicoes em que falha: id invalido ou inexistente.\n"
           "  Exemplo: despede 2";
}

string ComandoDespede::executar(Fabrica&, Simulador&) {
    return "Comando 'despede' validado com sucesso (funcionalidade de engenheiros reservada para a entrega final).";
}

Comando* ComandoDespede::criarDeStream(std::istringstream& iss) {
    string idEngenheiro;
    string resto;
    iss >> idEngenheiro >> resto;
    return new ComandoDespede(idEngenheiro, resto);
}
