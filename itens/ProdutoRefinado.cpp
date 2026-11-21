#include "ProdutoRefinado.h"
#include <utility>

ProdutoRefinado::ProdutoRefinado(std::string nome, char simbolo, int valor) noexcept
    : Item(std::move(nome), simbolo, valor) {}

ProdutoRefinado::~ProdutoRefinado() noexcept = default;
