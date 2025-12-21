#include "menu/MenuPrincipal.h"
#include "menu/MenuProtocolo.h"
#include "menu/MenuEnfermero.h"
#include "menu/MenuTurno.h"
#include "menu/MenuTipoAnalisis.h"
#include "menu/MenuPaciente.h"
#include "menu/MenuObraSocial.h"
#include "menu/MenuConfiguracion.h"
#include "menu/listados/MenuListados.h"
#include "menu/consultas/MenuConsultas.h"
#include "menu/informes/MenuInformes.h"
#include "manager/ManagerTurno.h"
#include "utils/rlutil.h"
#include <iostream>


MenuPrincipal::MenuPrincipal(): Menu(10, "Menu Principal"){
    std::string opciones[10] = {
        "Turnos",
        "Pacientes",
        "Protocolos",
        "Tipos de analisis",
        "Enfermeros",
        "Obras sociales",
        "Modulo LISTADOS",
        "Modulo CONSULTAS",
        "Modulo INFORMES",
        "Configuracion"
    };

    setVectorOpciones(opciones);
}

void MenuPrincipal::ejecutarOpcion(){
    if (_opcionSeleccionada == 0) {
        return;
    }

    if (_opcionSeleccionada == 1) {

        // Antes de entrar al menu de Turnos, corroborar si el usuario desea actualizar 
        // el importe de los turnos existenes segun los protocolos creados
        /*
        std::cout << "\nDesea actualizar los importes de los turnos existentes segun los protocolos actuales? s/n: ";
        char opc;
        std::cin >> opc;
        if (opc == 's') {
            ManagerTurno mTurno;
            mTurno.actualizarImportesSeleccionados();
        }
        */
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
    } else if (_opcionSeleccionada == 10) {
        MenuConfiguracion menu;
        menu.buclePrincipal();
    } else {
        std::cout << "Intente nuevamente\n";
        return;
    }
    
    setOpcionSeleccionada(99);
}
