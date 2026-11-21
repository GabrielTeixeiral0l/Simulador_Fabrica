#include "Armazem.h"
#include <sstream>

using std::string;

Armazem::Armazem() noexcept
    : itens(nullptr), quantidade(0) {}

Armazem::~Armazem() {
    if (itens != nullptr) {
        for (int i = 0; i < quantidade; ++i) {
            delete itens[i];
        }
        delete[] itens;
        itens = nullptr;
    }
    quantidade = 0;
}

bool Armazem::adicionarItem(Item* item) {
    if (item == nullptr) {
        return false;
    }

    Item** novo = new Item*[quantidade + 1];
    for (int i = 0; i < quantidade; ++i) {
        novo[i] = itens[i];
    }
    novo[quantidade++] = item;

    delete[] itens;
    itens = novo;
    return true;
}

Item* Armazem::obterItemMaisAntigo() const noexcept {
    if (quantidade == 0 || itens == nullptr) {
        return nullptr;
    }
    return itens[0];
}

bool Armazem::removerItemMaisAntigo(Item*& itemRemovido) {
    if (quantidade <= 0 || itens == nullptr) {
        itemRemovido = nullptr;
        return false;
    }

    itemRemovido = itens[0];
    --quantidade;

    Item** novo = (quantidade > 0) ? new Item*[quantidade] : nullptr;
    for (int i = 0; i < quantidade; ++i) {
        novo[i] = itens[i + 1];
    }

    delete[] itens;
    itens = novo;
    return true;
}

bool Armazem::descartarItemMaisAntigo() noexcept {
    Item* descartado = nullptr;
    if (removerItemMaisAntigo(descartado)) {
        delete descartado;
        return true;
    }
    return false;
}

int Armazem::getQuantidadeTotal() const noexcept {
    return quantidade;
}

string Armazem::getInfoEstado() const {
    std::ostringstream oss;
    oss << "Silo (" << quantidade << " itens guardados)";
    if (quantidade == 0 || itens == nullptr) {
        return oss.str() + ": vazio";
    }

    oss << ": proximo=" << itens[0]->getNome();
    return oss.str();
} // TODO (se der tempo) pensar como fazer uma listagem que apareça item: quantidade, para cada item