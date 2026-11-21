#ifndef SIMULADOR_COMANDO_H
#define SIMULADOR_COMANDO_H

#include <sstream>
#include <string>

class Fabrica;
class Simulador;

class Comando {
    Comando* proximo = nullptr;
    bool prototipo = false;
    static Comando* cabeca;

    static const Comando* encontrarPrototipo(const std::string& nome) noexcept;

protected:
    explicit Comando(bool registarComoPrototipo);

public:
    Comando() noexcept = default;
    virtual ~Comando() noexcept;

    virtual const char* getNome() const noexcept = 0;
    virtual bool validar() const = 0;
    virtual std::string getAjuda() const = 0;
    virtual std::string executar(Fabrica& fabrica, Simulador& simulador) = 0;
    virtual Comando* criarComArgs(std::istringstream& iss) const = 0;
    virtual bool requerFabrica() const noexcept { return true; }

    static Comando* criar(const std::string& linhaComando);
    static int getTotalComandos() noexcept;
    static std::string getNomeComando(int indice);
    static std::string obterAjudaComando(const std::string& nome);
};

#endif // SIMULADOR_COMANDO_H
