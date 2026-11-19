#include "Deposito.h"
#include <sstream>
#include <utility>

Deposito::Deposito(char simbolo, std::string nome, int quantidade) noexcept
    : simbolo(simbolo), nome(std::move(nome)), quantidade(quantidade) {}

char Deposito::getSimbolo() const noexcept {
    return simbolo;
}

std::string Deposito::getDescricao() const {
    std::ostringstream oss;
    oss << "Deposito de " << nome << " (" << quantidade << " unidades)";
    return oss.str();
}

int Deposito::getQuantidade() const noexcept {
    return quantidade;
}

bool Deposito::extrair(int quantidadeExtrair) noexcept {
    if (quantidadeExtrair <= 0 || quantidade < quantidadeExtrair) {
        return false;
    }
    quantidade -= quantidadeExtrair;
    return true;
}

Terreno* Deposito::clone() const {
    return new Deposito(*this);
}
