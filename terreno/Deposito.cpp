#include "Deposito.h"
#include <sstream>

Deposito::Deposito(char simbolo, const std::string& nome, int quantidade)
    : simbolo(simbolo), nome(nome), quantidade(quantidade) {}

char Deposito::getSimboloTerreno() const noexcept {
    return simbolo;
}

std::string Deposito::getDescricao() const {
    std::ostringstream oss;
    oss << "Deposito de " << nome << " (" << quantidade << " unidades)";
    const Maquina* m = getMaquina();
    if (m != nullptr)
        oss << " com " << m->getDescricao();
    return oss.str();
}

bool Deposito::podeConstruir() const noexcept {
    return getMaquina() == nullptr;
}
int Deposito::getQuantidade() const noexcept {
    return quantidade;
}

bool Deposito::extrair(int quantidadeExtrair) noexcept {
    if (quantidadeExtrair <= 0 || quantidade < quantidadeExtrair) return false;
    quantidade -= quantidadeExtrair;
    return true;
}
