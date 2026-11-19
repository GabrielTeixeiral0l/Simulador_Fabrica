#include "ComandoAtribui.h"
#include <utility>

ComandoAtribui::ComandoAtribui(std::string argId, std::string coord, std::string resto) noexcept
    : argId(std::move(argId)), coord(std::move(coord)), resto(std::move(resto)) {}

bool ComandoAtribui::validar() const {
    if (!resto.empty() || coord.length() != 2) {
        return false;
    }
    char l = coord[0];
    char c = coord[1];
    if (!((l >= 'a' && l <= 'z') || (l >= 'A' && l <= 'Z')) ||
        !((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))) {
        return false;
    }

    try {
        size_t idx;
        int id = std::stoi(argId, &idx);
        return idx == argId.length() && id > 0;
    } catch (...) {
        return false;
    }
}

std::string ComandoAtribui::getAjuda() const {
    return "atribui <id> <lc>\n"
           "  Significado: Atribui o engenheiro com numero id a maquina na posicao lc.\n"
           "  Condicoes em que falha: id invalido, posicao invalida ou sem maquina.\n"
           "  Exemplo: atribui 2 hr";
}

std::string ComandoAtribui::executar([[maybe_unused]] Fabrica& fabrica, [[maybe_unused]] Simulador& simulador) {
    return "Comando 'atribui' validado com sucesso (funcionalidade de engenheiros reservada para a entrega final).";
}
