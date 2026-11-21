#include "SilicioBruto.h"
#include "../Settings.h"

SilicioBruto::SilicioBruto() noexcept
    : MateriaPrima("silicio_bruto", 's', Settings::valor_silicio_bruto) {}

SilicioBruto::~SilicioBruto() noexcept = default;

Item* SilicioBruto::clone() const {
    return new SilicioBruto(*this);
}
