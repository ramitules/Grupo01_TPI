#include "menu/MenuProtocolo.h"
#include "manager/ManagerProtocolo.h"
#include "Protocolo.h"
#include "utils/funcFrontend.h"
#include <iostream>

#include "manager/ManagerAnalisisProtocolo.h"


MenuProtocolo::MenuProtocolo(): Menu(7, "Menu Protocolo"){
    std::string opciones[7] = {
        "Iniciar",
        "Cargar Estudios",
        "Asignar Protocolo",
        "Modificar protocolo",
        "Mostrar Protocolo",
        "Mostrar todos",
        "Eliminar protocolo"
    };

    setVectorOpciones(opciones);
    setSalir(false);
}

void MenuProtocolo::ejecutarOpcion(){
    ManagerProtocolo mProtocolo;
    ManagerAnalisisProtocolo mAnalisisProtocolo;
    Protocolo protocolo;
    int idProtocolo;
    switch (_opcionSeleccionada) {
        case 0:
            return;
        case 1:
            std::cout << getNombreMenu() << ": " << _opciones[0] << "\n";
            std::cout << "==============================\n";

            mProtocolo.iniciar(1);
            system("pause");
            break;
        case 2:
            std::cout << getNombreMenu() << ": " << _opciones[1] << "\n";
            std::cout << "==============================\n";

            if (mProtocolo.comprobar()) {
                mProtocolo.mostrarTodos();

                std::cout << "Ingrese ID del Protocolo a cargar: ";
                std::cin >> idProtocolo;

                mAnalisisProtocolo.cargar(idProtocolo);


            }

            system("pause");
            break;
            case 3:
            std::cout << getNombreMenu() << ": " << _opciones[2] << "\n";
            std::cout << "==============================\n";

            if (mProtocolo.comprobar()) {
                std::cout << "Ingrese el ID a asignar: ";
                std::cin >> idProtocolo;

                if (mProtocolo.comprobar(idProtocolo)) {
                    protocolo = mProtocolo.seleccionar(idProtocolo);

                    mProtocolo.asignar(protocolo);

                }
            }
            system("pause");
            break;
        case 4:
            std::cout << getNombreMenu() << ": " << _opciones[3] << "\n";
            std::cout << "==============================\n";
            system("pause");
            break;
        case 5:
            std::cout << getNombreMenu() << ": " << _opciones[4] << "\n";
            std::cout << "==============================\n";

            int idProtocolo;
            mProtocolo.mostrarTodos();

            std::cout << "Ingrese ID del Protocolo: ";
            std::cin >> idProtocolo;

            mProtocolo.mostrar(mProtocolo.seleccionar(idProtocolo));

            system("pause");
            break;
        case 6:
            std::cout << getNombreMenu() << ": " << _opciones[5] << "\n";
            std::cout << "==============================\n";
            mProtocolo.mostrarTodos();
            system("pause");
            break;
        case 7:
            std::cout << getNombreMenu() << ": " << _opciones[6] << "\n";
            std::cout << "==============================\n";
            system("pause");
            break;

        default:
            std::cout << "Intente nuevamente\n";
            break;
    }
}
