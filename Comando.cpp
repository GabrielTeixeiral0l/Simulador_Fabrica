#include "Comando.h"
#include "ComandoCarrega.h"
#include "ComandoCria.h"
#include "ComandoInfo.h"
#include "ComandoExec.h"
#include "ComandoSair.h"
#include <sstream>

Comando* Comando::criar(const std::string& linhaComando) {
    std::istringstream iss(linhaComando);
    std::string nomeCmd;

    if (!(iss >> nomeCmd)) {
        return nullptr;
    }

    if (nomeCmd == "carrega") {
        std::string ficheiro;
        if (iss >> ficheiro) {
            return new ComandoCarrega(ficheiro);
        }
        return nullptr;
    }

    if (nomeCmd == "cria") {
        int linhas, colunas;
        if (iss >> linhas >> colunas) {
            return new ComandoCria(linhas, colunas);
        }
        return nullptr;
    }

    if (nomeCmd == "info") {
        std::string coord;
        if (iss >> coord) {
            return new ComandoInfo(coord);
        }
        return nullptr;
    }

    if (nomeCmd == "exec") {
        std::string ficheiro;
        if (iss >> ficheiro) {
            return new ComandoExec(ficheiro);
        }
        return nullptr;
    }

    if (nomeCmd == "sair") {
        return new ComandoSair();
    }

    return nullptr;
}
