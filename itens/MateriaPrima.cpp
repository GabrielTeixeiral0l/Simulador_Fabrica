#include "MateriaPrima.h"
#include <utility>

MateriaPrima::MateriaPrima(std::string nome, char simbolo, int valor) noexcept
    : Item(std::move(nome), simbolo, valor) {}

MateriaPrima::~MateriaPrima() noexcept = default;
