#include <iostream>
#include "include/utils/rlutil.h"
#include "include/menu/MenuPrincipal.h"
#include "include/archivo/ArchivoObraSocial.h"
#include "include/ObraSocial.h"


int main(){
    ArchivoObraSocial arOS;

    if (!arOS.existeRuta()) {
        std::cout << "                          !!        ADVERTENCIA        !!\n\n";
        std::cout << "                   No se ha encontrado la carpeta 'base_de_datos'.\n";
        std::cout << "No se puede continuar. Por favor, asegurese que la carpeta este creada al lado de su programa.\n\n";
        std::cout << "Presione ENTER para salir";
        rlutil::anykey();
        return 0;
    }

    // Datos minimos para el funcionamiento de la aplicacion
    if (arOS.cantidadRegistros() == 0) {
        // Cargar obra social generica
        ObraSocial OSGenerica(1, "Particular", "N/A", 0, "N/A");
        arOS.guardar(OSGenerica);
    }

    MenuPrincipal menu;
    menu.buclePrincipal();
    return 0;
}
