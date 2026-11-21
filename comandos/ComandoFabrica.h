#ifndef SIMULADOR_COMANDOFABRICA_H
#define SIMULADOR_COMANDOFABRICA_H

#include "Comando.h"
#include <sstream>
#include <string>

class ComandoFabrica : public Comando {
    std::string linhas;
    std::string colunas;
    std::string resto;

public:
    ComandoFabrica(std::string linhas, std::string colunas, std::string resto = "") noexcept;
    ~ComandoFabrica() noexcept override = default;
    static Comando* criarDeStream(std::istringstream& iss);

    bool validar() const override;
    std::string getAjudaSimples() const override;
    std::string getAjuda() const override;
    std::string executar(Fabrica& fabrica, Simulador& simulador) override;
    bool requerFabrica() const noexcept override;
};

#endif // SIMULADOR_COMANDOFABRICA_H
