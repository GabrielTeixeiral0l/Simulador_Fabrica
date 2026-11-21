#include "Gelo.h"
#include "../Settings.h"

Gelo::Gelo() noexcept
    : MateriaPrima("gelo", 'g', Settings::valor_gelo) {}

Gelo::~Gelo() noexcept = default;

Item* Gelo::duplicar() const {
    return new Gelo(*this);
}
