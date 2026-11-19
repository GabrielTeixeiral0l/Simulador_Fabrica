#include "ComandoSair.h"
#include "Simulador.h"

std::string ComandoSair::executar([[maybe_unused]] Fabrica& fabrica, Simulador& simulador) {
    simulador.parar();
    return "A sair do simulador...";
}
