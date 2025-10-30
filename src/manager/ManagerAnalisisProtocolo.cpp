#include "manager/ManagerTipoAnalisis.h"
#include "TipoAnalisis.h"
#include "Protocolo.h"
#include "AnalisisProtocolo.h"


ManagerAnalisisProtocolo::ManagerAnalisisProtocolo(){};

bool ManagerAnalisisProtocolo::cargar(idProtocolo){
    std::cin.ignore(100, '\n');

    ArchivoTipoAnalisis repoTipoAnalisis;
    ManagerTipoAnalisis mTipoAnalisis;

    opcValida = false;
    int idTipoAnalisis;

    std::cout << "ID del Protocolo: " << idProtocolo << "\n";
    std::cout << "Seleccione el estudio a realizar: ";
    mTipoAnalisis.mostrarTodos();
    std::cin >> idTipoAnalisis;

    std::cout << "Seleccione el estudio a realizar:\n";
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
    }

    //A laburar resultados

    AnalisisProtocolo analisisProtocolo(idProtocolo, idTipoAnalisis, resultados);

    if (_repo.guardar(analisisProtocolo)) {
        std::cout << "El analisis se ha guardado correctamente.\n";
        return true;
    }

    std::cout << "Ocurrio un error al intentar guardar el analisis.\n";
    return false;
}


void ManagerAnalisisProtocolo::mostrar(AnalisisProtocolo analisisProtocolo){
    TipoAnalisis auxTA = analisisProtocolo.getIdTipoAnalisis();

    std::cout << "ID del Protocolo: " << analisisProtocolo.getIdProtocolo() << "\n";
    std::cout << "Analisis: " << auxTA.getNombreAnalisis() << "\n";
    std::cout << "Resultado: " << analisisProtocolo.getResultado() << "\n";

    //Pendiente mostrar todos los análisis del mismo protocolo
}

void ManagerAnalisisProtocolo::mostrarTodos(){
    for(int i=0; i<_repo.cantidadRegistros(); i++){
        this->mostrar(_repo.leer(i));
    }
}

bool ManagerAnalisisProtocolo::actualizar(AnalisisProtocolo analisisProtocolo){
    // PENDIENTE
}

bool ManagerAnalisisProtocolo::eliminar(AnalisisProtocolo analisisProtocolo){
    char opc;

    std::cout << "Seguro que desea eliminar el analisis del Protocolo? s/n: ";
    std::cin >> opc;

    if (opc == 's' || opc == 'S') {
        if (_repo.eliminar(_repo.getPos(AnalisisProtocolo.getId()))){
            std::cout << "El Analisis se ha eliminado correctamente del Protocolo.\n";
            return true;
        } else {
            std::cout << "Ocurrio un error al intentar eliminar el analisis.\n";
            return false;
        }
    }
}

ArchivoAnalisisProtocolo ManagerAnalisisProtocolo::getRepositorio(){
    return _repo;
}