#include "ComandoGrava.h"
#include <utility>

ComandoGrava::ComandoGrava(std::string nome, std::string resto) noexcept
    : nome(std::move(nome)), resto(std::move(resto)) {}

bool ComandoGrava::validar() const {
    return !nome.empty() && resto.empty();
}

std::string ComandoGrava::getAjuda() const {
    return "grava <nome>\n"
           "  Significado: Salvaguarda em memoria uma copia do estado completo da fabrica sob o nome indicado.\n"
           "  Condicoes em que falha: nome em falta ou argumentos extra.\n"
           "  Exemplo: grava antes";
}

std::string ComandoGrava::executar([[maybe_unused]] Fabrica& fabrica, [[maybe_unused]] Simulador& simulador) {
    return "Comando 'grava' validado com sucesso (funcionalidade de snapshots reservada para a entrega final).";
}
