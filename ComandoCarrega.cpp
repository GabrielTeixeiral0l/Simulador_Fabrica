#include "ComandoCarrega.h"
#include "Fabrica.h"
#include <utility>

ComandoCarrega::ComandoCarrega(std::string ficheiro, std::string resto) noexcept
    : ficheiro(std::move(ficheiro)), resto(std::move(resto)) {}

bool ComandoCarrega::validar() const {
    return !ficheiro.empty() && resto.empty();
}

std::string ComandoCarrega::getAjuda() const {
    return "carrega <nome-do-ficheiro>\n"
           "  Significado: Cria fabrica a partir do ficheiro de mapa indicado.\n"
           "  Condicoes em que falha: ficheiro em falta, inexistente ou com formato invalido.\n"
           "  Exemplo: carrega mapa1.txt";
}

std::string ComandoCarrega::executar(Fabrica& fabrica, Simulador&) {
    if (fabrica.carregarFicheiro(ficheiro)) {
        return "Ficheiro '" + ficheiro + "' carregado com sucesso.";
    }
    return "Erro ao carregar ficheiro '" + ficheiro + "'.";
}
