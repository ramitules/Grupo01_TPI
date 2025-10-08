#include "menu/consultas/ConsultasAnalisis.h"
#include <iostream>


ConsultasAnalisis::ConsultasAnalisis(): Menu(3, "Menu Consultas"){
    std::string opciones[3] = {
        "Busqueda por tipo",
        "Busqueda por paciente",
        "Busqueda por Obra Social"
    };

    setVectorOpciones(opciones);
    setSalir(false);
}

void ConsultasAnalisis::ejecutarOpcion(){
    if (_opcionSeleccionada == 0) {
        return;
    }
}

void ConsultasAnalisis::mostrarOpciones(){
    std::cout << getNombreMenu() << "\n";
    std::cout << "==============================\n";

    std::cout << "  Consulta de pacientes\n";
    std::cout << "- Consulta de analisis\n";

    for (int i = 1; i < _cantidadOpciones + 1; i++) {
        std::cout << "     " << i << ". " << _opciones[i - 1] << '\n';
    }

    std::cout << '\n';
    std::cout << "  Consulta de turnos\n";
    std::cout << "  Consulta de obras sociales\n";
    std::cout << "------------------------------\n";
    std::cout << "0. Volver\n";
}
