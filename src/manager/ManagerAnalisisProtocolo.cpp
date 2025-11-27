#include "manager/ManagerAnalisisProtocolo.h"
#include "manager/ManagerTipoAnalisis.h"
#include "manager/ManagerProtocolo.h"
#include "archivo/ArchivoAnalisisProtocolo.h"
#include "Protocolo.h"
#include "AnalisisProtocolo.h"

ManagerAnalisisProtocolo::ManagerAnalisisProtocolo(){};

bool ManagerAnalisisProtocolo::comprobar(int idProtocolo, int idTipoAnalisis) {
    AnalisisProtocolo regAnalisisProtocolo;
    int cantidadAnalisisProtocolo = _repo.cantidadRegistros();

    if (cantidadAnalisisProtocolo == 0) {
        std::cout << "\nRegistro vacio.\n" << std::endl;
        return false;
    }

    if (idProtocolo == -1) { // valor por defecto: no se ingresó parametro
        return true;
    }

    for (int i=0; i<cantidadAnalisisProtocolo; i++) {
        regAnalisisProtocolo = _repo.leer(i);

        if (regAnalisisProtocolo.getIdProtocolo() == idProtocolo && regAnalisisProtocolo.getIdTipoAnalisis()==idTipoAnalisis) {
            return true;
        }
    }
    return false;
}

bool ManagerAnalisisProtocolo::cargar(int idProtocolo) {
    std::cin.ignore(100, '\n');

    ManagerProtocolo mProtocolo;
    ManagerTipoAnalisis mTipoAnalisis;
    ManagerAnalisisProtocolo mAnalisisProtocolo;
    TipoAnalisis regTipoAnalisis;
    AnalisisProtocolo regAnalisisProtocolo;
    bool analisisCargados = false;

    char opc;

    std::cout << "\nAnalisis disponibles para agregar al protocolo \n" << std::endl;
    mTipoAnalisis.mostrarTodos();

    while (true) {
        int idTipoAnalisis;

        std::cout << "\nCARGAR ID del analisis (0 para terminar): ";
        std::cin >> idTipoAnalisis;

        if (idTipoAnalisis == 0) {
            if (analisisCargados) {
                return true;
            } else {
                return false;
            }
        }

        if (mTipoAnalisis.comprobar(idTipoAnalisis)) {
            regTipoAnalisis = mTipoAnalisis.seleccionar(idTipoAnalisis);
        } else {
            continue;
        }

        if (mAnalisisProtocolo.comprobar(idProtocolo,idTipoAnalisis)) {
            std::cout << "\n\tYa se encuentra cargado este analisis al Protocolo\n";
            analisisCargados = true;
            continue;
        }

        //Comprobar que no este cargado

        std::cout << "CONFIRMAR: agregar " << regTipoAnalisis.getNombreAnalisis() << " al Protocolo? s/n: ";
        std::cin >> opc;

        if (opc == 's') {
            regAnalisisProtocolo.setIdProtocolo(idProtocolo);
            regAnalisisProtocolo.setIdTipoAnalisis(regTipoAnalisis.getID());
            regAnalisisProtocolo.setPrecioSolicitud(regTipoAnalisis.getPrecio());

            if (_repo.guardar(regAnalisisProtocolo)){
                std::cout << "\n\tEl Analisis se ha agregado correctamente.\n";
                analisisCargados = true;
            } else {
                std::cout << "Ocurrio un error al intentar agregar el analisis.\n";
            }
        }
    }
}

void ManagerAnalisisProtocolo::mostrarTodos(int idProtocolo) {
    ManagerTipoAnalisis mTipoAnalisis;
    ManagerProtocolo mProtocolo;
    AnalisisProtocolo regAnalisisProtocolo;
    Protocolo protocolo;
    TipoAnalisis regTipoAnalisis;

    int cantidadAnalisisProtocolo = _repo.cantidadRegistros();
    int resultadoDias = -1;
    int total = 0;

    protocolo = mProtocolo.seleccionar(idProtocolo);

    std::cout << "\nID\tTipo\t\t     Tiempo estimado\tPrecio solicitud\n";

    for (int i=0; i<cantidadAnalisisProtocolo; i++) {
        regAnalisisProtocolo = _repo.leer(i);

        if (idProtocolo==regAnalisisProtocolo.getIdProtocolo()) {
            regTipoAnalisis = regAnalisisProtocolo.getTipoAnalisis();

            std::cout << regTipoAnalisis.getID() << "\t" ;
            std::cout << regTipoAnalisis.getNombreAnalisis() << "\t\t     ";
            std::cout << regTipoAnalisis.getTiempoResultado() << " dias\t";
            std::cout << "\t$ " << regAnalisisProtocolo.getPrecioSolicitud() << "\n";

            total += regTipoAnalisis.getPrecio();
            if (regTipoAnalisis.getTiempoResultado() > resultadoDias) {
                resultadoDias = regTipoAnalisis.getTiempoResultado();
            }
        }
    }

    if (protocolo.getEstado()) {
        std::cout << "\nPROTOCOLO FINALIZADO\n" ;
        std::cout << "\n\tPRECIO FINAL: $" << total ;
        std::cout << "\n\tRESULTADOS en " << resultadoDias << " dia(s)\n" ;
    } else {
        std::cout << "\nPROTOCOLO PENDIENTE\n" ;
        std::cout << "\n\tPRECIO ESTIMADO (SOLICITUD): $" << total ;
        std::cout << "\n\tPLAZO ESTIMADO PARA LOS RESULTADOS: " << resultadoDias << " dia(s)\n" ;
    }
}

ArchivoAnalisisProtocolo ManagerAnalisisProtocolo::getRepositorio(){
    return _repo;
}