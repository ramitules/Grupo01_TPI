#include "menu/MenuTipoAnalisis.h"
#include "manager/ManagerTipoAnalisis.h"
#include "TipoAnalisis.h"
#include <iostream>


MenuTipoAnalisis::MenuTipoAnalisis(): Menu(4, "Menu Tipos de Analisis"){
    std::string opciones[4] = {
        "Mostrar todos",
        "Cargar",
        "Modificar",

        "Eliminar"
    };

    setVectorOpciones(opciones);
    setSalir(false);
}

void MenuTipoAnalisis::ejecutarOpcion(){
    ManagerTipoAnalisis mTipoAnalisis;
    TipoAnalisis tipoAnalisis;
    bool seleccion = false;

    switch (_opcionSeleccionada) {
        case 0:
            return;
        case 1:
            std::cout << getNombreMenu() << ": " << _opciones[0] << "\n";
            std::cout << "==============================\n";
            mTipoAnalisis.mostrarTodos();
            system("pause");
            break;
        case 2:
            std::cout << getNombreMenu() << ": " << _opciones[1] << "\n";
            std::cout << "==============================\n";
            mTipoAnalisis.cargar();
            system("pause");
            break;
        case 3:
            std::cout << getNombreMenu() << ": " << _opciones[2] << "\n";
            std::cout << "==============================\n";

            seleccion = mTipoAnalisis.mostrarTodos();

            if (seleccion) {
                tipoAnalisis = mTipoAnalisis.seleccionar();
                mTipoAnalisis.actualizar(tipoAnalisis);
            }
            system("pause");
            break;
        case 4:
            std::cout << getNombreMenu() << ": " << _opciones[3] << "\n";
            std::cout << "==============================\n";

            mTipoAnalisis.mostrarTodos();
            tipoAnalisis = mTipoAnalisis.seleccionar();
            mTipoAnalisis.eliminar(tipoAnalisis);
            system("pause");
            break;
        default:
            std::cout << "Intente nuevamente\n";
            break;
    }
}