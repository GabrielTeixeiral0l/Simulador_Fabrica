#include "Terreno.h"

bool Terreno::podeConstruir() const noexcept {
    return false;
}

bool Terreno::extrair([[maybe_unused]] int quantidadeExtrair) noexcept {
    return false;
}

int Terreno::getQuantidade() const noexcept {
    return 0;
}
