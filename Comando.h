#ifndef SIMULADOR_COMANDO_H
#define SIMULADOR_COMANDO_H

#include <string>
#include <vector>

class Fabrica;
class Simulador;

class Comando {
public:
    Comando() noexcept = default;
    virtual ~Comando() noexcept = default;

    virtual bool validar() const = 0;
    virtual std::string getAjuda() const = 0;
    virtual std::string executar(Fabrica& fabrica, Simulador& simulador) = 0;

    static Comando* criar(const std::string& linhaComando);
    static const std::vector<std::string>& getListaNomesComandos();
    static std::string obterAjudaComando(const std::string& nome);
};

#endif // SIMULADOR_COMANDO_H
