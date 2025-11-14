#include "menu/MenuAnalisisProtocolo.h"
#include <iostream>


MenuAnalisisProtocolo::MenuAnalisisProtocolo(): Menu(4, "Menu Configuracion"){
    std::string opciones[4] = {
        "Realizar copia de seguridad",
        "Restaurar copia de seguridad",
        "Paleta de colores"
    };

    setVectorOpciones(opciones);
    setSalir(false);
}

void MenuAnalisisProtocolo::ejecutarOpcion(){
    switch (_opcionSeleccionada) {
        case 0:
            return;

        default:
            std::cout << "Intente nuevamente\n";
            break;
    }
}
