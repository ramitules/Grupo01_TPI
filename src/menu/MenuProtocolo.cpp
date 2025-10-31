#include "menu/MenuProtocolo.h"
#include <iostream>


MenuProtocolo::MenuProtocolo(): Menu(3, "Menu Protocolo"){
    std::string opciones[3] = {
        "Crear nuevo protocolo",
        "Modificar protocolo",
        "Eliminar protocolo"
    };

    setVectorOpciones(opciones);
    setSalir(false);
}

void MenuProtocolo::ejecutarOpcion(){
    switch (_opcionSeleccionada) {
        case 0:
            return;

        default:
            std::cout << "Intente nuevamente\n";
            break;
    }
}
