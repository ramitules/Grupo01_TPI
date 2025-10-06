#include "menu/MenuAnalisis.h"
#include <iostream>


MenuAnalisis::MenuAnalisis(): Menu(3, "Menu Analisis"){
    std::string opciones[3] = {
        "Crear nuevo analisis",
        "Modificar analisis",
        "Eliminar analisis"
    };

    setVectorOpciones(opciones);
    setSalir(false);
}

void MenuAnalisis::ejecutarOpcion(){
    switch (_opcionSeleccionada) {
        case 0:
            return;

        default:
            std::cout << "Intente nuevamente\n";
            break;
    }
}
