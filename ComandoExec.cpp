#include "ComandoExec.h"
#include "Simulador.h"
#include <fstream>
#include <utility>

ComandoExec::ComandoExec(std::string nomeFicheiro) noexcept
    : nomeFicheiro(std::move(nomeFicheiro)) {}

std::string ComandoExec::executar([[maybe_unused]] Fabrica& fabrica, Simulador& simulador) {
    std::ifstream ficheiro(nomeFicheiro);
    if (!ficheiro.is_open()) {
        return "Erro ao abrir ficheiro de comandos '" + nomeFicheiro + "'.";
    }

    std::string linha;
    int comandosExecutados = 0;
    while (std::getline(ficheiro, linha)) {
        if (!linha.empty()) {
            simulador.processarLinha(linha);
            ++comandosExecutados;
        }
    }

    return "Ficheiro '" + nomeFicheiro + "' executado (" + std::to_string(comandosExecutados) + " comandos).";
}
