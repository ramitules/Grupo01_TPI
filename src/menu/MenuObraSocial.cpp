#include "menu/MenuObraSocial.h"
#include <iostream>


MenuObraSocial::MenuObraSocial(): Menu(3, "Menu Obras Sociales"){
    std::string opciones[3] = {
        "Ingresar nueva obra social",
        "Modificar obra social",
        "Eliminar obra social"
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
