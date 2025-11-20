#include "menu/informes/MenuInformes.h"
#include "manager/ManagerTurno.h"
#include "manager/ManagerProtocolo.h"
#include "manager/ManagerAnalisisProtocolo.h"
#include "archivo/ArchivoTipoAnalisis.h"
#include "utils/rlutil.h"
#include "utils/Fecha.h"
#include <iostream>


void analisisMesTipo() {
    Fecha fecha;
    Fecha fechaTurno;

    ArchivoTipoAnalisis arTipoAnalisis;
    ManagerAnalisisProtocolo mAnalisisP;
    ManagerProtocolo mProto;
    ManagerTurno mTurno;

    AnalisisProtocolo auxAnalisisP;
    Protocolo auxProto;
    Turno auxTurno;

    int acumTipoAnalisis[500] = {0};

    for (int i = 0; i < mTurno.getRepositorio().cantidadRegistros(); i ++) {
        auxTurno = mTurno.getRepositorio().leer(i);

        // Fechas coinciden
        if (auxTurno.getFechaAtencion().getMes() == fecha.getMes() && auxTurno.getFechaAtencion().getAnio() == fecha.getAnio()) {
            for (int j = 0; j < mProto.getRepositorio().cantidadRegistros(); j ++) {
                if (auxProto.getIdTurno() != auxTurno.getID()) { continue; }
                // IDs turno coinciden
                auxProto = mProto.getRepositorio().leer(j);

                for (int k = 0; k < mAnalisisP.getRepositorio().cantidadRegistros(); k ++) {
                    auxAnalisisP = mAnalisisP.getRepositorio().leer(k);

                    // IDs protocolo coinciden
                    if (auxAnalisisP.getIdProtocolo() == auxProto.getId()) {
                        acumTipoAnalisis[auxAnalisisP.getTipoAnalisis().getID()] ++;
                    }
                }
            }
        }
    }

    std::cout << "-- Analisis realizados en este mes --\n";

    for (int i = 0; i < 500; i ++) {
        if (acumTipoAnalisis[i] > 0) {
            std::cout << arTipoAnalisis.leer(i).getNombreAnalisis() << ": " << acumTipoAnalisis[i] << "\n";
        }
    }
    std::cout << "\nPresione ENTER para volver\n";
    rlutil::anykey();
}

void analisisMesOS() {

}




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
    if (_opcionSeleccionada == 0) { return; }
    if (_opcionSeleccionada == 1) { return analisisMesTipo(); }
    if (_opcionSeleccionada == 2) { return analisisMesOS(); }

}
