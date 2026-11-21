#include "ComandoExecuta.h"
#include "../Simulador.h"

#include <fstream>
#include <sstream>
#include <utility>

using std::string;

ComandoExecuta::ComandoExecuta(string nomeFicheiro, string resto) noexcept
    : nomeFicheiro(std::move(nomeFicheiro)), resto(std::move(resto)) {}

bool ComandoExecuta::validar() const {
    return !nomeFicheiro.empty() && resto.empty();
}

string ComandoExecuta::getAjudaSimples() const {
    return "executa <nome-do-ficheiro>";
}

string ComandoExecuta::getAjuda() const {
    return getAjudaSimples() + "\n"
           "  Significado: Le e executa comandos linha a linha a partir do ficheiro indicado.\n"
           "  Condicoes em que falha: ficheiro em falta ou inacessivel.\n"
           "  Exemplo: executa teste1.txt";
}

string ComandoExecuta::executar(Fabrica&, Simulador& simulador) {
    std::ifstream f(nomeFicheiro);
    if (!f.is_open()) {
        return "Erro ao abrir ficheiro '" + nomeFicheiro + "'.";
    }

    string linha;
    int contador = 0;
    while (std::getline(f, linha)) {
        if (!linha.empty()) {
            simulador.processarLinha(linha);
            ++contador;
        }
    }
    return "Ficheiro '" + nomeFicheiro + "' executado (" + std::to_string(contador) + " linhas).";
}

Comando* ComandoExecuta::criarDeStream(std::istringstream& iss) {
    string nomeFicheiro;
    string resto;
    iss >> nomeFicheiro >> resto;
    return new ComandoExecuta(nomeFicheiro, resto);
}

bool ComandoExecuta::requerFabrica() const noexcept {
    return false;
}
