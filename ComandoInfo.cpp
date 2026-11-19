#include "ComandoInfo.h"
#include "Fabrica.h"
#include <utility>

ComandoInfo::ComandoInfo(std::string coordenadas) noexcept
    : coordenadas(std::move(coordenadas)) {}

std::string ComandoInfo::executar(Fabrica& fabrica, [[maybe_unused]] Simulador& simulador) {
    return fabrica.getInfoPosicao(coordenadas);
}
