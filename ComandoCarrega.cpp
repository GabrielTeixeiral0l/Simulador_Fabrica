#include "ComandoCarrega.h"
#include "Fabrica.h"
#include <utility>

ComandoCarrega::ComandoCarrega(std::string nomeFicheiro) noexcept
    : nomeFicheiro(std::move(nomeFicheiro)) {}

std::string ComandoCarrega::executar(Fabrica& fabrica, [[maybe_unused]] Simulador& simulador) {
    if (fabrica.carregarFicheiro(nomeFicheiro)) {
        return "Ficheiro '" + nomeFicheiro + "' carregado com sucesso.";
    }
    return "Erro ao carregar ficheiro '" + nomeFicheiro + "'.";
}
