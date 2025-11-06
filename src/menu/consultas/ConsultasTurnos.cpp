#include "menu/consultas/ConsultasTurnos.h"
#include "manager/ManagerTurno.h"
#include <iostream>


ConsultasTurnos::ConsultasTurnos(): Menu(2, "Menu Consultas"){
    std::string opciones[2] = {
        "Busqueda por fecha",
        "Busqueda por paciente"
    };

    setVectorOpciones(opciones);
    setSalir(false);
}

void ConsultasTurnos::ejecutarOpcion(){
    if (_opcionSeleccionada == 0) {
        return;
    }

    ManagerTurno mTurno;

    if (_opcionSeleccionada == 1) {
        mTurno.busquedaFecha();
        return;
    }

    if (_opcionSeleccionada == 2) {
        mTurno.busquedaPaciente();
        return;
    }

    std::cout << "Opcion fuera de rango. Intente nuevamente.\n";
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
