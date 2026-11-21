#ifndef SIMULADOR_COMANDOAJUDA_H
#define SIMULADOR_COMANDOAJUDA_H

#include "Comando.h"
#include <sstream>
#include <string>

class ComandoAjuda : public Comando {
    std::string comando;
    std::string resto;

public:
    ComandoAjuda(std::string comando = "", std::string resto = "") noexcept;
    ~ComandoAjuda() noexcept override = default;
    static Comando* criarDeStream(std::istringstream& iss);

    bool validar() const override;
    std::string getAjudaSimples() const override;
    std::string getAjuda() const override;
    std::string executar(Fabrica& fabrica, Simulador& simulador) override;
    bool requerFabrica() const noexcept override;
};

#endif // SIMULADOR_COMANDOAJUDA_H
