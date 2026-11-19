#include "ComandoEstado.h"
#include "../Fabrica.h"
#include "../terreno/Solo.h"
#include <sstream>
#include <utility>

ComandoEstado::ComandoEstado(std::string resto) noexcept
    : resto(std::move(resto)) {}

bool ComandoEstado::validar() const {
    return resto.empty();
}

std::string ComandoEstado::getAjuda() const {
    return "estado\n"
           "  Significado: Apresenta o estado geral da simulacao (instante, creditos, maquinas e armazem).\n"
           "  Condicoes em que falha: parametros adicionais inesperados.\n"
           "  Exemplo: estado";
}

std::string ComandoEstado::executar(Fabrica& fabrica, Simulador&) {
    std::ostringstream oss;
    oss << "Estado da Fabrica:\n"
        << "  Instante: " << fabrica.getInstante() << "\n"
        << "  Creditos: " << fabrica.getCreditos() << "\n"
        << "  " << fabrica.getArmazem().getInfoEstado() << "\n";

    int numMaquinas = 0;
    std::ostringstream maquinasOss;
    for (int l = 0; l < fabrica.getLinhas(); ++l) {
        for (int c = 0; c < fabrica.getColunas(); ++c) {
            const Solo* solo = dynamic_cast<const Solo*>(fabrica.getTerreno(l, c));
            if (solo != nullptr && solo->getMaquina() != nullptr) {
                const Maquina* m = solo->getMaquina();
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
