#include "ComandoDespede.h"
#include <utility>

using std::string;

ComandoDespede::ComandoDespede(string argId, string resto) noexcept
    : argId(std::move(argId)), resto(std::move(resto)) {}

bool ComandoDespede::validar() const {
    if (!resto.empty() || argId.empty()) {
        return false;
    }
    try {
        size_t idx;
        int id = std::stoi(argId, &idx);
        return idx == argId.length() && id > 0;
    } catch (...) {
        return false;
    }
}

string ComandoDespede::getAjuda() const {
    return "despede <id>\n"
           "  Significado: Despede o engenheiro com o id indicado, cessando o pagamento de salario.\n"
           "  Condicoes em que falha: id invalido ou inexistente.\n"
           "  Exemplo: despede 2";
}

string ComandoDespede::executar(Fabrica&, Simulador&) {
    return "Comando 'despede' validado com sucesso (funcionalidade de engenheiros reservada para a entrega final).";
}

Comando* ComandoDespede::criarDeStream(std::istringstream& iss) {
    std::string id;
    std::string resto;
    iss >> id >> resto;
    return new ComandoDespede(id, resto);
}
