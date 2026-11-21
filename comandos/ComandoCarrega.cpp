#include "ComandoCarrega.h"
#include "../Fabrica.h"

#include <sstream>
#include <utility>

using std::string;

ComandoCarrega::ComandoCarrega(string nomeFicheiro, string resto) noexcept
    : nomeFicheiro(std::move(nomeFicheiro)), resto(std::move(resto)) {}

bool ComandoCarrega::validar() const {
    return !nomeFicheiro.empty() && resto.empty();
}

string ComandoCarrega::getAjudaSimples() const {
    return "carrega <nome-do-ficheiro>";
}

string ComandoCarrega::getAjuda() const {
    return getAjudaSimples() + "\n"
           "  Significado: Cria fabrica a partir do ficheiro de mapa indicado.\n"
           "  Condicoes em que falha: ficheiro em falta, inexistente ou com formato invalido.\n"
           "  Exemplo: carrega mapa1.txt";
}

string ComandoCarrega::executar(Fabrica& fabrica, Simulador&) {
    if (fabrica.getLinhas() > 0) {
        return "Erro: a fabrica ja foi criada e nao pode ser recriada.";
    }
    if (fabrica.carregarFicheiro(nomeFicheiro)) {
        return "Ficheiro '" + nomeFicheiro + "' carregado com sucesso.";
    }
    return "Erro ao carregar ficheiro '" + nomeFicheiro + "' (ficheiro inexistente ou formato invalido).";
}

Comando* ComandoCarrega::criarDeStream(std::istringstream& iss) {
    string nomeFicheiro;
    string resto;
    iss >> nomeFicheiro >> resto;
    return new ComandoCarrega(nomeFicheiro, resto);
}

bool ComandoCarrega::requerFabrica() const noexcept {
    return false;
}
