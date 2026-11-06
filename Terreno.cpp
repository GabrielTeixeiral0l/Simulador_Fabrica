#include "Terreno.h"
#include <sstream>

Terreno::~Terreno() = default;

char Terreno::getSimbolo() const noexcept {
    return ' ';
}

std::string Terreno::getDescricao() const {
    return "Terreno";
}

Solo::~Solo() = default;

char Solo::getSimbolo() const noexcept {
    return ' ';
}

std::string Solo::getDescricao() const {
    return "Solo vazio";
}

Cratera::~Cratera() = default;

char Cratera::getSimbolo() const noexcept {
    return '#';
}

std::string Cratera::getDescricao() const {
    return "Cratera";
}

Deposito::Deposito(const std::string& nome, char simbolo, int quantidade)
    : nome(nome), simbolo(simbolo), quantidade(quantidade) {}

Deposito::~Deposito() = default;

char Deposito::getSimbolo() const noexcept {
    return simbolo;
}

std::string Deposito::getDescricao() const {
    std::ostringstream oss;
    oss << "Deposito de " << nome << " (" << quantidade << " unidades)";
    return oss.str();
}

const std::string& Deposito::getNome() const noexcept {
    return nome;
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
