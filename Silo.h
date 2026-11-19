#ifndef SIMULADOR_SILO_H
#define SIMULADOR_SILO_H

#include <string>

class Silo {
private:
    struct ElementoItem {
        std::string tipo;
        ElementoItem* proximo;
    };

    ElementoItem* primeiro;
    ElementoItem* ultimo;
    int quantidade;

    void libertarItens() noexcept;
    void copiarDe(const Silo& outro);

public:
    Silo() noexcept;
    ~Silo();
    Silo(const Silo& outro);
    Silo& operator=(const Silo& outro);

    bool adicionarItem(const std::string& tipo);
    bool removerItemMaisAntigo(std::string& tipoRemovido);
    bool removerItem(const std::string& tipo);

    int getQuantidadeTotal() const noexcept;
    int getQuantidadePorTipo(const std::string& tipo) const noexcept;
    std::string getInfoEstado() const;
};

#endif // SIMULADOR_SILO_H
