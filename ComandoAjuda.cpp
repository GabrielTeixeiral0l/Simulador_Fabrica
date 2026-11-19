#include "ComandoAjuda.h"
#include <sstream>
#include <utility>

ComandoAjuda::ComandoAjuda(std::string comandoAlvo, std::string resto) noexcept
    : comandoAlvo(std::move(comandoAlvo)), resto(std::move(resto)) {}

bool ComandoAjuda::validar() const {
    return resto.empty();
}

std::string ComandoAjuda::getAjuda() const {
    return "ajuda [comando]\n"
           "  Significado: Apresenta resumo de todos os comandos ou a ajuda detalhada do comando indicado.\n"
           "  Condicoes em que falha: argumentos extra alem do nome do comando.\n"
           "  Exemplo: ajuda compra";
}

std::string ComandoAjuda::executar([[maybe_unused]] Fabrica& fabrica, [[maybe_unused]] Simulador& simulador) {
    if (comandoAlvo.empty()) {
        std::ostringstream oss;
        oss << "Comandos disponiveis no simulador:\n";
        const auto& lista = Comando::getListaNomesComandos();
        for (const auto& nome : lista) {
            std::string detalhe = Comando::obterAjudaComando(nome);
            size_t primLinha = detalhe.find('\n');
            std::string resumo = (primLinha != std::string::npos) ? detalhe.substr(0, primLinha) : detalhe;
            oss << "  - " << resumo << "\n";
        }
        return oss.str();
    }

    std::string detalhe = Comando::obterAjudaComando(comandoAlvo);
    if (detalhe.empty()) {
        return "Comando '" + comandoAlvo + "' desconhecido. Escreva 'ajuda' para ver a lista.";
    }
    return "Ajuda para o comando '" + comandoAlvo + "':\n" + detalhe;
}
