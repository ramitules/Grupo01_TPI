#include "menu/MenuEnfermero.h"
#include "manager/ManagerEnfermero.h"
#include "utils/rlutil.h"
#include <iostream>


MenuEnfermero::MenuEnfermero(): Menu(4, "Menu Enfermero"){
    std::string opciones[4] = {
        "Nuevo enfermero",
        "Modificar enfermero",
        "Eliminar enfermero",
        "Mostrar todos"
    };

    setVectorOpciones(opciones);
    setSalir(false);
}

void MenuEnfermero::ejecutarOpcion(){
    if (_opcionSeleccionada == 0) {
        return;
    }

    ManagerEnfermero mEnf;

    if (_opcionSeleccionada == 1) {
        mEnf.cargar();
        return;
    }

    if (_opcionSeleccionada == 4) {
        mEnf.mostrarTodos();
        std::cout << "Presione ENTER para continuar";
        rlutil::anykey();
        return;
    }

    if (_opcionSeleccionada < 0 || _opcionSeleccionada > _cantidadOpciones) {
        std::cout << "Opcion fuera de rango. Intente nuevamente.\n";
        return;
    }

    int opcionSecundaria = 0;
    int posEnfermero = -1;

    std::cout << "Si conoce el DNI del enfermero, ingreselo a continuacion (0 = listar todos | -1 = salir): ";
    std::cin >> opcionSecundaria;

    if (opcionSecundaria < 0) {
        return;
    }

    if (opcionSecundaria == 0) {
        // Mostrar todos los enfermeros por pantalla
        // Esto sirve para modificacion y eliminacion por igual
        mEnf.mostrarTodos();

        while (true) {
            std::cout << "Ingrese el DNI del enfermero, o 0 para cancelar: ";
            std::cin >> opcionSecundaria;

            if (opcionSecundaria == 0) {
                return;
            }

            posEnfermero = (mEnf.getRepositorio().getPos(opcionSecundaria));

            if (posEnfermero != -1) {
                break;
            }

            std::cout << "El enfermero no existe. Intente nuevamente.\n";
        }
    } else if (opcionSecundaria > 0){
        // Con un ID especifico, no se permite intentar nuevamente (sin ciclo while)
        posEnfermero = (mEnf.getRepositorio().getPos(opcionSecundaria));

        if (posEnfermero == -1) {
            std::cout << "El enfermero no existe. Presione ENTER para volver.\n";
            rlutil::anykey();
            return;
        }
    }

    Enfermero enfermero = mEnf.getRepositorio().leer(posEnfermero);
    
    if (_opcionSeleccionada == 2) {
        mEnf.actualizar(enfermero);
        return;
    }
    
    if (_opcionSeleccionada == 3) {
        mEnf.eliminar(enfermero);
        return;
    }
}
