#include "Terreno.h"
#include <sstream>

Terreno::Terreno() noexcept
    : simbolo(' '), nome(""), quantidade(0) {}

Terreno::Terreno(char s, std::string n, int q) noexcept
    : simbolo(s), nome(std::move(n)), quantidade(q) {}

Terreno Terreno::criarSolo() noexcept {
    return Terreno(' ', "", 0);
}

Terreno Terreno::criarCratera() noexcept {
    return Terreno('#', "", 0);
}

Terreno Terreno::criarDeposito(char s, const std::string& n, int q) noexcept {
    return Terreno(s, n, q);
}

char Terreno::getSimbolo() const noexcept {
    return simbolo;
}

std::string Terreno::getDescricao() const {
    if (simbolo == '#') {
        return "Cratera";
    }
    if (simbolo == ' ') {
        return "Solo vazio";
    }
    std::ostringstream oss;
    oss << "Deposito de " << nome << " (" << quantidade << " unidades)";
    return oss.str();
}

const std::string& Terreno::getNome() const noexcept {
    return nome;
}

int Terreno::getQuantidade() const noexcept {
    return quantidade;
}

bool Terreno::podeConstruir() const noexcept {
    return simbolo != '#';
}

bool Terreno::extrair(int qtd) noexcept {
    if (qtd <= 0 || quantidade < qtd) {
        return false;
    }
    quantidade -= qtd;
    return true;
}
