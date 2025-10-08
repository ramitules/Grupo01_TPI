#include "menu/listados/MenuListados.h"
#include "menu/listados/ListadosPacientes.h"
#include "menu/listados/ListadosAnalisis.h"
#include "menu/listados/ListadosTurnos.h"
#include "menu/listados/ListadosObrasSociales.h"
#include <iostream>


MenuListados::MenuListados(): Menu(4, "Menu Listados"){
    std::string opciones[4] = {
        "Listados de pacientes",
        "Listados de analisis",
        "Listados de turnos",
        "Listados de obras sociales"
    };

    setVectorOpciones(opciones);
    setSalir(false);
}

void MenuListados::ejecutarOpcion(){
    if (_opcionSeleccionada == 0) {
        return;
    }

    if (_opcionSeleccionada == 1) {
        ListadosPacientes menu;
        menu.buclePrincipal();
    } else if (_opcionSeleccionada == 2){
        ListadosAnalisis menu;
        menu.buclePrincipal();
    } else if (_opcionSeleccionada == 3){
        ListadosTurnos menu;
        menu.buclePrincipal();
    } else if (_opcionSeleccionada == 4){
        ListadosObrasSociales menu;
        menu.buclePrincipal();
    } else {
        std::cout << "Intente nuevamente\n";
        return;
    }

    setOpcionSeleccionada(99);
}
