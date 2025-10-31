#include "menu/MenuAnalisisProtocolo.h"
#include <iostream>


MenuAnalisisProtocolo::MenuAnalisisProtocolo(): Menu(3, "Menu Analisis Protocolo"){
    std::string opciones[3] = {
        "Agregar estudio al Protocolo",
        "Modificar estudio del protocolo",
        "Eliminar estudio del protocolo"
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
