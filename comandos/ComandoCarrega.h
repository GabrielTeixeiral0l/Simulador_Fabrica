#ifndef SIMULADOR_COMANDOCARREGA_H
#define SIMULADOR_COMANDOCARREGA_H

#include "Comando.h"
#include <string>

class ComandoCarrega : public Comando {
    std::string ficheiro;
    std::string resto;

public:
    ComandoCarrega(std::string ficheiro, std::string resto = "") noexcept;
    ~ComandoCarrega() noexcept override = default;
    static Comando* criarDeStream(std::istringstream& iss);

    bool validar() const override;
    std::string getAjuda() const override;
    static std::string ajuda();
    std::string executar(Fabrica& fabrica, Simulador& simulador) override;
    bool requerFabrica() const noexcept override { return false; }
};

#endif // SIMULADOR_COMANDOCARREGA_H
