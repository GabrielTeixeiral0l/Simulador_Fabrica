#ifndef SIMULADOR_COMANDORECUPERA_H
#define SIMULADOR_COMANDORECUPERA_H

#include "Comando.h"
#include <string>

class ComandoRecupera : public Comando {
    std::string nome;
    std::string resto;

public:
    ComandoRecupera(std::string nome, std::string resto = "") noexcept;
    ~ComandoRecupera() noexcept override = default;
    static Comando* criarDeStream(std::istringstream& iss);

    bool validar() const override;
    std::string getAjudaSimples() const override;
    std::string getAjuda() const override;
    static std::string ajuda();
    std::string executar(Fabrica& fabrica, Simulador& simulador) override;
};

#endif // SIMULADOR_COMANDORECUPERA_H
