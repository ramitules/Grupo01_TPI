#include "menu/consultas/MenuConsultas.h"
#include "menu/consultas/ConsultasAnalisis.h"
#include "menu/consultas/ConsultasPacientes.h"
#include "menu/consultas/ConsultasTurnos.h"
#include <iostream>


MenuConsultas::MenuConsultas(): Menu(4, "Menu Consultas"){
    std::string opciones[4] = {
        "Consulta de pacientes",
        "Consulta de analisis",
        "Consulta de turnos",
        "Consulta de obras sociales"
    };

    setVectorOpciones(opciones);
    setSalir(false);
}

void MenuConsultas::ejecutarOpcion(){
    if (_opcionSeleccionada == 0) {
        return;
    }

    // Consultas de obras sociales no implementada
    if (_opcionSeleccionada == 1) {
        ConsultasPacientes menu;
        menu.buclePrincipal();
    } else if (_opcionSeleccionada == 2){
        ConsultasAnalisis menu;
        menu.buclePrincipal();
    } else if (_opcionSeleccionada == 3){
        ConsultasTurnos menu;
        menu.buclePrincipal();
    } else {
        std::cout << "Intente nuevamente\n";
        return;
    }

    setOpcionSeleccionada(99);
}
