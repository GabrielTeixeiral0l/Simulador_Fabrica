#include "ComandoExecuta.h"
#include "Simulador.h"
#include <fstream>
#include <utility>

ComandoExecuta::ComandoExecuta(std::string ficheiro, std::string resto) noexcept
    : ficheiro(std::move(ficheiro)), resto(std::move(resto)) {}

bool ComandoExecuta::validar() const {
    return !ficheiro.empty() && resto.empty();
}

std::string ComandoExecuta::getAjuda() const {
    return "executa <nome-do-ficheiro>\n"
           "  Significado: Le e executa comandos linha a linha a partir do ficheiro indicado.\n"
           "  Condicoes em que falha: ficheiro em falta ou inacessivel.\n"
           "  Exemplo: executa teste1.txt";
}

std::string ComandoExecuta::executar(Fabrica&, Simulador& simulador) {
    std::ifstream f(ficheiro);
    if (!f.is_open()) {
        return "Erro ao abrir ficheiro '" + ficheiro + "'.";
    }

    std::string linha;
    int contador = 0;
    while (std::getline(f, linha)) {
        if (!linha.empty()) {
            simulador.processarLinha(linha);
            ++contador;
        }
    }
    return "Ficheiro '" + ficheiro + "' executado (" + std::to_string(contador) + " linhas).";
}
