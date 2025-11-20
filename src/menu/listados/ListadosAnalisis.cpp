#include "menu/listados/ListadosAnalisis.h"
#include <iostream>

#include "manager/ManagerTipoAnalisis.h"


ListadosAnalisis::ListadosAnalisis(): Menu(2, "Menu Listados"){
    std::string opciones[2] = {
        "Agrupados por tipo (ordenados por valor)",
        "Agrupados por tipo (ordenados nombre de analisis)"
    };

    setVectorOpciones(opciones);
    setSalir(false);
}

void ListadosAnalisis::ejecutarOpcion(){
    ManagerTipoAnalisis mTipoAnalisis;

    if (_opcionSeleccionada == 0) {
        return;
    }

    if (_opcionSeleccionada == 1) {
        mTipoAnalisis.listadoXvalor();
        system("pause");
        return;
    }

    if (_opcionSeleccionada == 2) {

        mTipoAnalisis.listadoXnombre();
        system("pause");
        return;
    }
}

void ListadosAnalisis::mostrarOpciones(){
    std::cout << getNombreMenu() << "\n";
    std::cout << "==============================\n";

    std::cout << "  Listados de pacientes\n";
    std::cout << "- Listados de analisis\n";

    for (int i = 1; i < _cantidadOpciones + 1; i++) {
        std::cout << "     " << i << ". " << _opciones[i - 1] << '\n';
    }

    std::cout << '\n';
    std::cout << "  Listados de turnos\n";
    std::cout << "  Listados de obras sociales\n";
    std::cout << "------------------------------\n";
    std::cout << "0. Volver\n";
}