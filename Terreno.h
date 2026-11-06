#ifndef SIMULADOR_TERRENO_H
#define SIMULADOR_TERRENO_H

#include <string>

class Terreno {
    char simbolo;
    std::string nome;
    int quantidade;

public:
    Terreno() noexcept;
    Terreno(char simbolo, std::string nome = "", int quantidade = 0) noexcept;

    static Terreno criarSolo() noexcept;
    static Terreno criarCratera() noexcept;
    static Terreno criarDeposito(char simbolo, const std::string& nome, int quantidade) noexcept;

    char getSimbolo() const noexcept;
    std::string getDescricao() const;
    const std::string& getNome() const noexcept;
    int getQuantidade() const noexcept;

    bool podeConstruir() const noexcept;
    bool extrair(int quantidadeExtrair = 1) noexcept;
};

#endif // SIMULADOR_TERRENO_H
