#include "menu/MenuTipoAnalisis.h"
#include <iostream>


MenuTipoAnalisis::MenuTipoAnalisis(): Menu(3, "Menu Tipos de Analisis"){
    std::string opciones[3] = {
        "Crear nuevo tipo de analisis",
        "Modificar tipo de analisis",
        "Eliminar tipo de analisis"
    };

    setVectorOpciones(opciones);
    setSalir(false);
}

void MenuTipoAnalisis::ejecutarOpcion(){
    switch (_opcionSeleccionada) {
        case 0:
            return;

        default:
            std::cout << "Intente nuevamente\n";
            break;
    }
}
