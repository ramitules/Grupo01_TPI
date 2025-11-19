#include "menu/MenuTurno.h"
#include "manager/ManagerTurno.h"
#include <iostream>


MenuTurno::MenuTurno(): Menu(4, "Menu Turno"){
    std::string opciones[4] = {
        "Crear nuevo turno",
        "Modificar turno",
        "Eliminar turno",
        "Mostrar todos"
    };

    setVectorOpciones(opciones);
    setSalir(false);
}

void MenuTurno::ejecutarOpcion(){
    if (_opcionSeleccionada == 0) {
        return;
    }

    ManagerTurno mTurno;

    if (_opcionSeleccionada == 1) {
        mTurno.cargar();
        return;
    }

    if (_opcionSeleccionada == 4) {
        mTurno.mostrarTodos();
        return;
    }

    if (_opcionSeleccionada < 0 || _opcionSeleccionada > _cantidadOpciones) {
        std::cout << "Opcion fuera de rango. Intente nuevamente.\n";
        return;
    }

    int opcionSecundaria = 0;
    int posTurno = -1;

    std::cout << "Si conoce el ID del turno, ingreselo a continuacion (0 = listar todos | -1 = salir): ";
    std::cin >> opcionSecundaria;

    if (opcionSecundaria < 0) {
        return;
    }

    if (opcionSecundaria == 0) {
        // Mostrar todos los turnos por pantalla
        // Esto sirve para modificacion y eliminacion por igual
        mTurno.mostrarTodos();

        while (true) {
            std::cout << "Ingrese el ID del turno, o 0 para cancelar: ";
            std::cin >> opcionSecundaria;

            if (opcionSecundaria == 0) {
                return;
            }

            posTurno = (mTurno.getRepositorio().getPos(opcionSecundaria));

            if (posTurno != -1) {
                break;
            }

            std::cout << "El ID ingresado no existe. Intente nuevamente\n";
        }
    } else if (opcionSecundaria > 0){
        // Con un ID especifico, no se permite intentar nuevamente (sin ciclo while)
        posTurno = (mTurno.getRepositorio().getPos(opcionSecundaria));

        if (posTurno == -1) {
            std::cout << "El turno no existe.\n";
            return;
        }
    }

    Turno turno = mTurno.getRepositorio().leer(posTurno);

    if (_opcionSeleccionada == 2) {
        mTurno.actualizar(turno);
        return;
    }

    if (opcionSecundaria == 3) {
        mTurno.eliminar(turno);
        return;
    }
}
