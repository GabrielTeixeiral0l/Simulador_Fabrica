#include "ComandoMelhora.h"
#include <utility>

ComandoMelhora::ComandoMelhora(std::string coord, std::string resto) noexcept
    : coord(std::move(coord)), resto(std::move(resto)) {}

bool ComandoMelhora::validar() const {
    if (!resto.empty() || coord.length() != 2) {
        return false;
    }
    char l = coord[0];
    char c = coord[1];
    return (((l >= 'a' && l <= 'z') || (l >= 'A' && l <= 'Z')) &&
            ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z')));
}

std::string ComandoMelhora::getAjuda() const {
    return "melhora <lc>\n"
           "  Significado: Melhora a maquina na posicao lc pagando o respetivo custo.\n"
           "  Condicoes em que falha: posicao sem maquina ou coordenadas invalidas.\n"
           "  Exemplo: melhora hi";
}

std::string ComandoMelhora::executar(Fabrica&, Simulador&) {
    return "Comando 'melhora' validado com sucesso (funcionalidade reservada para a entrega final).";
}
