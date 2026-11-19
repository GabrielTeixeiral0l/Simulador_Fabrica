#include "Armazem.h"
#include <sstream>

Armazem::Armazem() noexcept
    : primeiro(nullptr), ultimo(nullptr), quantidade(0) {}

Armazem::~Armazem() {
    libertarItens();
}

void Armazem::libertarItens() noexcept {
    ElementoItem* atual = primeiro;
    while (atual != nullptr) {
        ElementoItem* seg = atual->proximo;
        delete atual;
        atual = seg;
    }
    primeiro = nullptr;
    ultimo = nullptr;
    quantidade = 0;
}

bool Armazem::adicionarItem(const std::string& tipo) {
    if (tipo.empty()) {
        return false;
    }

    ElementoItem* novo = new ElementoItem{tipo, nullptr};
    if (ultimo == nullptr) {
        primeiro = novo;
        ultimo = novo;
    } else {
        ultimo->proximo = novo;
        ultimo = novo;
    }
    ++quantidade;
    return true;
}

bool Armazem::removerItemMaisAntigo(std::string& tipoRemovido) {
    if (primeiro == nullptr) {
        return false;
    }

    ElementoItem* aRemover = primeiro;
    tipoRemovido = aRemover->tipo;
    primeiro = primeiro->proximo;
    if (primeiro == nullptr) {
        ultimo = nullptr;
    }

    delete aRemover;
    --quantidade;
    return true;
}

bool Armazem::removerItem(const std::string& tipo) {
    ElementoItem* anterior = nullptr;
    ElementoItem* atual = primeiro;

    while (atual != nullptr) {
        if (atual->tipo == tipo) {
            if (anterior == nullptr) {
                primeiro = atual->proximo;
            } else {
                anterior->proximo = atual->proximo;
            }

            if (atual == ultimo) {
                ultimo = anterior;
            }

            delete atual;
            --quantidade;
            return true;
        }
        anterior = atual;
        atual = atual->proximo;
    }

    return false;
}

int Armazem::getQuantidadeTotal() const noexcept {
    return quantidade;
}

int Armazem::getQuantidadePorTipo(const std::string& tipo) const noexcept {
    int contagem = 0;
    ElementoItem* atual = primeiro;
    while (atual != nullptr) {
        if (atual->tipo == tipo) {
            ++contagem;
        }
        atual = atual->proximo;
    }
    return contagem;
}

std::string Armazem::getInfoEstado() const {
    std::ostringstream oss;
    oss << "Armazem (" << quantidade << " itens guardados)";
    if (quantidade == 0) {
        oss << ": vazio";
        return oss.str();
    }

    oss << ":";
    struct TipoContagem {
        std::string tipo;
        int count;
    };

    TipoContagem contagens[32];
    int totalTipos = 0;

    ElementoItem* atual = primeiro;
    while (atual != nullptr) {
        int encontrado = -1;
        for (int i = 0; i < totalTipos; ++i) {
            if (contagens[i].tipo == atual->tipo) {
                encontrado = i;
                break;
            }
        }

        if (encontrado >= 0) {
            contagens[encontrado].count++;
        } else if (totalTipos < 32) {
            contagens[totalTipos].tipo = atual->tipo;
            contagens[totalTipos].count = 1;
            totalTipos++;
        }
        atual = atual->proximo;
    }

    for (int i = 0; i < totalTipos; ++i) {
        oss << " " << contagens[i].tipo << "=" << contagens[i].count;
    }

    return oss.str();
}
