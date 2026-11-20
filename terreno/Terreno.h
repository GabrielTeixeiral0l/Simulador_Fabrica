#ifndef SIMULADOR_TERRENO_H
#define SIMULADOR_TERRENO_H

#include <string>
#include "../maquinas/Maquina.h"

class Terreno {
    Maquina* maquina;
    virtual char getSimboloTerreno() const noexcept = 0;

public:
    Terreno() noexcept;
    virtual ~Terreno() noexcept;
    Terreno(const Terreno&) = delete;
    Terreno& operator=(const Terreno&) = delete;

    char getSimbolo() const noexcept;
    virtual std::string getDescricao() const = 0;

    virtual bool podeConstruir() const noexcept;
    virtual bool extrair(int quantidade = 1) noexcept;
    virtual int getQuantidade() const noexcept;

    bool colocarMaquina(Maquina* novaMaquina) noexcept;
    Maquina* removerMaquina() noexcept;
    const Maquina* getMaquina() const noexcept;
    Maquina* getMaquina() noexcept;
};

#endif // SIMULADOR_TERRENO_H
