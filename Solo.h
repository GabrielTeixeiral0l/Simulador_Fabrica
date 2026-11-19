#ifndef SIMULADOR_SOLO_H
#define SIMULADOR_SOLO_H

#include "Terreno.h"
#include "Maquina.h"

class Solo : public Terreno {
private:
    Maquina* maquina;

public:
    Solo() noexcept;
    ~Solo() noexcept override;
    Solo(const Solo& outro);
    Solo& operator=(const Solo& outro);

    char getSimbolo() const noexcept override;
    std::string getDescricao() const override;
    bool podeConstruir() const noexcept override;
    Terreno* clone() const override;

    bool colocarMaquina(Maquina* novaMaquina) noexcept;
    Maquina* removerMaquina() noexcept;
    const Maquina* getMaquina() const noexcept;
    Maquina* getMaquina() noexcept;
};

#endif // SIMULADOR_SOLO_H
