#include "menu/consultas/ConsultasPacientes.h"
#include "manager/ManagerPaciente.h"
#include <iostream>


ConsultasPacientes::ConsultasPacientes(): Menu(3, "Menu Consultas"){
    std::string opciones[3] = {
        "Busqueda por DNI",
        "Busqueda por nombre completo",
        "Busqueda por obra social"
    };

    setVectorOpciones(opciones);
    setSalir(false);
}

void ConsultasPacientes::ejecutarOpcion(){
    if (_opcionSeleccionada == 0) {
        return;
    }

    ManagerPaciente mPaciente;

    if (_opcionSeleccionada == 1) { return mPaciente.busquedaDNI(); }
    if (_opcionSeleccionada == 2) { return mPaciente.busquedaNombreCompleto(); }
    if (_opcionSeleccionada == 3) { return mPaciente.busquedaObraSocial(); }
}

void ConsultasPacientes::mostrarOpciones(){
    std::cout << getNombreMenu() << "\n";
    std::cout << "==============================\n";

    std::cout << "- Consulta de pacientes\n";
    for (int i = 1; i < _cantidadOpciones + 1; i++) {
        std::cout << "     " << i << ". " << _opciones[i - 1] << '\n';
    }
    std::cout << '\n';
    std::cout << "  Consulta de analisis\n";
    std::cout << "  Consulta de turnos\n";
    std::cout << "  Consulta de obras sociales\n";
    std::cout << "------------------------------\n";
    std::cout << "0. Volver\n";
}
