#include "MinerioFerro.h"
#include "../Settings.h"

MinerioFerro::MinerioFerro() noexcept
    : MateriaPrima("minerio_ferro", 'f', Settings::valor_minerio_ferro) {}

MinerioFerro::~MinerioFerro() noexcept = default;

Item* MinerioFerro::duplicar() const {
    return new MinerioFerro(*this);
}
