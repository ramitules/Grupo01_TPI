#include "manager/ManagerAnalisisProtocolo.h"
#include "manager/ManagerTipoAnalisis.h"
#include "archivo/ArchivoAnalisisProtocolo.h"
#include "AnalisisProtocolo.h"

ManagerAnalisisProtocolo::ManagerAnalisisProtocolo(){};

bool ManagerAnalisisProtocolo::cargar(int idProtocolo) {
    std::cin.ignore(100, '\n');

    ManagerTipoAnalisis mTipoAnalisis;
    ManagerAnalisisProtocolo mAnalisisProtocolo;
    TipoAnalisis tipoAnalisis;

    char opc;

    std::cout << "ID del Protocolo: " << idProtocolo << "\n";
    std::cout << "Analisis para agregar al protocolo: \n" << std::endl;
    mTipoAnalisis.mostrarTodos();

    while (true) {
        int idTipoAnalisis;

        std::cout << "ID tipo de analisis (0 para cancelar): ";
        std::cin >> idTipoAnalisis;

        if (idTipoAnalisis == 0) {
            return false;
        }

        if (mTipoAnalisis.comprobar(idTipoAnalisis = false)) {
            std::cout << "Por favor ingrese un tipo de analisis valido\n";
            return true;
        }

        std::cout << "Seguro que desea agregar el agregar el analisis al Protocolo? s/n: ";
        std::cin >> opc;

        if (opc == 's') {
            AnalisisProtocolo analisisProtocolo(idProtocolo,tipoAnalisis.getID(),tipoAnalisis.getPrecio());

            if (_repo.guardar(analisisProtocolo)){
                std::cout << "El Analisis se ha agregado correctamente en el Protocolo.\n";
            } else {
                std::cout << "Ocurrio un error al intentar agregar el analisis.\n";
            }
        }
        return true;
    }
}

void ManagerAnalisisProtocolo::mostrar(AnalisisProtocolo analisisProtocolo){
    /*ArchivoTipoAnalisis repoTipoAnalisis;
    TipoAnalisis auxTA // = analisisProtocolo.getIdTipoAnalisis();

    std::cout << "ID del Protocolo: " << analisisProtocolo.getIdProtocolo() << "\n";
    std::cout << "Analisis: " << auxTA.getNombreAnalisis() << "\n";
    std::cout << "Resultado: " << analisisProtocolo.getResultado() << "\n";

    //Pendiente mostrar todos los análisis del mismo protocolo*/
}

void ManagerAnalisisProtocolo::mostrarTodos(){
    for(int i=0; i<_repo.cantidadRegistros(); i++){
        this->mostrar(_repo.leer(i));
    }
}

bool ManagerAnalisisProtocolo::actualizar(AnalisisProtocolo analisisProtocolo){
    // PENDIENTE
}

/* bool ManagerAnalisisProtocolo::eliminar(AnalisisProtocolo analisisProtocolo){
    char opc;

    std::cout << "Seguro que desea eliminar el analisis del Protocolo? s/n: ";
    std::cin >> opc;

    if (opc == 's') {
        if (_repo.eliminar(_repo.getPos(AnalisisProtocolo.getId()-1))){
            std::cout << "El Analisis se ha eliminado correctamente del Protocolo.\n";
            return true;
        } else {
            std::cout << "Ocurrio un error al intentar eliminar el analisis.\n";
            return false;
        }
    }
}
*/

ArchivoAnalisisProtocolo ManagerAnalisisProtocolo::getRepositorio(){
    return _repo;
}