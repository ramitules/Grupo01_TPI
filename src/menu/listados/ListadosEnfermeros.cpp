#include "menu/listados/ListadosEnfermeros.h"
#include "manager/ManagerEnfermero.h"
#include <iostream>


ListadosEnfermeros::ListadosEnfermeros(): Menu(3, "Menu Listados"){
    std::string opciones[3] = {
        "Ordenados por apellido",
        "Ordenados por DNI",
        "Ordenados por antiguedad"
    };

    setVectorOpciones(opciones);
    setSalir(false);
}

void ListadosEnfermeros::ejecutarOpcion(){
    if (_opcionSeleccionada == 0) {
        return;
    }
    ManagerEnfermero mEnf;

    if (_opcionSeleccionada == 1) { return mEnf.ordenadosApellido(); }
    if (_opcionSeleccionada == 2) { return mEnf.ordenadosDNI(); }
    if (_opcionSeleccionada == 3) { return mEnf.ordenadosAntiguedad(); }

    std::cout << "Opcion fuera de rango. Intente nuevamente.\n";
}

void ListadosEnfermeros::mostrarOpciones(){
    std::cout << getNombreMenu() << "\n";
    std::cout << "==============================\n";

    std::cout << "  Listados de pacientes\n";
    std::cout << "  Listados de analisis\n";
    std::cout << "  Listados de turnos\n";
    std::cout << "  Listados de obras sociales\n";
    std::cout << "- Listados de enfermeros\n";
    for (int i = 1; i < _cantidadOpciones + 1; i++) {
        std::cout << "     " << i << ". " << _opciones[i - 1] << '\n';
    }
    std::cout << '\n';
    std::cout << "------------------------------\n";
    std::cout << "0. Volver\n";
}