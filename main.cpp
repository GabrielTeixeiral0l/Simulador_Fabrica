#include <iostream>
#include "Ecra.h"
#include "Fabrica.h"

int main() {
    Fabrica fabrica(10, 15);

    Ecra ecra;

    fabrica.desenhar(ecra);
    ecra.mostrar();

    std::cout << std::endl;
    std::cout << fabrica.getInfoPosicao("aa") << std::endl;

    return 0;
}


/*int main() {
    Fabrica fabrica(10, 15);
    Ecra ecra;

    if (fabrica.carregarFicheiro("../mapa_teste.txt")) {
        std::cout << "Ficheiro carregado com sucesso!\n" << std::endl;
        fabrica.desenhar(ecra);
        ecra.mostrar();
    } else {
        std::cout << "Erro ao carregar o ficheiro mapa_teste.txt!" << std::endl;
    }

    return 0;
}*/