#include "ComandoAjuda.h"

#include <sstream>
#include <utility>

using std::string;

ComandoAjuda::ComandoAjuda(string comando, string resto) noexcept
    : comando(std::move(comando)), resto(std::move(resto)) {}

bool ComandoAjuda::validar() const {
    return resto.empty();
}

string ComandoAjuda::getAjudaSimples() const {
    return "ajuda [comando]";
}

string ComandoAjuda::getAjuda() const {
    return getAjudaSimples() + "\n"
           "  Significado: Apresenta resumo de todos os comandos ou a ajuda do comando indicado.\n"
           "  Condicoes em que falha: argumentos extra alem do nome do comando.\n"
           "  Exemplo: ajuda compra";
}

string ComandoAjuda::executar(Fabrica&, Simulador&) {
    if (!comando.empty()) {
        string detalhe = obterAjudaComando(comando);
        if (detalhe.empty()) {
            return "Comando '" + comando + "' desconhecido. Escreva 'ajuda' para ver a lista.";
        }
        return "Ajuda para o comando '" + comando + "':\n" + detalhe;
    }

    string out = "Comandos disponiveis:\n";
    int total = getTotalComandos();
    for (int i = 0; i < total; ++i) {
        string nome = getNomeComando(i);
        out += "  " + obterAjudaSimplesComando(nome) + "\n";
    }
    return out;
}

Comando* ComandoAjuda::criarDeStream(std::istringstream& iss) {
    string comando;
    string resto;
    iss >> comando >> resto;
    return new ComandoAjuda(comando, resto);
}

bool ComandoAjuda::requerFabrica() const noexcept {
    return false;
}
