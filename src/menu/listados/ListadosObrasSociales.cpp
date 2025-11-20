#include "menu/listados/ListadosObrasSociales.h"
#include "manager/ManagerObraSocial.h"
#include <iostream>


ListadosObrasSociales::ListadosObrasSociales(): Menu(2, "Menu Listados"){
    std::string opciones[2] = {
        "Ordenadas por nombre",
        "Agrupadas por cantidad de pacientes"
    };

    setVectorOpciones(opciones);
    setSalir(false);
}

void ListadosObrasSociales::ejecutarOpcion(){
    if (_opcionSeleccionada == 0) {
        return;
    }

    ManagerObraSocial mOS;

    if (_opcionSeleccionada == 1) { return mOS.ordenadosNombre(); }
    if (_opcionSeleccionada == 2) { return mOS.agrupadosPacientes(); }

    std::cout << "Opcion fuera de rango. Intente nuevamente.\n";
}

void ListadosObrasSociales::mostrarOpciones(){
    std::cout << getNombreMenu() << "\n";
    std::cout << "==============================\n";

    std::cout << "  Listados de pacientes\n";
    std::cout << "  Listados de analisis\n";
    std::cout << "  Listados de turnos\n";
    std::cout << "- Listados de obras sociales\n";

    for (int i = 1; i < _cantidadOpciones + 1; i++) {
        std::cout << "     " << i << ". " << _opciones[i - 1] << '\n';
    }

    std::cout << '\n';
    std::cout << "------------------------------\n";
    std::cout << "0. Volver\n";
}