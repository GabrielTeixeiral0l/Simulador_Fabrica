#ifndef SIMULADOR_MAQUINA_H
#define SIMULADOR_MAQUINA_H

#include <string>
#include "Orientacao.h"

class Fabrica;
class Item;

class Maquina {
    static int proximoId;
    int id;
    Orientacao orientacao;
    int custo;
    bool ativo;

public:
    explicit Maquina(int custo, Orientacao orientacao = Orientacao::Norte) noexcept;
    virtual ~Maquina() noexcept;

    virtual char getSimbolo() const noexcept = 0;
    virtual std::string getDescricao() const = 0;
    virtual void operar(Fabrica& fabrica, int linha, int coluna) = 0;
    virtual bool aceitarItem(Item* item);

    void rodar() noexcept;
    void setOrientacao(Orientacao novaOrientacao) noexcept;
    Orientacao getOrientacao() const noexcept;
    char getOrientacaoChar() const noexcept;
    std::string getOrientacaoNome() const;

    int getId() const noexcept;
    int getCusto() const noexcept;
    bool isAtivo() const noexcept;
    void setAtivo(bool estado) noexcept;

    static Orientacao charParaOrientacao(char c) noexcept;
    static Maquina* criar(const std::string& tipo, Orientacao orientacao = Orientacao::Este);
};

#endif // SIMULADOR_MAQUINA_H
