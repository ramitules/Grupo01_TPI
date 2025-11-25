#include "menu/MenuProtocolo.h"
#include "manager/ManagerProtocolo.h"
#include "Protocolo.h"
#include "utils/funcFrontend.h"
#include <iostream>
#include "manager/ManagerAnalisisProtocolo.h"
#include "utils/rlutil.h"


MenuProtocolo::MenuProtocolo(): Menu(8, "Menu Protocolo"){
    std::string opciones[8] = {
        "Iniciar",
        "Cargar Estudios",
        "Asignar Protocolo",
        "Finalizar protocolo",
        "Mostrar Protocolo",
        "Mostrar todos",
        "Cargar resultados",
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
    int idTurno;
    char confirmar;

    switch (_opcionSeleccionada) {
        case 0:
            return;
        case 1:
            std::cout << getNombreMenu() << ": " << _opciones[0] << "\t(Ingrese 0 para SALIR)\n";
            std::cout << "==============================\n";

            //PENDIENTE MOSTRAR TURNOS SIN INICIAR

            protocolo = Protocolo();

            std::cout << "\nIngrese el ID de turno: ";
            std:: cin >> idTurno;

            if (idTurno==0) {
                menuVolver();
                break;
            }

            std::cout << "CONFIRMAR: Iniciar el protocolo (s/n): ";
            std::cin >> confirmar;

            if (confirmar != 's') {
                //CARGA CANCELADA
                menuVolver();
                break;
            } else {
                protocolo.setIdTurno(idTurno);
            }

            if (mProtocolo.chequearTurno(protocolo)) {
                std::cout << "\nATENCION: El turno ingresado ya tiene un Protocolo iniciado\n";
                mProtocolo.mostrar(protocolo);
                std::cout << std::endl;
                menuVolver();
                break;
            }

            if (mProtocolo.iniciar(protocolo)) {
                std::cout << "\nPROTOCOLO INICIADO. ";
            } else {
                std::cout << "\nPROTOCOLO CANCELADO.";
            }

            pausa();
            break;
        case 2:
            std::cout << getNombreMenu() << ": " << _opciones[1] << "\t(Ingrese 0 para SALIR)\n";
            std::cout << "==============================\n";

            if (mProtocolo.comprobar()) {
                mProtocolo.mostrarTodos();

                std::cout << "ID del Protocolo donde cargar los estudios: ";
                std::cin >> idProtocolo;

                if (idProtocolo==0) {
                    menuVolver();
                    break;
                }

                if (mProtocolo.comprobar(idProtocolo)) {
                    protocolo = mProtocolo.seleccionar(idProtocolo);

                    if (protocolo.getEliminado()) {
                        std::cout << "\nATENCION: El protocolo no existe.\n";
                        menuVolver();
                        break;
                    }

                    if (protocolo.getEstado()) {
                        std::cout << "\nATENCION: El protocolo esta finalizado.\n";
                        menuVolver();
                        break;
                    }

                    if (!protocolo.getAnalisis()) {
                        std::cout << "\nATENCION: El protocolo ya tiene los estudios cargados\n";
                        mAnalisisProtocolo.mostrarTodos(protocolo.getId());
                        menuVolver();
                        break;
                    }

                    rlutil::cls();
                    std::cout << getNombreMenu() << ": " << _opciones[1] << "\t(Ingrese 0 para SALIR)\n";
                    std::cout << "==============================\n";
                } else {
                    menuVolver();
                    break;
                }

                if (mAnalisisProtocolo.cargar(protocolo.getId())) {
                    std::cout << "\nCARGA EXITOSA. ";
                } else {
                    std::cout << "\nCARGA CANCELADA. ";
                }
                pausa();
                break;
            }
            system("pause");
            break;
        case 3:
            std::cout << getNombreMenu() << ": " << _opciones[2] << "\t(Ingrese 0 para SALIR)\n";
            std::cout << "==============================\n";

            if (mProtocolo.comprobar()) {
                mProtocolo.mostrarTodos();

                std::cout << "Ingrese el ID a asignar: ";
                std::cin >> idProtocolo;

                if (idProtocolo<=0) {
                    menuVolver();
                    break;
                }

                if (mProtocolo.comprobar(idProtocolo)) {
                    protocolo = mProtocolo.seleccionar(idProtocolo);
                    rlutil::cls();
                    std::cout << getNombreMenu() << ": " << _opciones[2] << "\t(Ingrese 0 para SALIR)\n";
                    std::cout << "==============================\n";
                    mProtocolo.mostrar(protocolo);

                }else {
                    menuVolver();
                    break;
                }

                if (mProtocolo.asignar(protocolo)){
                    std::cout << "\nASIGNACION EXITOSA. ";
                    pausa();
                } else {
                    std::cout << "\nASIGNACION CANCELADA. ";
                    pausa();
                }
            }
            break;
        case 4:
            std::cout << getNombreMenu() << ": " << _opciones[3] << "\t(Ingrese 0 para SALIR)\n";
            std::cout << "==============================\n";

            mProtocolo.mostrarTodos();


            if (mProtocolo.comprobar()) {
                std::cout << "Ingrese el ID a finalizar: ";
                std::cin >> idProtocolo;

                if (idProtocolo==0) {
                    menuVolver();
                    break;
                }

                if (mProtocolo.comprobar(idProtocolo)) {
                    protocolo = mProtocolo.seleccionar(idProtocolo);

                    mProtocolo.finalizar(protocolo);
                }
            }
            system("pause");
            break;
        case 5:
            std::cout << getNombreMenu() << ": " << _opciones[4] << "\t(Ingrese 0 para SALIR)\n";
            std::cout << "==============================\n";

            mProtocolo.mostrarTodos();

            if (mProtocolo.comprobar()) {
                std::cout << "Ingrese el ID a observar: ";
                std::cin >> idProtocolo;

                if (idProtocolo==0) {
                    menuVolver();
                    break;
                }

                if (mProtocolo.comprobar(idProtocolo)) {
                    rlutil::cls();
                    std::cout << getNombreMenu() << ": " << _opciones[4] << "\t(Ingrese 0 para SALIR)\n";
                    std::cout << "==============================\n";

                    mProtocolo.mostrar(mProtocolo.seleccionar(idProtocolo));

                    if (mAnalisisProtocolo.comprobar(idProtocolo)) {
                        mAnalisisProtocolo.mostrarTodos(idProtocolo);
                    }
                }
            }
            system("pause");
            break;
        case 6:
            std::cout << getNombreMenu() << ": " << _opciones[5] << "\t(Ingrese 0 para SALIR)\n";
            std::cout << "==============================\n";
            mProtocolo.mostrarTodos();
            system("pause");
            break;
        case 7:
            //Cargar resultados;
        case 8:
            std::cout << getNombreMenu() << ": " << _opciones[6] << "\t(Ingrese 0 para SALIR)\n";
            std::cout << "==============================\n";

            mProtocolo.mostrarTodos();

            if (mProtocolo.comprobar()) {
                std::cout << "\nIngrese el ID a Eliminar: ";
                std::cin >> idProtocolo;

                if (idProtocolo==0) {
                    menuVolver();
                    break;
                }

                if (mProtocolo.comprobar(idProtocolo)) {

                    protocolo = mProtocolo.seleccionar(idProtocolo);
                    mProtocolo.mostrar(protocolo);
                }else {
                    std::cout << std::endl ;
                    menuVolver();
                    break;
                }

                if (mProtocolo.eliminar(protocolo)){
                    std::cout << "\nELIMINACION EXITOSA.";
                } else {
                    std::cout << "\nELIMINACION CANCELADA.";
                }
                pausa();
                break;
            }
        default:
            std::cout << "Intente nuevamente\n";
            break;
    }
}
