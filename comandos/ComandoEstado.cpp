#include "ComandoEstado.h"
#include "../Fabrica.h"
#include <sstream>
#include <utility>

using std::string;

ComandoEstado::ComandoEstado(string resto) noexcept
    : resto(std::move(resto)) {}

bool ComandoEstado::validar() const {
    return resto.empty();
}

string ComandoEstado::getAjuda() const {
    return "estado\n"
           "  Significado: Apresenta o estado geral da simulacao (instante, creditos e maquinas).\n"
           "  Condicoes em que falha: parametros adicionais inesperados.\n"
           "  Exemplo: estado";
}

string ComandoEstado::executar(Fabrica& fabrica, Simulador&) {
    std::ostringstream oss;
    oss << "Estado da Fabrica:\n"
        << "  Instante: " << fabrica.getInstante() << "\n"
        << "  Creditos: " << fabrica.getCreditos() << "\n";

    int numMaquinas = 0;
    std::ostringstream maquinasOss;
    for (int l = 0; l < fabrica.getLinhas(); ++l) {
        for (int c = 0; c < fabrica.getColunas(); ++c) {
            const Terreno* t = fabrica.getTerreno(l, c);
            if (t != nullptr && t->getMaquina() != nullptr) {
                const Maquina* m = t->getMaquina();
                char lChar = static_cast<char>('a' + l);
                char cChar = static_cast<char>('a' + c);
                maquinasOss << "    - [" << lChar << cChar << "] " << m->getDescricao() << " (ID: " << m->getId() << ")\n";
                ++numMaquinas;
            }
        }
    }
    oss << "  Maquinas (" << numMaquinas << " instaladas):\n";
    if (numMaquinas == 0) {
        oss << "    (nenhuma maquina instalada)\n";
    } else {
        oss << maquinasOss.str();
    }
    return oss.str();
}

ComandoEstado::ComandoEstado(bool) : Comando(true) {}

const char* ComandoEstado::getNome() const noexcept {
    return "estado";
}

Comando* ComandoEstado::criarComArgs(std::istringstream& iss) const {
    std::string resto;
    iss >> resto;
    return new ComandoEstado(resto);
}

namespace {
    ComandoEstado prototipo_ComandoEstado(true);
}
