#include "menu/MenuTipoAnalisis.h"
#include "TipoAnalisis.h"
#include "manager/ManagerTipoAnalisis.h"
#include "utils/funcFrontend.h"
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
    char confirmar;

    switch (_opcionSeleccionada) {
        case 0:
            return;
        case 1:
            std::cout << getNombreMenu() << ": " << _opciones[0] << "\t(Ingrese 0 para SALIR)\n";
            std::cout << "==============================\n";
            tipoAnalisis = TipoAnalisis();

            if (!mTipoAnalisis.ingresarDatos(tipoAnalisis, true)) {
                break;
            }

            std::cout << "\nCONFIRMAR: Cargar los datos s/n: ";
            std::cin >> confirmar;

            if (confirmar != 's') {
                //CARGA CANCELADA
                menuVolver();
                break;
            }

            if (mTipoAnalisis.cargarDatos(tipoAnalisis)) {
                std::cout << "\nCARGA EXITOSA. ";
            } else {
                std::cout << "\nCARGA CANCELADA. ";
            }
            pausa();
            break;
        case 2:
            std::cout << getNombreMenu() << ": " << _opciones[1] << "\t(Ingrese 0 para SALIR)\n";
            std::cout << "==============================\n";
            tipoAnalisis = TipoAnalisis();

            if (mTipoAnalisis.comprobar()) {
                mTipoAnalisis.mostrarTodos();
                std::cout << std::endl;
            }

            pausa();
            break;
        case 3:
            std::cout << getNombreMenu() << ": " << _opciones[2] << "\t(Ingrese 0 para SALIR)\n";
            std::cout << "==============================\n";

            std::cin.ignore(100,'\n');

            mTipoAnalisis.mostrarTodos();

            std::cout << "\nIngrese el ID a modificar: ";
            std::cin >> idTipoAnalisis;

            if (idTipoAnalisis==0) {
                menuVolver();
                break;
            }

            if (!mTipoAnalisis.comprobar(idTipoAnalisis)) {
                pausa();
                break;
            }

            tipoAnalisis = mTipoAnalisis.seleccionar(idTipoAnalisis);
            mTipoAnalisis.mostrar(tipoAnalisis);

            std::cout << "\nModificar los datos s/n: ";
            std::cin >> confirmar;

            if (confirmar != 's') {
                //CARGA CANCELADA
                menuVolver();
                break;
            }

            if (!mTipoAnalisis.ingresarDatos(tipoAnalisis)) {
                menuVolver();
                break;
            }

            std::cout << "\nCONFIRMAR: Guardar los cambios realizados s/n: ";
            std::cin >> confirmar;

            if (confirmar != 's') {
                //CARGA CANCELADA
                menuVolver();
                break;
            }

            if (mTipoAnalisis.actualizar(tipoAnalisis)) {
                std::cout << "\nMODIFICACION EXITOSA. ";
            } else {
                std::cout << "\nMODIFICACION CANCELADA. ";
            }

            pausa();
            break;
        case 4:
            std::cout << getNombreMenu() << ": " << _opciones[3] <<  "\t(Ingrese 0 para SALIR)\n";
            std::cout << "==============================\n";

            if (!mTipoAnalisis.comprobar()) {
                mTipoAnalisis.mostrarTodos();
                menuVolver();
                break;
            }

            mTipoAnalisis.mostrarTodos();

            std::cout << "\nIngrese el ID a eliminar: ";
            std::cin >> idTipoAnalisis;

            if (idTipoAnalisis==0) {
                menuVolver();
                break;
            }
            if (!mTipoAnalisis.comprobar(idTipoAnalisis)) {
                pausa();
                break;
            }

            tipoAnalisis = mTipoAnalisis.seleccionar(idTipoAnalisis);

            std::cout << "\nCONFIRMAR: Eliminar los datos s/n: ";
            std::cin >> confirmar;

            if (confirmar != 's') {
                //CARGA CANCELADA
                menuVolver();
                break;
            }

            if (mTipoAnalisis.eliminar(tipoAnalisis)){
                std::cout << "\nELIMINACION EXITOSA. \n";
            } else {
                std::cout << "\nELIMINACION CANCELADA. \n";
            }
            pausa();
            break;

        default:
            std::cout << "Intente nuevamente\n";
            break;
    }
}