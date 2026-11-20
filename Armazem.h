#ifndef SIMULADOR_ARMAZEM_H
#define SIMULADOR_ARMAZEM_H

#include <string>

class Armazem {
    struct ElementoItem {
        std::string tipo;
        ElementoItem* proximo;
    };

    ElementoItem* primeiro;
    ElementoItem* ultimo;
    int quantidade;

    public:
    void libertarItens() noexcept;
    Armazem() noexcept;
    ~Armazem();
    Armazem(const Armazem&) = delete;
    Armazem& operator=(const Armazem&) = delete;

    bool adicionarItem(const std::string& tipo);
    bool obterItemMaisAntigo(std::string& tipo) const;
    bool removerItemMaisAntigo(std::string& tipoRemovido);
    bool removerItem(const std::string& tipo);

    int getQuantidadeTotal() const noexcept;
    int getQuantidadePorTipo(const std::string& tipo) const noexcept;
    std::string getInfoEstado() const;
};

#endif // SIMULADOR_ARMAZEM_H
