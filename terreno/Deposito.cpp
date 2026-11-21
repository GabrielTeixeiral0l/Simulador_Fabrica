#include "Deposito.h"
#include <sstream>
#include "../itens/MinerioFerro.h"
#include "../itens/SilicioBruto.h"
#include "../itens/Gelo.h"

Deposito::Deposito(char simbolo, const std::string& nome, int quantidade)
    : simbolo(simbolo), nome(nome), quantidade(quantidade) {}

Deposito::~Deposito() noexcept = default;

char Deposito::getSimboloTerreno() const noexcept {
    return simbolo;
}

std::string Deposito::getDescricao() const {
    std::ostringstream oss;
    oss << "Deposito de " << nome << " (" << quantidade << " unidades)";
    const Maquina* m = getMaquina();
    if (m != nullptr) {
        oss << " com " << m->getDescricao();
    }
    return oss.str();
}

bool Deposito::podeConstruir() const noexcept {
    return getMaquina() == nullptr;
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

std::string Deposito::getNome() const {
    return nome;
}


Item* Deposito::criarItem() const {
    if (nome == "Ferro") {
        return new MinerioFerro();
    }
    if (nome == "Silicio") {
        return new SilicioBruto();
    }
    if (nome == "Gelo") {
        return new Gelo();
    }
    return nullptr;
}