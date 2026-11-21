#include "PlacaFerro.h"
#include "../Settings.h"

PlacaFerro::PlacaFerro() noexcept
    : ProdutoRefinado("placa_ferro", 'p', Settings::valor_placa_ferro) {}

PlacaFerro::~PlacaFerro() noexcept = default;

Item* PlacaFerro::duplicar() const {
    return new PlacaFerro(*this);
}
