#ifndef SIMULADOR_COMANDOCARREGA_H
#define SIMULADOR_COMANDOCARREGA_H

#include "Comando.h"
#include <sstream>
#include <string>

class ComandoCarrega : public Comando {
    std::string nomeFicheiro;
    std::string resto;

public:
    ComandoCarrega(std::string nomeFicheiro, std::string resto = "") noexcept;
    ~ComandoCarrega() noexcept override = default;
    static Comando* criarDeStream(std::istringstream& iss);

    bool validar() const override;
    std::string getAjudaSimples() const override;
    std::string getAjuda() const override;
    std::string executar(Fabrica& fabrica, Simulador& simulador) override;
    bool requerFabrica() const noexcept override;
};

#endif // SIMULADOR_COMANDOCARREGA_H
