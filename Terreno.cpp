#include "Terreno.h"
#include <sstream>

Terreno::Terreno() noexcept
    : simbolo(' '), nome(""), quantidade(0) {}

Terreno::Terreno(char simbolo, std::string nome, int quantidade) noexcept
    : simbolo(simbolo), nome(std::move(nome)), quantidade(quantidade) {}

Terreno Terreno::criarSolo() noexcept {
    return Terreno(' ', "", 0);
}

Terreno Terreno::criarCratera() noexcept {
    return Terreno('#', "", 0);
}

Terreno Terreno::criarDeposito(char simbolo, const std::string& nome, int quantidade) noexcept {
    return Terreno(simbolo, nome, quantidade);
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

bool Terreno::extrair(int quantidadeExtrair) noexcept {
    if (quantidadeExtrair <= 0 || quantidade < quantidadeExtrair) {
        return false;
    }
    quantidade -= quantidadeExtrair;
    return true;
}
