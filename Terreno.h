#ifndef SIMULADOR_TERRENO_H
#define SIMULADOR_TERRENO_H

#include <string>

class Terreno {
public:
    Terreno() noexcept = default;
    virtual ~Terreno() noexcept = default;

    virtual char getSimbolo() const noexcept = 0;
    virtual std::string getDescricao() const = 0;

    virtual bool podeConstruir() const noexcept;
    virtual bool extrair(int quantidade = 1) noexcept;
    virtual int getQuantidade() const noexcept;
};

#endif // SIMULADOR_TERRENO_H
