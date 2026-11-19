#include "ComandoCria.h"
#include "Fabrica.h"

ComandoCria::ComandoCria(int linhas, int colunas) noexcept
    : linhas(linhas), colunas(colunas) {}

std::string ComandoCria::executar(Fabrica& fabrica, [[maybe_unused]] Simulador& simulador) {
    if (fabrica.gerarAleatoria(linhas, colunas)) {
        return "Fabrica criada com sucesso (" + std::to_string(linhas) + "x" + std::to_string(colunas) + ").";
    }
    return "Dimensoes invalidas para criar fabrica.";
}
