#include <iostream>
#include "include/utils/rlutil.h"
#include "include/menu/MenuPrincipal.h"
#include "include/archivo/Archivo.h"


int main(){
    Archivo temp("", "base_de_datos");

    if (!temp.existeRuta()) {
        std::cout << "                          !!        ADVERTENCIA        !!\n\n";
        std::cout << "                   No se ha encontrado la carpeta 'base_de_datos'.\n";
        std::cout << "No se puede continuar. Por favor, asegurese que la carpeta este creada al lado de su programa.\n\n";
        std::cout << "Presione ENTER para salir";
        rlutil::getkey();
        return 0;
    }

    MenuPrincipal menu;
    menu.buclePrincipal();
    return 0;
}
