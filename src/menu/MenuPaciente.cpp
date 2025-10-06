#include "menu/MenuPaciente.h"
#include <iostream>


MenuPaciente::MenuPaciente(): Menu(3, "Menu Paciente"){
    std::string opciones[3] = {
        "Crear nuevo paciente",
        "Modificar paciente",
        "Eliminar paciente"
    };

    setVectorOpciones(opciones);
    setSalir(false);
}

void MenuPaciente::ejecutarOpcion(){
    switch (_opcionSeleccionada) {
        case 0:
            return;

        default:
            std::cout << "Intente nuevamente\n";
            break;
    }
}
