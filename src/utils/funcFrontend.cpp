#include "utils/funcFrontend.h"
#include "utils/rlutil.h"
#include <iostream>


void buscando(){
    std::cout << "\nBuscando ";
    rlutil::msleep(500);
    std::cout << ". ";
    rlutil::msleep(500);
    std::cout << ". ";
    rlutil::msleep(500);
    std::cout << ". ";
    rlutil::msleep(500);
    std::cout << "\n";
}

void pausa() {
    std::cout << "Presione una tecla para continuar...";
    rlutil::anykey();
}

void menuVolver() {
    std::cout << "\nVOLVIENDO AL MENU. ";
    pausa();
}


void separador(){
    std::string separador = "";

    for (int i=0; i<rlutil::tcols(); i++) {
        separador += "-";
    }

    std::cout << separador << '\n';
}


void separadorParcial(){
    std::string separador = "";

    for (int i=0; i<rlutil::tcols() / 2; i++) {
        separador += "-";
    }

    std::cout << separador << '\n';
}
