#ifndef SIMULADOR_TERRENO_H
#define SIMULADOR_TERRENO_H

#include <string>

class Terreno {
public:
    virtual ~Terreno();

    virtual char getSimbolo() const noexcept;
    virtual std::string getDescricao() const;
};

class Solo : public Terreno {
public:
    ~Solo() override;

    char getSimbolo() const noexcept override;
    std::string getDescricao() const override;
};

class Cratera : public Terreno {
public:
    ~Cratera() override;

    char getSimbolo() const noexcept override;
    std::string getDescricao() const override;
};

class Deposito : public Terreno {
    std::string nome;
    char simbolo;
    int quantidade;

public:
    Deposito(const std::string& n, char s, int q);
    ~Deposito() override;

    char getSimbolo() const noexcept override;
    std::string getDescricao() const override;

    const std::string& getNome() const noexcept;
    int getQuantidade() const noexcept;
    bool extrair(int qtd = 1) noexcept;
};

#endif // SIMULADOR_TERRENO_H
