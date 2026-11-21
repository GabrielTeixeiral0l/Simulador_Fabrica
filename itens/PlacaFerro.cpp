#include "PlacaFerro.h"
#include "../Settings.h"

PlacaFerro::PlacaFerro() noexcept
    : ProdutoRefinado("placa_ferro", 'p', Settings::valor_placa_ferro) {}

PlacaFerro::~PlacaFerro() noexcept = default;

Item* PlacaFerro::clone() const {
    return new PlacaFerro(*this);
}
