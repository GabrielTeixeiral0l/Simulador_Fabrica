#include "ComandoContrata.h"
#include <utility>

using std::string;

ComandoContrata::ComandoContrata(string nome, string resto) noexcept
    : nome(std::move(nome)), resto(std::move(resto)) {}

bool ComandoContrata::validar() const {
    return !nome.empty() && resto.empty();
}

string ComandoContrata::getAjuda() const {
    return "contrata <nome>\n"
           "  Significado: Contrata um novo engenheiro com o nome indicado (salario e custo definidos em Settings).\n"
           "  Condicoes em que falha: nome em falta ou creditos insuficientes.\n"
           "  Exemplo: contrata joaquim";
}

string ComandoContrata::executar(Fabrica&, Simulador&) {
    return "Comando 'contrata' validado com sucesso (funcionalidade de engenheiros reservada para a entrega final).";
}
