#include "ComandoMelhora.h"
#include <utility>

using std::string;

ComandoMelhora::ComandoMelhora(string coord, string resto) noexcept
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

string ComandoMelhora::getAjuda() const {
    return "melhora <lc>\n"
           "  Significado: Melhora a maquina na posicao lc pagando o respetivo custo.\n"
           "  Condicoes em que falha: posicao sem maquina ou coordenadas invalidas.\n"
           "  Exemplo: melhora hi";
}

string ComandoMelhora::executar(Fabrica&, Simulador&) {
    return "Comando 'melhora' validado com sucesso (funcionalidade reservada para a entrega final).";
}

ComandoMelhora::ComandoMelhora(bool) : Comando(true) {}

const char* ComandoMelhora::getNome() const noexcept {
    return "melhora";
}

Comando* ComandoMelhora::criarComArgs(std::istringstream& iss) const {
    std::string coord;
    std::string resto;
    iss >> coord >> resto;
    return new ComandoMelhora(coord, resto);
}

namespace {
    ComandoMelhora prototipo_ComandoMelhora(true);
}
