#include "menu/MenuTipoAnalisis.h"
#include "manager/ManagerTipoAnalisis.h"
#include "TipoAnalisis.h"
#include <iostream>


MenuTipoAnalisis::MenuTipoAnalisis(): Menu(4, "Menu Tipos de Analisis"){
    std::string opciones[4] = {
        "Cargar",
        "Mostrar Todos",
        "Modificar",
        "Eliminar"
    };

    setVectorOpciones(opciones);
    setSalir(false);
}

void MenuTipoAnalisis::ejecutarOpcion(){
    ManagerTipoAnalisis mTipoAnalisis;
    TipoAnalisis tipoAnalisis;

    int idTipoAnalisis;
    bool seleccion = false;

    switch (_opcionSeleccionada) {
        case 0:
            return;
        case 1:
            std::cout << getNombreMenu() << ": " << _opciones[0] << "\n";
            std::cout << "==============================\n";

            mTipoAnalisis.cargar();
            std::cin.get();
            break;
        case 2:
            std::cout << getNombreMenu() << ": " << _opciones[1] << "\n";
            std::cout << "==============================\n";

            if (mTipoAnalisis.comprobar()) {
                mTipoAnalisis.mostrarTodos();
            }

            std::cin.get();
            break;
        case 3:
            std::cout << getNombreMenu() << ": " << _opciones[2] << "\n";
            std::cout << "==============================\n";

            if (mTipoAnalisis.comprobar()) {
                mTipoAnalisis.mostrarTodos();

                std::cout << "Ingrese el ID a modificar: ";
                std::cin >> idTipoAnalisis;

                if (mTipoAnalisis.comprobar(idTipoAnalisis)) {
                    tipoAnalisis = mTipoAnalisis.seleccionar(idTipoAnalisis);
                    mTipoAnalisis.actualizar(tipoAnalisis);
                }
            }

            std::cin.get();
            break;
        case 4:
            std::cout << getNombreMenu() << ": " << _opciones[3] << "\n";
            std::cout << "==============================\n";

            if (mTipoAnalisis.comprobar()) {
                mTipoAnalisis.mostrarTodos();

                std::cout << "Ingrese el ID a eliminar: ";
                std::cin >> idTipoAnalisis;

                if (mTipoAnalisis.comprobar(idTipoAnalisis)) {
                    tipoAnalisis = mTipoAnalisis.seleccionar(idTipoAnalisis);
                    mTipoAnalisis.eliminar(tipoAnalisis);
                }
            }
            std::cin.get();
            break;
        default:
            std::cout << "Intente nuevamente\n";
            break;
    }
}