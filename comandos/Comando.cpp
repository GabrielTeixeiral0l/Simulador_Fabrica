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

const std::vector<string>& Comando::getListaNomesComandos() {
    static const std::vector<string> lista = {
        "fabrica",
        "carrega",
        "avanca",
        "compra",
        "vende",
        "roda",
        "melhora",
        "contrata",
        "atribui",
        "despede",
        "estado",
        "lposicao",
        "grava",
        "recupera",
        "executa",
        "ajuda",
        "fim"
    };
    return lista;
}

string Comando::obterAjudaComando(const string& nome) {
    if (nome == "fabrica") {
        ComandoFabrica c("", "");
        return c.getAjuda();
    }
    if (nome == "carrega") {
        ComandoCarrega c("");
        return c.getAjuda();
    }
    if (nome == "executa") {
        ComandoExecuta c("");
        return c.getAjuda();
    }
    if (nome == "compra") {
        ComandoCompra c("", "");
        return c.getAjuda();
    }
    if (nome == "vende") {
        ComandoVende c("");
        return c.getAjuda();
    }
    if (nome == "roda") {
        ComandoRoda c("");
        return c.getAjuda();
    }
    if (nome == "avanca") {
        ComandoAvanca c("");
        return c.getAjuda();
    }
    if (nome == "estado") {
        ComandoEstado c("");
        return c.getAjuda();
    }
    if (nome == "lposicao") {
        ComandoLPosicao c("");
        return c.getAjuda();
    }
    if (nome == "ajuda") {
        ComandoAjuda c("");
        return c.getAjuda();
    }
    if (nome == "fim") {
        ComandoFim c("");
        return c.getAjuda();
    }
    if (nome == "melhora") {
        ComandoMelhora c("");
        return c.getAjuda();
    }
    if (nome == "contrata") {
        ComandoContrata c("");
        return c.getAjuda();
    }
    if (nome == "atribui") {
        ComandoAtribui c("", "");
        return c.getAjuda();
    }
    if (nome == "despede") {
        ComandoDespede c("");
        return c.getAjuda();
    }
    if (nome == "grava") {
        ComandoGrava c("");
        return c.getAjuda();
    }
    if (nome == "recupera") {
        ComandoRecupera c("");
        return c.getAjuda();
    }
    return "";
}

Comando* Comando::criar(const string& linhaComando) {
    std::istringstream iss(linhaComando);
    string nomeCmd;

    if (!(iss >> nomeCmd)) {
        return nullptr;
    }

    if (nomeCmd == "fabrica") {
        string nl, nc, resto;
        iss >> nl >> nc;
        iss >> resto;
        return new ComandoFabrica(nl, nc, resto);
    }

    if (nomeCmd == "carrega") {
        string fich, resto;
        iss >> fich;
        iss >> resto;
        return new ComandoCarrega(fich, resto);
    }

    if (nomeCmd == "executa") {
        string fich, resto;
        iss >> fich;
        iss >> resto;
        return new ComandoExecuta(fich, resto);
    }

    if (nomeCmd == "compra") {
        string tipo, coord, dir, resto;
        iss >> tipo >> coord;
        if (iss >> dir) {
            iss >> resto;
        } else {
            dir = "c";
        }
        return new ComandoCompra(tipo, coord, dir, resto);
    }

    if (nomeCmd == "vende") {
        string coord, resto;
        iss >> coord;
        iss >> resto;
        return new ComandoVende(coord, resto);
    }

    if (nomeCmd == "roda") {
        string coord, dir, resto;
        iss >> coord;
        if (iss >> dir) {
            iss >> resto;
        }
        return new ComandoRoda(coord, dir, resto);
    }

    if (nomeCmd == "avanca") {
        string n, resto;
        if (iss >> n) {
            iss >> resto;
        }
        return new ComandoAvanca(n, resto);
    }

    if (nomeCmd == "estado") {
        string resto;
        iss >> resto;
        return new ComandoEstado(resto);
    }

    if (nomeCmd == "lposicao") {
        string coord, raio, resto;
        iss >> coord;
        if (iss >> raio) {
            iss >> resto;
        }
        return new ComandoLPosicao(coord, raio, resto);
    }

    if (nomeCmd == "ajuda") {
        string cmdAlvo, resto;
        if (iss >> cmdAlvo) {
            iss >> resto;
        }
        return new ComandoAjuda(cmdAlvo, resto);
    }

    if (nomeCmd == "fim") {
        string resto;
        iss >> resto;
        return new ComandoFim(resto);
    }

    if (nomeCmd == "melhora") {
        string coord, resto;
        iss >> coord;
        iss >> resto;
        return new ComandoMelhora(coord, resto);
    }

    if (nomeCmd == "contrata") {
        string nome, resto;
        iss >> nome;
        iss >> resto;
        return new ComandoContrata(nome, resto);
    }

    if (nomeCmd == "atribui") {
        string id, coord, resto;
        iss >> id >> coord;
        iss >> resto;
        return new ComandoAtribui(id, coord, resto);
    }

    if (nomeCmd == "despede") {
        string id, resto;
        iss >> id;
        iss >> resto;
        return new ComandoDespede(id, resto);
    }

    if (nomeCmd == "grava") {
        string nome, resto;
        iss >> nome;
        iss >> resto;
        return new ComandoGrava(nome, resto);
    }

    if (nomeCmd == "recupera") {
        string nome, resto;
        iss >> nome;
        iss >> resto;
        return new ComandoRecupera(nome, resto);
    }

    return nullptr;
}
