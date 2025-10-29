#include "manager/ManagerProtocolo.h"
#include "manager/ManagerTurno.h"
#include "manager/ManagerTipoAnalisis.h"
#include "manager/ManagerSecuencia.h"



ManagerProtocolo::ManagerProtocolo(){};

bool ManagerProtocolo::cargar(){
    std::cin.ignore(100, '\n');

    ArchivoTurno repoTurno;
    ArchivoEnfermero repoEnfermero;

    ManagerTipoAnalisis mTipoAnalisis;
    ManagerSecuencia managerSecuencia;

    Secuencia sec = managerSecuencia.cargar("Protocolo");

    int proximoID = sec.getIdActual() + 1;
    int idTurno = 0;
    int dniEnfermero = 0;
    int sala = 0;
    char observaciones[255]{};
    bool opcValida = false;

    std::cout << "ID del Protocolo: " << proximoID << "\n";
    std::cout << "ID del Turno: ¿?" ; // A corregir
    std::cout << "Enfermero: ";
    std::cout << dniEnfermero; // A corregir
    std::cout << "Sala: ";
    std::cin >> sala;

    /* PENDIENTE TIPOS DE ANALISIS

    std::cout << "Tipos de analisis disponibles:\n";
    mTipoAnalisis.mostrarTodos();

    while (true) {
        std::cout << "------------------------------\n";
        std::cout << "ID tipo de analisis (0 para cancelar): ";
        std::cin >> idTipoAnalisis;
        
        if (idTipoAnalisis == 0) {
            return false;
        }

        for (int i = 0; i < repoTipoAnalisis.cantidadRegistros(); i++) {
            if (repoTipoAnalisis.leer(i).getID() == idTipoAnalisis) {
                opcValida = true;
                break;
            }
        }
        
        if (opcValida) {
            break;
        }

        std::cout << "Por favor ingrese un tipo de analisis valido\n";
    } */

    std::cout << "Observaciones: "; // A laburar;

    Protocolo protocolo(proximoID, idTurno, dniEnfermero, sala, observaciones);

    if (_repo.guardar(protocolo)) {
        std::cout << "El protocolo se ha guardado correctamente.\n";
        return true;
    }

    std::cout << "Ocurrio un error al intentar guardar el protocolo.\n";
    return false;
}


void ManagerProtocolo::mostrar(Protocolo protocolo){
    Enfermero auxE = protocolo.getEnfermero();

    std::cout << "ID del Protocolo: " << protocolo.getId() << "\n";
    std::cout << "Turno: " << protocolo.getIdTurno() << "\n";
    std::cout << "Enfermero: " << auxE.getNombre() << " " << auxE.getApellido() << "\n";
    std::cout << "Sala: " << protocolo.getSala() << "\n";
    std::cout << "Observaciones: " << protocolo.getObservaciones() << "\n";
}

void ManagerProtocolo::mostrarTodos(){
    for(int i=0; i<_repo.cantidadRegistros(); i++){
        this->mostrar(_repo.leer(i));
    }
}

bool ManagerProtocolo::actualizar(Protocolo protocolo){
    // PENDIENTE
}

bool ManagerProtocolo::eliminar(Protocolo protocolo){
    char opc;

    std::cout << "Seguro que desea eliminar el protocolo? s/n: ";
    std::cin >> opc;

    if (opc == 's' || opc == 'S') {
        if (_repo.eliminar(_repo.getPos(protocolo.getId()))){
            std::cout << "El Protocolo se ha eliminado correctamente.\n";
            return true;
        } else {
            std::cout << "Ocurrio un error al intentar eliminar el protocolo.\n";
            return false;
        }
    }
}
