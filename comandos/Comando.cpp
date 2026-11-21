#include "Comando.h"

using std::string;

Comando* Comando::cabeca = nullptr;

Comando::Comando(bool registarComoPrototipo) : proximo(nullptr), prototipo(registarComoPrototipo) {
    if (prototipo) {
        proximo = cabeca;
        cabeca = this;
    }
}

Comando::~Comando() noexcept {
    if (prototipo && cabeca != nullptr) {
        Comando* atual = cabeca;
        Comando* anterior = nullptr;
        while (atual != nullptr) {
            if (atual == this) {
                if (anterior == nullptr) {
                    cabeca = atual->proximo;
                } else {
                    anterior->proximo = atual->proximo;
                }
                break;
            }
            anterior = atual;
            atual = atual->proximo;
        }
    }
}

const Comando* Comando::encontrarPrototipo(const string& nome) noexcept {
    for (const Comando* atual = cabeca; atual != nullptr; atual = atual->proximo) {
        if (nome == atual->getNome()) {
            return atual;
        }
    }
    return nullptr;
}

int Comando::getTotalComandos() noexcept {
    int total = 0;
    for (const Comando* atual = cabeca; atual != nullptr; atual = atual->proximo) {
        ++total;
    }
    return total;
}

string Comando::getNomeComando(int indice) {
    if (indice < 0) return "";
    int pos = 0;
    for (const Comando* atual = cabeca; atual != nullptr; atual = atual->proximo) {
        if (pos == indice) {
            return atual->getNome();
        }
        ++pos;
    }
    return "";
}

string Comando::obterAjudaComando(const string& nome) {
    const Comando* proto = encontrarPrototipo(nome);
    return proto != nullptr ? proto->getAjuda() : "";
}

Comando* Comando::criar(const string& linhaComando) {
    std::istringstream iss(linhaComando);
    string nomeCmd;
    if (!(iss >> nomeCmd)) {
        return nullptr;
    }
    const Comando* proto = encontrarPrototipo(nomeCmd);
    return proto != nullptr ? proto->criarComArgs(iss) : nullptr;
}
