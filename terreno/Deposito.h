#ifndef SIMULADOR_DEPOSITO_H
#define SIMULADOR_DEPOSITO_H

#include "Terreno.h"
#include <string>

class Deposito : public Terreno {
    char simbolo;
    std::string nome;
    int quantidade;
    char getSimboloTerreno() const noexcept override;

public:
    Deposito(char simbolo, const std::string& nome, int quantidade);
    ~Deposito() noexcept override;

    std::string getDescricao() const override;
    bool podeConstruir() const noexcept override;
    int getQuantidade() const noexcept override;
    bool extrair(int quantidadeExtrair = 1) noexcept override;
    std::string getNome() const;

    Item* criarItem() const;
};

#endif // SIMULADOR_DEPOSITO_H
