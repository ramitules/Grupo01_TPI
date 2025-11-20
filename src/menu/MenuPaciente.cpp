#include "menu/MenuPaciente.h"
#include "manager/ManagerPaciente.h"
#include "utils/rlutil.h"
#include <iostream>


MenuPaciente::MenuPaciente(): Menu(4, "Menu Paciente"){
    std::string opciones[4] = {
        "Crear nuevo paciente",
        "Modificar paciente",
        "Eliminar paciente",
        "Mostrar todos"
    };

    setVectorOpciones(opciones);
    setSalir(false);
}

void MenuPaciente::ejecutarOpcion(){
    if (_opcionSeleccionada == 0) {
        return;
    }

    ManagerPaciente mPaciente;

    if (_opcionSeleccionada == 1) { 
        mPaciente.cargar(); 
        return;
    }

    if (_opcionSeleccionada == 4) {
        mPaciente.mostrarTodos();
        std::cout << "Presione ENTER para continuar";
        rlutil::anykey();
        return;
    }

    if (_opcionSeleccionada < 0 || _opcionSeleccionada > _cantidadOpciones) {
        std::cout << "Opcion fuera de rango. Intente nuevamente.\n";
        return;
    }

    int opcionSecundaria = 0;
    int posPaciente = -1;

    std::cout << "Si conoce el DNI del paciente, ingreselo a continuacion (0 = listar todos | -1 = salir): ";
    std::cin >> opcionSecundaria;

    if (opcionSecundaria < 0) {
        return;
    }

    if (opcionSecundaria == 0) {
        // Mostrar todos los pacientes por pantalla
        // Esto sirve para modificacion y eliminacion por igual
        mPaciente.mostrarTodos();

        while (true) {
            std::cout << "Ingrese el DNI del paciente, o 0 para cancelar: ";
            std::cin >> opcionSecundaria;

            if (opcionSecundaria == 0) {
                return;
            }

            posPaciente = (mPaciente.getRepositorio().getPos(opcionSecundaria));

            if (posPaciente != -1) {
                break;
            }

            std::cout << "El DNI ingresado no existe. Intente nuevamente\n";
        }

    } else if (opcionSecundaria > 0){
        // Con un ID especifico, no se permite intentar nuevamente (sin ciclo while)
        posPaciente = (mPaciente.getRepositorio().getPos(opcionSecundaria));

        if (posPaciente == -1) {
            std::cout << "El paciente no existe. Presione ENTER para volver.\n";
            rlutil::anykey();
            return;
        }
    }

    Paciente paciente = mPaciente.getRepositorio().leer(posPaciente);

    if (_opcionSeleccionada == 2) {
        mPaciente.actualizar(paciente);
        return;
    }

    if (opcionSecundaria == 3) {
        mPaciente.eliminar(paciente);
        return;
    }
}
