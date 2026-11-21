#include "Agua.h"
#include "../Settings.h"

Agua::Agua() noexcept
    : ProdutoRefinado("agua", 'a', Settings::valor_agua) {}

Agua::~Agua() noexcept = default;

Item* Agua::duplicar() const {
    return new Agua(*this);
}
