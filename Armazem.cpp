#include "Armazem.h"
#include <sstream>

using std::string;

Armazem::Armazem() noexcept
    : itens(nullptr), quantidade(0) {}

Armazem::~Armazem() {
    libertarItens();
}

Armazem::Armazem(const Armazem& outro)
    : itens(nullptr), quantidade(0) {
    if (outro.quantidade > 0 && outro.itens != nullptr) {
        itens = new Item*[outro.quantidade];
        quantidade = outro.quantidade;
        for (int i = 0; i < quantidade; ++i) {
            itens[i] = outro.itens[i] != nullptr ? outro.itens[i]->clone() : nullptr;
        }
    }
}

Armazem& Armazem::operator=(const Armazem& outro) {
    if (this != &outro) {
        libertarItens();
        if (outro.quantidade > 0 && outro.itens != nullptr) {
            itens = new Item*[outro.quantidade];
            quantidade = outro.quantidade;
            for (int i = 0; i < quantidade; ++i) {
                itens[i] = outro.itens[i] != nullptr ? outro.itens[i]->clone() : nullptr;
            }
        }
    }
    return *this;
}

void Armazem::libertarItens() noexcept {
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
    novo[quantidade] = item;

    delete[] itens;
    itens = novo;
    ++quantidade;
    return true;
}

Item* Armazem::obterItemMaisAntigo() const noexcept {
    if (quantidade == 0 || itens == nullptr) {
        return nullptr;
    }
    return itens[0];
}

bool Armazem::removerItemMaisAntigo(Item*& itemRemovido) {
    if (quantidade == 0 || itens == nullptr) {
        itemRemovido = nullptr;
        return false;
    }

    itemRemovido = itens[0];

    if (quantidade == 1) {
        delete[] itens;
        itens = nullptr;
        quantidade = 0;
        return true;
    }

    Item** novo = new Item*[quantidade - 1];
    for (int i = 1; i < quantidade; ++i) {
        novo[i - 1] = itens[i];
    }

    delete[] itens;
    itens = novo;
    --quantidade;
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

int Armazem::getQuantidadePorTipo(const string& nome) const noexcept {
    int contagem = 0;
    for (int i = 0; i < quantidade; ++i) {
        if (itens[i] != nullptr && itens[i]->getNome() == nome) {
            ++contagem;
        }
    }
    return contagem;
}

string Armazem::getInfoEstado() const {
    std::ostringstream oss;
    oss << "Silo (" << quantidade << " itens guardados)";
    if (quantidade == 0) {
        oss << ": vazio";
        return oss.str();
    }

    oss << ":";
    string tiposRegistados[32];
    int contagens[32];
    int totalTipos = 0;

    for (int i = 0; i < quantidade; ++i) {
        if (itens[i] == nullptr) {
            continue;
        }
        string nomeItem = itens[i]->getNome();
        int encontrado = -1;
        for (int j = 0; j < totalTipos; ++j) {
            if (tiposRegistados[j] == nomeItem) {
                encontrado = j;
                break;
            }
        }

        if (encontrado >= 0) {
            contagens[encontrado]++;
        } else if (totalTipos < 32) {
            tiposRegistados[totalTipos] = nomeItem;
            contagens[totalTipos] = 1;
            ++totalTipos;
        }
    }

    for (int i = 0; i < totalTipos; ++i) {
        oss << " " << tiposRegistados[i] << "=" << contagens[i];
    }

    return oss.str();
}
