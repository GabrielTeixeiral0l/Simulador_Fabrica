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

using std::string;

static constexpr const char* NOMES_COMANDOS[] = {
    "fabrica", "carrega", "executa", "compra", "vende", "roda",
    "avanca", "estado", "lposicao", "ajuda", "fim", "melhora",
    "contrata", "atribui", "despede", "grava", "recupera"
};
static constexpr int TOTAL_COMANDOS = static_cast<int>(std::size(NOMES_COMANDOS));

int Comando::getTotalComandos() noexcept {
    return TOTAL_COMANDOS;
}

string Comando::getNomeComando(int indice) {
    if (indice < 0 || indice >= TOTAL_COMANDOS) return "";
    return NOMES_COMANDOS[indice];
}

string Comando::obterAjudaComando(const string& nome) {
    if (nome == "fabrica") return ComandoFabrica("", "").getAjuda();
    if (nome == "carrega") return ComandoCarrega("").getAjuda();
    if (nome == "executa") return ComandoExecuta("").getAjuda();
    if (nome == "compra") return ComandoCompra("", "", "c").getAjuda();
    if (nome == "vende") return ComandoVende("").getAjuda();
    if (nome == "roda") return ComandoRoda("").getAjuda();
    if (nome == "avanca") return ComandoAvanca("").getAjuda();
    if (nome == "estado") return ComandoEstado().getAjuda();
    if (nome == "lposicao") return ComandoLPosicao("").getAjuda();
    if (nome == "ajuda") return ComandoAjuda("").getAjuda();
    if (nome == "fim") return ComandoFim().getAjuda();
    if (nome == "melhora") return ComandoMelhora("").getAjuda();
    if (nome == "contrata") return ComandoContrata("").getAjuda();
    if (nome == "atribui") return ComandoAtribui("", "").getAjuda();
    if (nome == "despede") return ComandoDespede("").getAjuda();
    if (nome == "grava") return ComandoGrava("").getAjuda();
    if (nome == "recupera") return ComandoRecupera("").getAjuda();
    return "";
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
