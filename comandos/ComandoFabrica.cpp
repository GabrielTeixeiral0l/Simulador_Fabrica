#include "ComandoFabrica.h"
#include "../FerramentasAuxiliares.h"
#include "../Fabrica.h"
#include "../Settings.h"

#include <sstream>
#include <utility>

using std::string;

ComandoFabrica::ComandoFabrica(string linhas, string colunas, string resto) noexcept
    : linhas(std::move(linhas)), colunas(std::move(colunas)), resto(std::move(resto)) {}

bool ComandoFabrica::validar() const {
    if (!resto.empty()) {
        return false;
    }
    if (!FerramentasAuxiliares::isNumeroPositivo(linhas) || !FerramentasAuxiliares::isNumeroPositivo(colunas)) {
        return false;
    }
    int numLinhas = FerramentasAuxiliares::converterInteiro(linhas);
    int numColunas = FerramentasAuxiliares::converterInteiro(colunas);
    return numLinhas >= 1 && numLinhas <= Settings::fabrica_max_linhas &&
           numColunas >= 1 && numColunas <= Settings::fabrica_max_colunas;
}

string ComandoFabrica::getAjudaSimples() const {
    return "fabrica <nl> <nc>";
}

string ComandoFabrica::getAjuda() const {
    return getAjudaSimples() + "\n"
           "  Significado: Cria fabrica aleatoria com nl linhas e nc colunas (maximo " +
           std::to_string(Settings::fabrica_max_linhas) + " linhas e " +
           std::to_string(Settings::fabrica_max_colunas) + " colunas).\n"
           "  Condicoes em que falha: argumentos nao numericos, dimensoes fora de [1, " +
           std::to_string(Settings::fabrica_max_linhas) + "/" +
           std::to_string(Settings::fabrica_max_colunas) + "], ou argumentos extra.\n"
           "  Exemplo: fabrica 12 20";
}

string ComandoFabrica::executar(Fabrica& fabrica, Simulador&) {
    if (fabrica.getLinhas() > 0) {
        return "Erro: a fabrica ja foi criada e nao pode ser recriada.";
    }
    int numLinhas = FerramentasAuxiliares::converterInteiro(linhas);
    int numColunas = FerramentasAuxiliares::converterInteiro(colunas);
    if (numLinhas < 1 || numLinhas > Settings::fabrica_max_linhas ||
        numColunas < 1 || numColunas > Settings::fabrica_max_colunas) {
        return "Erro: dimensoes fora do intervalo permitido (1 a " +
               std::to_string(Settings::fabrica_max_linhas) + " linhas e 1 a " +
               std::to_string(Settings::fabrica_max_colunas) + " colunas).";
    }
    if (fabrica.gerarAleatoria(numLinhas, numColunas)) {
        return "Fabrica criada com sucesso (" + std::to_string(numLinhas) + "x" + std::to_string(numColunas) + ").";
    }
    return "Erro ao criar fabrica com dimensoes fornecidas.";
}

Comando* ComandoFabrica::criarDeStream(std::istringstream& iss) {
    string linhas;
    string colunas;
    string resto;
    iss >> linhas >> colunas >> resto;
    return new ComandoFabrica(linhas, colunas, resto);
}

bool ComandoFabrica::requerFabrica() const noexcept {
    return false;
}
