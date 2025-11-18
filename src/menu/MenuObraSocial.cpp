#include "menu/MenuObraSocial.h"
#include <iostream>


MenuObraSocial::MenuObraSocial(): Menu(4, "Menu Obras Sociales"){
    std::string opciones[4] = {
        "Ingresar nueva obra social",
        "Modificar obra social",
        "Eliminar obra social",
        "Mostrar todas"
    };

    setVectorOpciones(opciones);
    setSalir(false);
}

void MenuObraSocial::ejecutarOpcion(){
    switch (_opcionSeleccionada) {
        case 0:
            return;

        default:
            std::cout << "Intente nuevamente\n";
            break;
    }
}
