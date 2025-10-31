#include "menu/MenuPrincipal.h"
#include "menu/MenuProtocolo.h"
#include "menu/MenuEnfermero.h"
#include "menu/MenuTurno.h"
#include "menu/MenuTipoAnalisis.h"
#include "menu/MenuPaciente.h"
#include "menu/MenuObraSocial.h"
#include "menu/listados/MenuListados.h"
#include "menu/consultas/MenuConsultas.h"
#include "menu/informes/MenuInformes.h"
#include <iostream>


MenuPrincipal::MenuPrincipal(): Menu(8, "Menu Principal"){
    std::string opciones[9] = {
        "Turnos",
        "Pacientes",
        "Protocolos",
        "Tipos de analisis",
        "Enfermeros",
        "Obras sociales",
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
        MenuProtocolo menu;
        menu.buclePrincipal();
    } else if (_opcionSeleccionada == 4) {
        MenuTipoAnalisis menu;
        menu.buclePrincipal();
    } else if (_opcionSeleccionada == 5) {
        MenuEnfermero menu;
        menu.buclePrincipal();
    } else if (_opcionSeleccionada == 6) {
        MenuObraSocial menu;
        menu.buclePrincipal();
    } else if (_opcionSeleccionada == 7) {
        MenuListados menu;
        menu.buclePrincipal();
    }  else if (_opcionSeleccionada == 8) {
        MenuConsultas menu;
        menu.buclePrincipal();
    }  else if (_opcionSeleccionada == 9) {
        MenuInformes menu;
        menu.buclePrincipal();
    } else {
        std::cout << "Intente nuevamente\n";
        return;
    }
    
    setOpcionSeleccionada(99);
}
