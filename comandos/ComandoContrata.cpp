#include "ComandoContrata.h"

#include <sstream>
#include <utility>

using std::string;

ComandoContrata::ComandoContrata(string nome, string resto) noexcept
    : nome(std::move(nome)), resto(std::move(resto)) {}

bool ComandoContrata::validar() const {
    return !nome.empty() && resto.empty();
}

string ComandoContrata::getAjudaSimples() const {
    return "contrata <nome>";
}

string ComandoContrata::getAjuda() const {
    return getAjudaSimples() + "\n"
           "  Significado: Contrata um novo engenheiro com o nome indicado (custo: " +
           std::to_string(Settings::engenheiro_custo_contratacao) +
           " creditos; salario: " + std::to_string(Settings::engenheiro_salario) +
           " creditos/instante).\n"
           "  Condicoes em que falha: nome em falta ou creditos insuficientes.\n"
           "  Exemplo: contrata joaquim";
}

string ComandoContrata::executar(Fabrica&, Simulador&) {
    return ""; // TODO
}

Comando* ComandoContrata::criarDeStream(std::istringstream& iss) {
    string nome;
    string resto;
    iss >> nome >> resto;
    return new ComandoContrata(nome, resto);
}
