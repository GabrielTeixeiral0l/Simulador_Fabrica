#ifndef SIMULADOR_DEPOSITO_H
#define SIMULADOR_DEPOSITO_H

#include "Terreno.h"
#include <string>

class Deposito : public Terreno {
private:
    char simbolo;
    std::string nome;
    int quantidade;

public:
    Deposito(char simbolo, std::string nome, int quantidade) noexcept;
    ~Deposito() noexcept override = default;

    char getSimbolo() const noexcept override;
    std::string getDescricao() const override;
    int getQuantidade() const noexcept override;
    bool extrair(int quantidadeExtrair = 1) noexcept override;
    Terreno* clone() const override;
};

#endif // SIMULADOR_DEPOSITO_H
