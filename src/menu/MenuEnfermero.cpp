#include "menu/MenuEnfermero.h"
#include <iostream>


MenuEnfermero::MenuEnfermero(): Menu(3, "Menu Enfermero"){
    std::string opciones[3] = {
        "Crear nuevo enfermero",
        "Modificar enfermero",
        "Eliminar enfermero"
    };

    setVectorOpciones(opciones);
    setSalir(false);
}

void MenuEnfermero::ejecutarOpcion(){
    switch (_opcionSeleccionada) {
        case 0:
            return;

        default:
            std::cout << "Intente nuevamente\n";
            break;
    }
}
