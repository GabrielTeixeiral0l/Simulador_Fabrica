#include "Comando.h"
#include "ComandoFabrica.h"
#include "ComandoCarrega.h"
#include "ComandoExecuta.h"
#include "ComandoCompra.h"
#include "ComandoVende.h"
#include "ComandoRoda.h"
#include "ComandoAvanca.h"
#include "ComandoEstado.h"
#include "ComandoLPosicao.h"
#include "ComandoAjuda.h"
#include "ComandoFim.h"
#include "ComandoMelhora.h"
#include "ComandoContrata.h"
#include "ComandoAtribui.h"
#include "ComandoDespede.h"
#include "ComandoGrava.h"
#include "ComandoRecupera.h"

#include <sstream>
using std::string;


static const char* NOMES_COMANDOS[] = {
    "fabrica", "carrega", "executa", "compra", "vende", "roda",
    "avanca", "estado", "lposicao", "ajuda", "fim", "melhora",
    "contrata", "atribui", "despede", "grava", "recupera"
};
static const int TOTAL_COMANDOS = static_cast<int>(std::size(NOMES_COMANDOS));

bool Comando::requerFabrica() const noexcept {
    return true;
}

int Comando::getTotalComandos() noexcept {
    return TOTAL_COMANDOS;
}

string Comando::getNomeComando(int indice) {
    if (indice < 0 || indice >= TOTAL_COMANDOS) return "";
    return NOMES_COMANDOS[indice];
}

static string obterTextoAjuda(const string& nome, bool simples) {
    if (nome.empty()) return "";
    Comando* cmd = Comando::criar(nome);
    if (!cmd) return "";
    string out = simples ? cmd->getAjudaSimples() : cmd->getAjuda();
    delete cmd;
    return out;
}

string Comando::obterAjudaSimplesComando(const string& nome) {
    return obterTextoAjuda(nome, true);
}

string Comando::obterAjudaComando(const string& nome) {
    return obterTextoAjuda(nome, false);
}

Comando* Comando::criar(const string& linhaComando) {
    std::istringstream iss(linhaComando);
    string nomeCmd;
    if (!(iss >> nomeCmd)) {
        return nullptr;
    }
    if (nomeCmd == "fabrica") return ComandoFabrica::criarDeStream(iss);
    if (nomeCmd == "carrega") return ComandoCarrega::criarDeStream(iss);
    if (nomeCmd == "executa") return ComandoExecuta::criarDeStream(iss);
    if (nomeCmd == "compra") return ComandoCompra::criarDeStream(iss);
    if (nomeCmd == "vende") return ComandoVende::criarDeStream(iss);
    if (nomeCmd == "roda") return ComandoRoda::criarDeStream(iss);
    if (nomeCmd == "avanca") return ComandoAvanca::criarDeStream(iss);
    if (nomeCmd == "estado") return ComandoEstado::criarDeStream(iss);
    if (nomeCmd == "lposicao") return ComandoLPosicao::criarDeStream(iss);
    if (nomeCmd == "ajuda") return ComandoAjuda::criarDeStream(iss);
    if (nomeCmd == "fim") return ComandoFim::criarDeStream(iss);
    if (nomeCmd == "melhora") return ComandoMelhora::criarDeStream(iss);
    if (nomeCmd == "contrata") return ComandoContrata::criarDeStream(iss);
    if (nomeCmd == "atribui") return ComandoAtribui::criarDeStream(iss);
    if (nomeCmd == "despede") return ComandoDespede::criarDeStream(iss);
    if (nomeCmd == "grava") return ComandoGrava::criarDeStream(iss);
    if (nomeCmd == "recupera") return ComandoRecupera::criarDeStream(iss);
    return nullptr;
}
