#include "menu/MenuPrincipal.h"
#include "menu/MenuAnalisis.h"
#include "menu/MenuEnfermero.h"
#include "menu/MenuTurno.h"
#include "menu/MenuTipoAnalisis.h"
#include "menu/MenuPaciente.h"
#include <iostream>


MenuPrincipal::MenuPrincipal(): Menu(8, "Menu Principal"){
    std::string opciones[8] = {
        "Turnos",
        "Pacientes",
        "Analisis",
        "Tipos de analisis",
        "Enfermeros",
        "Modulo LISTADOS",
        "Modulo CONSULTAS",
        "Modulo INFORMES"
    };

    setVectorOpciones(opciones);
}

void MenuPrincipal::ejecutarOpcion(){
    if (_opcionSeleccionada == 0) {
        return;
    }

    if (_opcionSeleccionada == 1) {
        MenuTurno menu;
        menu.buclePrincipal();
    } else if (_opcionSeleccionada == 2) {
        MenuPaciente menu;
        menu.buclePrincipal();
    } else if (_opcionSeleccionada == 3) {
        MenuAnalisis menu;
        menu.buclePrincipal();
    } else if (_opcionSeleccionada == 4) {
        MenuTipoAnalisis menu;
        menu.buclePrincipal();
    } else if (_opcionSeleccionada == 5) {
        MenuEnfermero menu;
        menu.buclePrincipal();
    } else {
        std::cout << "Intente nuevamente\n";
        return;
    }
    
    setOpcionSeleccionada(99);
}
