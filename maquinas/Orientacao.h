#ifndef SIMULADOR_ORIENTACAO_H
#define SIMULADOR_ORIENTACAO_H

#include <string>

class Orientacao {
    char direcao; // 'c', 'd', 'b', 'e'

public:
    static const char Norte = 'c';
    static const char Este = 'd';
    static const char Sul = 'b';
    static const char Oeste = 'e';

    Orientacao(char dir = Norte) noexcept;

    char getDirecao() const noexcept;
    std::string getNome() const;

    void rodar() noexcept;
    int getPassoLinha() const noexcept;
    int getPassoColuna() const noexcept;

    bool igualA(const Orientacao& outra) const noexcept;
    static Orientacao deChar(char c) noexcept;
};

#endif // SIMULADOR_ORIENTACAO_H
