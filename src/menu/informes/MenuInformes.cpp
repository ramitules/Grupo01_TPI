#include "menu/informes/MenuInformes.h"
#include <iostream>


MenuInformes::MenuInformes(): Menu(7, "Menu Informes"){
    std::string opciones[7] = {
        "Cantidad de analisis realizados en el mes por tipo",
        "Cantidad de analisis realizados en el mes por Obra Social",
        "Pacientes atendidos por Obra Social",
        "Facturacion mensual total",
        "Facturacion mensual por Obra Social",
        "Cantidad de analisis por enfermero",
        "Tipo de analisis ordenados por recaudacion"
    };

    setVectorOpciones(opciones);
    setSalir(false);
}

void MenuInformes::ejecutarOpcion(){
    switch (_opcionSeleccionada) {
        case 0:
            return;

        default:
            std::cout << "Intente nuevamente\n";
            break;
    }
}
