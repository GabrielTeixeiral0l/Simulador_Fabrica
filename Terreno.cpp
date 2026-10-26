#include "Terreno.h"
#include <sstream>

Terreno::~Terreno() {}

char Terreno::getSimbolo() const noexcept {
    return ' ';
}

std::string Terreno::getDescricao() const {
    return "Terreno";
}

Solo::Solo() noexcept {}

Solo::~Solo() {}

char Solo::getSimbolo() const noexcept {
    return ' ';
}

std::string Solo::getDescricao() const {
    return "Solo vazio";
}

Cratera::Cratera() noexcept {}

Cratera::~Cratera() {}

char Cratera::getSimbolo() const noexcept {
    return '#';
}

std::string Cratera::getDescricao() const {
    return "Cratera";
}

Deposito::Deposito(const std::string& n, char s, int q)
    : nome(n), simbolo(s), quantidade(q) {}

Deposito::~Deposito() {}

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
