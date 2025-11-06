#include "utils/funcFrontend.h"
#include "utils/rlutil.h"


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


std::string separador(){
    std::string separador = "";

    for (int i=0; i<rlutil::tcols(); i++) {
        separador += "-";
    }

    std::cout << separador << '\n';
}


std::string separadorParcial(){
    std::string separador = "";

    for (int i=0; i<rlutil::tcols() / 2; i++) {
        separador += "-";
    }

    std::cout << separador << '\n';
}
