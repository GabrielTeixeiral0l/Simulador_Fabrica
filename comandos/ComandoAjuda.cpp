#include "ComandoAjuda.h"
#include <sstream>
#include <utility>

using std::string;

ComandoAjuda::ComandoAjuda(string comandoAlvo, string resto) noexcept
    : comandoAlvo(std::move(comandoAlvo)), resto(std::move(resto)) {}

bool ComandoAjuda::validar() const {
    return resto.empty();
}

string ComandoAjuda::getAjudaSimples() const {
    return "ajuda [comando]";
}

string ComandoAjuda::getAjuda() const {
    return getAjudaSimples() + "\n"
           "  Significado: Apresenta resumo de todos os comandos ou a ajuda detalhada do comando indicado.\n"
           "  Condicoes em que falha: argumentos extra alem do nome do comando.\n"
           "  Exemplo: ajuda compra";
}

string ComandoAjuda::executar(Fabrica&, Simulador&) {
    if (!comandoAlvo.empty()) {
        string detalhe = obterAjudaComando(comandoAlvo);
        if (detalhe.empty()) {
            return "Comando '" + comandoAlvo + "' desconhecido. Escreva 'ajuda' para ver a lista.";
        }
        return "Ajuda para o comando '" + comandoAlvo + "':\n" + detalhe;
    }

    string out = "Comandos disponiveis:\n";
    int total = getTotalComandos();
    for (int i = 0; i < total; ++i) {
        out += "  - " + obterAjudaSimplesComando(getNomeComando(i)) + "\n";
    }
    return out;
}

Comando* ComandoAjuda::criarDeStream(std::istringstream& iss) {
    std::string cmdAlvo;
    std::string resto;
    if (iss >> cmdAlvo) { iss >> resto; }
    return new ComandoAjuda(cmdAlvo, resto);
}
