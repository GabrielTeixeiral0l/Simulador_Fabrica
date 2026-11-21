#include "SilicioPuro.h"
#include "../Settings.h"

SilicioPuro::SilicioPuro() noexcept
    : ProdutoRefinado("silicio_puro", 'i', Settings::valor_silicio_puro) {}

SilicioPuro::~SilicioPuro() noexcept = default;

Item* SilicioPuro::duplicar() const {
    return new SilicioPuro(*this);
}
