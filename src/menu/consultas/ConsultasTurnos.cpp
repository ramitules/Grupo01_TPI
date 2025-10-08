#include "menu/consultas/ConsultasTurnos.h"
#include <iostream>


ConsultasTurnos::ConsultasTurnos(): Menu(3, "Menu Consultas"){
    std::string opciones[3] = {
        "Busqueda por fecha",
        "Busqueda por paciente",
        "Busqueda por tipo de analisis"
    };

    setVectorOpciones(opciones);
    setSalir(false);
}

void ConsultasTurnos::ejecutarOpcion(){
    if (_opcionSeleccionada == 0) {
        return;
    }
}

void ConsultasTurnos::mostrarOpciones(){
    std::cout << getNombreMenu() << "\n";
    std::cout << "==============================\n";

    std::cout << "  Consulta de pacientes\n";
    std::cout << "  Consulta de analisis\n";
    std::cout << "- Consulta de turnos\n";
    for (int i = 1; i < _cantidadOpciones + 1; i++) {
        std::cout << "     " << i << ". " << _opciones[i - 1] << '\n';
    }
    std::cout << '\n';
    std::cout << "  Consulta de obras sociales\n";
    std::cout << "------------------------------\n";
    std::cout << "0. Volver\n";
}
