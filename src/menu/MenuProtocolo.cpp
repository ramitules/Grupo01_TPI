#include "menu/MenuProtocolo.h"
#include "manager/ManagerProtocolo.h"
#include "Protocolo.h"
#include <iostream>

#include "manager/ManagerAnalisisProtocolo.h"


MenuProtocolo::MenuProtocolo(): Menu(8, "Menu Protocolo"){
    std::string opciones[7] = {
        "Iniciar protocolo",
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
            mProtocolo.iniciar(1);
            system("pause");
            break;
        case 2:
            std::cout << getNombreMenu() << ": " << _opciones[1] << "\n";
            mProtocolo.mostrarTodos();

            std::cout << "Ingrese ID del Protocolo a cargar: ";
            std::cin >> idProtocolo; std::cout << "\n";

            mAnalisisProtocolo.cargar(idProtocolo);
            system("pause");
            break;
        case 3:
            std::cout << getNombreMenu() << ": " << _opciones[2] << "\n";
            std::cout << "Asignar\n" << std::endl;

            std::cout << "Ingrese ID del Protocolo: ";
            std::cin >> idProtocolo;

            if (mProtocolo.comprobarProtocolo(idProtocolo)) {
                protocolo = mProtocolo.seleccionarProtocolo(idProtocolo);

                mProtocolo.asignar(protocolo);

            }
            system("pause");
            break;
        case 4:
            std::cout << getNombreMenu() << ": " << _opciones[3] << "\n";
            system("pause");
            break;
        case 5:
            std::cout << getNombreMenu() << ": " << _opciones[4] << "\n";
            int idProtocolo;
            mProtocolo.mostrarTodos();

            std::cout << "Ingrese ID del Protocolo: ";
            std::cin >> idProtocolo;

            mProtocolo.mostrar(mProtocolo.seleccionarProtocolo(idProtocolo));

            system("pause");
            break;
        case 6:
            std::cout << getNombreMenu() << ": " << _opciones[5] << "\n";
            mProtocolo.mostrarTodos();
            system("pause");
            break;
        case 7:
            std::cout << getNombreMenu() << ": " << _opciones[6] << "\n";
            system("pause");
            break;

        default:
            std::cout << "Intente nuevamente\n";
            break;
    }
}
