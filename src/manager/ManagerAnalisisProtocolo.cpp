#include "manager/ManagerAnalisisProtocolo.h"
#include "manager/ManagerTipoAnalisis.h"
#include "archivo/ArchivoAnalisisProtocolo.h"
#include "AnalisisProtocolo.h"

ManagerAnalisisProtocolo::ManagerAnalisisProtocolo(){};

bool ManagerAnalisisProtocolo::comprobar(int idProtocolo) {
    AnalisisProtocolo regAnalisisProtocolo;
    int cantidadAnalisisProtocolo = _repo.cantidadRegistros();

    if (cantidadAnalisisProtocolo <= 0) {
        std::cout << "\nRegistro vacio.\n" << std::endl;
        return false;
    }

    if (idProtocolo == -1) { // valor por defecto: no se ingresó parametro
        return true;
    }

    for (int i=0; i<cantidadAnalisisProtocolo; i++) {
        regAnalisisProtocolo = _repo.leer(i);

        if (regAnalisisProtocolo.getIdProtocolo() == idProtocolo) {
            return true;
        }
    }

    std::cout << "\nATENCION: El Protocolo no tiene estudios cargados.\n" << std::endl;
    return false;
}

bool ManagerAnalisisProtocolo::cargar(int idProtocolo) {
    std::cin.ignore(100, '\n');

    ManagerTipoAnalisis mTipoAnalisis;
    ManagerAnalisisProtocolo mAnalisisProtocolo;
    TipoAnalisis regTipoAnalisis;
    AnalisisProtocolo regAnalisisProtocolo;

    char opc;

    std::cout << "\nAnalisis para agregar al protocolo: \n" << std::endl;
    mTipoAnalisis.mostrarTodos();

    while (true) {
        int idTipoAnalisis;

        std::cout << "CARGAR ID del analisis (0 para terminar): ";
        std::cin >> idTipoAnalisis;

        if (idTipoAnalisis == 0) {
            return false;
        }

        if (mTipoAnalisis.comprobar(idTipoAnalisis)) {
            regTipoAnalisis = mTipoAnalisis.seleccionar(idTipoAnalisis);

            std::cout << "CONFIRMAR: agregar " << regTipoAnalisis.getNombreAnalisis() << " al Protocolo? s/n: ";
            std::cin >> opc;

            if (opc == 's') {
                regAnalisisProtocolo.setIdProtocolo(idProtocolo);
                regAnalisisProtocolo.setIdTipoAnalisis(regTipoAnalisis.getID());
                regAnalisisProtocolo.setPrecioSolicitud(regTipoAnalisis.getPrecio());

                if (_repo.guardar(regAnalisisProtocolo)){
                    std::cout << "El Analisis se ha agregado correctamente.\n\n";
                } else {
                    std::cout << "Ocurrio un error al intentar agregar el analisis.\n\n";
                }
            }
        }
        continue;
    }
}

void ManagerAnalisisProtocolo::mostrarTodos(int idProtocolo){
    ManagerTipoAnalisis mTipoAnalisis;
    AnalisisProtocolo regAnalisisProtocolo;
    TipoAnalisis regTipoAnalisis;
    int cantidadAnalisisProtocolo = _repo.cantidadRegistros();
    int resultadoDias = -1;
    int total = 0;

    std::cout << "\nID\tTipo\tTiempo estimado\tPrecio solicitud\n";

    for (int i=0; i<cantidadAnalisisProtocolo; i++) {
        regAnalisisProtocolo = _repo.leer(i);

        if (idProtocolo==regAnalisisProtocolo.getIdProtocolo()) {
            regTipoAnalisis = regAnalisisProtocolo.getTipoAnalisis();

            std::cout << regTipoAnalisis.getID() << "\t" ;
            std::cout << regTipoAnalisis.getNombreAnalisis() << "\t";
            std::cout << regTipoAnalisis.getTiempoResultado() << " dias\t";
            std::cout << "\t$ " << regAnalisisProtocolo.getPrecioSolicitud() << "\n\n";

            total += regTipoAnalisis.getPrecio();
            if (regTipoAnalisis.getTiempoResultado() > resultadoDias) {
                resultadoDias = regTipoAnalisis.getTiempoResultado();
            }
        }
    }
    std::cout << "PRECIO FINAL: $" << total << "\n";
    std::cout << "RESULTADOS en " << resultadoDias << " dia(s)\n\n" ;
}

ArchivoAnalisisProtocolo ManagerAnalisisProtocolo::getRepositorio(){
    return _repo;
}