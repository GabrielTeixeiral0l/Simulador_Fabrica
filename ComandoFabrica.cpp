#include "ComandoFabrica.h"
#include "Fabrica.h"
#include "Settings.h"
#include <utility>

ComandoFabrica::ComandoFabrica(std::string argLinhas, std::string argColunas, std::string resto) noexcept
    : argLinhas(std::move(argLinhas)), argColunas(std::move(argColunas)), resto(std::move(resto)) {}

bool ComandoFabrica::validar() const {
    if (!resto.empty() || argLinhas.empty() || argColunas.empty()) {
        return false;
    }
    try {
        size_t idxL, idxC;
        int l = std::stoi(argLinhas, &idxL);
        int c = std::stoi(argColunas, &idxC);
        if (idxL != argLinhas.length() || idxC != argColunas.length()) {
            return false;
        }
        return (l >= 1 && l <= Settings::fabrica_max_linhas && c >= 1 && c <= Settings::fabrica_max_colunas);
    } catch (...) {
        return false;
    }
}

std::string ComandoFabrica::getAjuda() const {
    return "fabrica <nl> <nc>\n"
           "  Significado: Cria fabrica aleatoria com nl linhas e nc colunas (maximo 26 cada).\n"
           "  Condicoes em que falha: argumentos nao numericos, dimensoes fora de [1, 26], ou argumentos extra.\n"
           "  Exemplo: fabrica 12 20";
}

std::string ComandoFabrica::executar(Fabrica& fabrica, Simulador&) {
    int l = std::stoi(argLinhas);
    int c = std::stoi(argColunas);
    if (fabrica.gerarAleatoria(l, c)) {
        return "Fabrica criada com sucesso (" + std::to_string(l) + "x" + std::to_string(c) + ").";
    }
    return "Erro ao criar fabrica com dimensoes fornecidas.";
}
