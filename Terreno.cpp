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

Deposito::Deposito(const std::string& n, char s, int q)
    : nome(n), simbolo(s), quantidade(q) {}

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

bool Deposito::extrair(int qtd) noexcept {
    if (qtd <= 0 || quantidade < qtd) {
        return false;
    }
    quantidade -= qtd;
    return true;
}
