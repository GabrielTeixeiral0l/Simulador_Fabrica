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
    explicit ComandoRecupera(bool);
    const char* getNome() const noexcept override;
    Comando* criarComArgs(std::istringstream& iss) const override;

    bool validar() const override;
    std::string getAjuda() const override;
    std::string executar(Fabrica& fabrica, Simulador& simulador) override;
};

#endif // SIMULADOR_COMANDORECUPERA_H
