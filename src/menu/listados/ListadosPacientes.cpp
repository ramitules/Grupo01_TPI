#include "menu/listados/ListadosPacientes.h"
#include "manager/ManagerPaciente.h"
#include <iostream>


ListadosPacientes::ListadosPacientes(): Menu(3, "Menu Listados"){
    std::string opciones[4] = {
        "Ordenados por apellido",
        "Ordenados por DNI",
        "Ordenados por edad",
        "Agrupados por obra social"
    };

    setVectorOpciones(opciones);
    setSalir(false);
}

void ListadosPacientes::ejecutarOpcion(){
    if (_opcionSeleccionada == 0) {
        return;
    }

    ManagerPaciente mPaciente;

    if (_opcionSeleccionada == 1) {
        mPaciente.ordenadosApellido();
        return;
    }

    if (_opcionSeleccionada == 2) {
        mPaciente.ordenadosDNI();
        return;
    }

    if (_opcionSeleccionada == 3) {
        mPaciente.ordenadosEdad();
        return;
    }

    if (_opcionSeleccionada == 4) {
        mPaciente.ordenadosObraSocial();
        return;
    }

    std::cout << "Opcion fuera de rango. Intente nuevamente.\n";
}

void ListadosPacientes::mostrarOpciones(){
    std::cout << getNombreMenu() << "\n";
    std::cout << "==============================\n";

    std::cout << "- Listados de pacientes\n";

    for (int i = 1; i < _cantidadOpciones + 1; i++) {
        std::cout << "     " << i << ". " << _opciones[i - 1] << '\n';
    }

    std::cout << '\n';
    std::cout << "  Listados de analisis\n";
    std::cout << "  Listados de turnos\n";
    std::cout << "  Listados de obras sociales\n";
    std::cout << "------------------------------\n";
    std::cout << "0. Volver\n";
}