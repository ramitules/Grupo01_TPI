#include "menu/MenuTurno.h"
#include <iostream>


MenuTurno::MenuTurno(): Menu(3, "Menu Turno"){
    std::string opciones[3] = {
        "Crear nuevo turno",
        "Modificar turno",
        "Eliminar turno"
    };

    setVectorOpciones(opciones);
    setSalir(false);
}

void MenuTurno::ejecutarOpcion(){
    switch (_opcionSeleccionada) {
        case 0:
            return;

        default:
            std::cout << "Intente nuevamente\n";
            break;
    }
}
