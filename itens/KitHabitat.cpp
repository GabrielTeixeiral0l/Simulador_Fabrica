#include "KitHabitat.h"
#include "../Settings.h"

KitHabitat::KitHabitat() noexcept
    : ProdutoRefinado("kit_habitat", 'k', Settings::valor_kit_habitat) {}

KitHabitat::~KitHabitat() noexcept = default;

Item* KitHabitat::duplicar() const {
    return new KitHabitat(*this);
}
