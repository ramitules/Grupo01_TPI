#include "menu/listados/ListadosTurnos.h"
#include "manager/ManagerTurno.h"
#include <iostream>


ListadosTurnos::ListadosTurnos(): Menu(1, "Menu Listados"){
    std::string opciones[1] = {
        "Ordenados por fecha"
    };

    setVectorOpciones(opciones);
    setSalir(false);
}

void ListadosTurnos::ejecutarOpcion(){
    if (_opcionSeleccionada == 0) {
        return;
    }

    if (_opcionSeleccionada == 1) {
        ManagerTurno mTurno;
        mTurno.ordenadosFecha();
        return;
    }

    std::cout << "Opcion fuera de rango. Intente nuevamente.\n";
}

void ListadosTurnos::mostrarOpciones(){
    std::cout << getNombreMenu() << "\n";
    std::cout << "==============================\n";

    std::cout << "  Listados de pacientes\n";
    std::cout << "  Listados de analisis\n";
    std::cout << "- Listados de turnos\n";

    for (int i = 1; i < _cantidadOpciones + 1; i++) {
        std::cout << "     " << i << ". " << _opciones[i - 1] << '\n';
    }

    std::cout << '\n';
    std::cout << "  Listados de obras sociales\n";
    std::cout << "------------------------------\n";
    std::cout << "0. Volver\n";
}