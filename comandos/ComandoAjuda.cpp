#include "ComandoAjuda.h"
#include <sstream>
#include <utility>

using std::string;

ComandoAjuda::ComandoAjuda(string comandoAlvo, string resto) noexcept
    : comandoAlvo(std::move(comandoAlvo)), resto(std::move(resto)) {}

bool ComandoAjuda::validar() const {
    return resto.empty();
}

string ComandoAjuda::getAjuda() const {
    return "ajuda [comando]\n"
           "  Significado: Apresenta resumo de todos os comandos ou a ajuda detalhada do comando indicado.\n"
           "  Condicoes em que falha: argumentos extra alem do nome do comando.\n"
           "  Exemplo: ajuda compra";
}

string ComandoAjuda::executar(Fabrica&, Simulador&) {
    if (comandoAlvo.empty()) {
        std::ostringstream oss;
        oss << "Comandos disponiveis no simulador:\n";
        int total = Comando::getTotalComandos();
        for (int i = 0; i < total; ++i) {
            string detalhe = Comando::obterAjudaComando(Comando::getNomeComando(i));
            size_t primLinha = detalhe.find('\n');
            string resumo = (primLinha != string::npos) ? detalhe.substr(0, primLinha) : detalhe;
            oss << "  - " << resumo << "\n";
        }
        return oss.str();
    }

    string detalhe = Comando::obterAjudaComando(comandoAlvo);
    if (detalhe.empty()) {
        return "Comando '" + comandoAlvo + "' desconhecido. Escreva 'ajuda' para ver a lista.";
    }
    return "Ajuda para o comando '" + comandoAlvo + "':\n" + detalhe;
}
