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
    Solo() noexcept;
    ~Solo();

    char getSimbolo() const noexcept;
    std::string getDescricao() const;
};

class Cratera : public Terreno {
public:
    Cratera() noexcept;
    ~Cratera();

    char getSimbolo() const noexcept;
    std::string getDescricao() const;
};

class Deposito : public Terreno {
    std::string nome;
    char simbolo;
    int quantidade;

public:
    Deposito(const std::string& n, char s, int q);
    ~Deposito();

    char getSimbolo() const noexcept;
    std::string getDescricao() const;

    const std::string& getNome() const noexcept;
    int getQuantidade() const noexcept;
    bool extrair(int qtd = 1) noexcept;
};

#endif // SIMULADOR_TERRENO_H
