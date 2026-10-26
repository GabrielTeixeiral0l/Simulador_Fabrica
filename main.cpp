#include <iostream>
#include "Ecra.h"
#include "Fabrica.h"

int main() {
    Fabrica fabrica(10, 15);

    int larguraTotal = fabrica.getColunas() + 5 + 1 + 35;
    int alturaTotal = fabrica.getLinhas() + 3;
    if (alturaTotal < 14) {
        alturaTotal = 14;
    }

    Ecra ecra(alturaTotal, larguraTotal);
    fabrica.desenhar(ecra);
    ecra.mostrar();

    std::cout << std::endl;
    std::cout << fabrica.getInfoPosicao("aa") << std::endl;

    return 0;
}