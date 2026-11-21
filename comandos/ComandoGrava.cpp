#include <sstream>
#include "ComandoGrava.h"
#include <utility>

using std::string;

ComandoGrava::ComandoGrava(string nome, string resto) noexcept
    : nome(std::move(nome)), resto(std::move(resto)) {}

bool ComandoGrava::validar() const {
    return !nome.empty() && resto.empty();
}

string ComandoGrava::getAjudaSimples() const {
    return "grava <nome>\n";
}

string ComandoGrava::getAjuda() const {
    return getAjudaSimples() + "\n"
           "  Significado: Salvaguarda em memoria uma copia do estado completo da fabrica sob o nome indicado.\n"
           "  Condicoes em que falha: nome em falta ou argumentos extra.\n"
           "  Exemplo: grava antes";
}

string ComandoGrava::executar(Fabrica&, Simulador&) {
    return "Comando 'grava' validado com sucesso (funcionalidade de snapshots reservada para a entrega final).";
}

Comando* ComandoGrava::criarDeStream(std::istringstream& iss) {
    std::string nome;
    std::string resto;
    iss >> nome >> resto;
    return new ComandoGrava(nome, resto);
}
