#include "menu/MenuObraSocial.h"
#include "manager/ManagerObraSocial.h"

#include <iostream>


MenuObraSocial::MenuObraSocial(): Menu(4, "Menu Obras Sociales"){
    std::string opciones[4] = {
        "Nueva obra social",
        "Modificar obra social",
        "Eliminar obra social",
        "Mostrar todas"
    };

    setVectorOpciones(opciones);
    setSalir(false);
}

void MenuObraSocial::ejecutarOpcion(){
    if (_opcionSeleccionada == 0) {
        return;
    }

    ManagerObraSocial mObraSocial;

    if (_opcionSeleccionada == 1) {
        mObraSocial.cargar();
        return;
    }

    if (_opcionSeleccionada == 4) {
        mObraSocial.mostrarTodos();
        std::cout << "Presione ENTER para continuar";
        std::cin.get();
        return;
    }

    if (_opcionSeleccionada < 0 || _opcionSeleccionada > _cantidadOpciones) {
        std::cout << "Opcion fuera de rango. Intente nuevamente.\n";
        return;
    }

    int opcionSecundaria = 0;
    int posObraSocial = -1;

    std::cout << "Si conoce el ID de la obra social, ingreselo a continuacion (0 = listar todas | -1 = salir): ";
    std::cin >> opcionSecundaria;

    if (opcionSecundaria < 0) {
        return;
    }

    if (opcionSecundaria == 0) {
        // Mostrar todas las obras sociales por pantalla
        // Esto sirve para modificacion y eliminacion por igual
        mObraSocial.mostrarTodos();

        while (true) {
            std::cout << "Ingrese el ID de la obra social, o 0 para cancelar: ";
            std::cin >> opcionSecundaria;

            if (opcionSecundaria == 0) {
                return;
            }

            posObraSocial = (mObraSocial.getRepositorio().getPos(opcionSecundaria));

            if (posObraSocial != -1) {
                break;
            }

            std::cout << "La obra social no existe. Intente nuevamente.\n";
        }
    } else if (opcionSecundaria > 0){
        // Con un ID especifico, no se permite intentar nuevamente (sin ciclo while)
        posObraSocial = (mObraSocial.getRepositorio().getPos(opcionSecundaria));

        if (posObraSocial == -1) {
            std::cout << "La obra social no existe. Presione ENTER para volver.\n";
            std::cin.get();
            return;
        }
    }

    ObraSocial obraSocial = mObraSocial.getRepositorio().leer(posObraSocial);

    if (obraSocial.getID() == 1) {
        std::cout << "La obra social por defecto no puede ser modificada o eliminada. Presione ENTER para volver.\n";
        std::cin.get();
        return;
    }
    
    if (_opcionSeleccionada == 2) {
        mObraSocial.actualizar(obraSocial);
        return;
    }
    
    if (_opcionSeleccionada == 3) {
        mObraSocial.eliminar(obraSocial);
        return;
    }
}
