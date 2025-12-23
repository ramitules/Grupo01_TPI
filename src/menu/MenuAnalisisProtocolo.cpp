#include "menu/MenuAnalisisProtocolo.h"
#include <iostream>
#include "manager/ManagerAnalisisProtocolo.h"
#include "manager/ManagerProtocolo.h"
#include "manager/ManagerTipoAnalisis.h"


MenuAnalisisProtocolo::MenuAnalisisProtocolo(): Menu(2, "Menu Analisis Protocolo"){
    std::string opciones[2] = {
        "Agregar estudios",
        "Modificar estudios",
    };

    setVectorOpciones(opciones);
    setSalir(false);
}

void MenuAnalisisProtocolo::ejecutarOpcion(){
    ManagerProtocolo mProtocolo;
    ManagerAnalisisProtocolo mAnalisisProtocolo;
    ManagerTipoAnalisis mTipoAnalisis;
    TipoAnalisis tipoAnalisis;
    int idProtocolo;

    switch (_opcionSeleccionada) {
        case 0:
            return;
        case 1:
            std::cout << getNombreMenu() << ": " << _opciones[0] << "\n";
            std::cout << "==============================\n";

            if (mProtocolo.comprobar()) {
                std::cout << "Ingrese ID del Protocolo a cargar: ";
                std::cin >> idProtocolo;

                if (mProtocolo.comprobar(idProtocolo)){

                    mAnalisisProtocolo.cargar(idProtocolo);
                }
            }
            system("pause");
            break;
        case 2:
            std::cout << getNombreMenu() << ": " << _opciones[1] << "\n";
            std::cout << "==============================\n";

            std::cout << "Ingrese ID del Protocolo a cargar: ";
            std::cin >> idProtocolo;

            mAnalisisProtocolo.mostrarTodos(idProtocolo);


            system("pause");
            break;
        default:
            std::cout << "Intente nuevamente\n";
            break;
    }
}
