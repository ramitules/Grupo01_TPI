#include "menu/MenuEnfermero.h"
#include "manager/ManagerEnfermero.h"
#include "Enfermero.h"
#include <iostream>


MenuEnfermero::MenuEnfermero(): Menu(5, "Menu Enfermero"){
    std::string opciones[5] = {
        "Ingresar nuevo enfermero",
        "Modificar enfermero",
        "Mostrar Enfermero",
        "Mostrar todos",
        "Eliminar enfermero"
    };

    setVectorOpciones(opciones);
    setSalir(false);
}

void MenuEnfermero::ejecutarOpcion(){
    ManagerEnfermero mEnfermero;
    Enfermero enfermero;

    int dniEnfermero;
    bool seleccion = false;

    switch (_opcionSeleccionada) {
        case 0:
            return;
        case 1:
            std::cout << getNombreMenu() << ": " << _opciones[1] << "\n";
            std::cout << "==============================\n";

            mEnfermero.cargar();
            system("pause");
            break;
        case 2:
            std::cout << getNombreMenu() << ": " << _opciones[0] << "\n";
            std::cout << "==============================\n";


            system("pause");
            break;
        case 3:
            std::cout << getNombreMenu() << ": " << _opciones[2] << "\n";
            std::cout << "==============================\n";


            system("pause");
            break;
        case 4:
            std::cout << getNombreMenu() << ": " << _opciones[2] << "\n";
            std::cout << "==============================\n";

            if (mEnfermero.comprobar()) {
                mEnfermero.mostrarTodos();
            }

            system("pause");
            break;
        case 5:
            std::cout << getNombreMenu() << ": " << _opciones[2] << "\n";
            std::cout << "==============================\n";


            system("pause");
            break;
        default:
            std::cout << "Intente nuevamente\n";
            break;
    }
}
