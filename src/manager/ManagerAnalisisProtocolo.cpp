#include "manager/ManagerAnalisisProtocolo.h"
#include "manager/ManagerTipoAnalisis.h"
#include "archivo/ArchivoAnalisisProtocolo.h"
#include "AnalisisProtocolo.h"
#include <algorithm>
#include <iomanip>

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
    TipoAnalisis regTipoAnalisis;
    AnalisisProtocolo regAnalisisProtocolo;

    char opc;

    std::cout << "\nAnalisis para agregar al protocolo: \n" << std::endl;
    mTipoAnalisis.mostrarTodos();

    int idTipoAnalisis = 0;
    int pos;

    while (true) {
        std::cout << "CARGAR ID del analisis (0 para terminar): ";
        std::cin >> idTipoAnalisis;

        if (idTipoAnalisis == 0) {
            return false;
        }

        if (mTipoAnalisis.getRepositorio().getPos(idTipoAnalisis) != -1) {
            if (mTipoAnalisis.getRepositorio().leer(pos).getEliminado()) {
                std::cout << "ATENCION: El analisis no se encuentra disponible. Intente nuevamente.\n";
                continue;
            }

            if (_repo.existe(idProtocolo, idTipoAnalisis)) {
                std::cout << "ATENCION: El analisis ya se encuentra en el protocolo. Intente nuevamente.\n";
                continue;
            }

            pos = mTipoAnalisis.getRepositorio().getPos(idTipoAnalisis);
            regTipoAnalisis = mTipoAnalisis.getRepositorio().leer(pos);

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

std::string ManagerAnalisisProtocolo::mostrarCabecera(int anchoID, int anchoTipoAnalisis, int anchoPrecioSoli, int anchoResultados){
    // -- Mostrar tabla --
    std::cout << std::left; // Alinear a la izquierda

    std::string linea = "+" + std::string(anchoID + 2, '-') +
                        "+" + std::string(anchoTipoAnalisis + 2, '-') +
                        "+" + std::string(anchoPrecioSoli + 2, '-') +
                        "+" + std::string(anchoResultados + 2, '-') +
                        "+\n";

    std::cout << linea;
    std::cout << "| " << std::setw(anchoID) << "ID Protocolo" << " | " 
              << std::setw(anchoTipoAnalisis) << "ID Tipo Analisis" << " | " 
              << std::setw(anchoPrecioSoli) << "Precio solicitud" << " | " 
              << std::setw(anchoResultados) << "Resultados" << " |\n";
    std::cout << linea;

    return linea;
}

    void ManagerAnalisisProtocolo::mostrarUno(AnalisisProtocolo analisisProtocolo){
    int anchoResultados = std::max((int)strlen("Resultados"), (int)strlen(analisisProtocolo.getResultado()));
    int anchoID = std::max((int)strlen("ID Protocolo"), (int)strlen(std::to_string(analisisProtocolo.getIdProtocolo()).c_str()));
    int anchoTipoAnalisis = std::max((int)strlen("ID Tipo Analisis"), (int)strlen(std::to_string(analisisProtocolo.getIdTipoAnalisis()).c_str()));
    int anchoPrecioSoli = std::max((int)strlen("Precio solicitud"), (int)strlen(std::to_string(analisisProtocolo.getPrecioSolicitud()).c_str()));

    std::string linea = mostrarCabecera(anchoID, anchoTipoAnalisis, anchoPrecioSoli, anchoResultados);
    
    std::cout << "| " << std::setw(anchoID) << analisisProtocolo.getIdProtocolo() << " | " 
              << std::setw(anchoTipoAnalisis) << analisisProtocolo.getIdTipoAnalisis() << " | " 
              << std::setw(anchoPrecioSoli) << analisisProtocolo.getPrecioSolicitud() << " | " 
              << std::setw(anchoResultados) << analisisProtocolo.getResultado() << " |\n";
    
    std::cout << linea;
}

void ManagerAnalisisProtocolo::mostrarVarios(AnalisisProtocolo* analisisProtocolos, const int cantidad){
    if (cantidad == 0) {
        std::cout << "\nATENCION: No hay analisis cargados.\n";
        return;
    }

    int anchoResultados = strlen("Resultados");
    int anchoID = strlen("ID Protocolo");
    int anchoTipoAnalisis = strlen("ID Tipo Analisis");
    int anchoPrecioSoli = strlen("Precio solicitud");

    for (int i=0; i<cantidad; i++) {
        if (analisisProtocolos[i].getEliminado()) {
            continue;
        }

        anchoID = std::max(anchoID, (int)strlen(std::to_string(analisisProtocolos[i].getIdProtocolo()).c_str()));
        anchoTipoAnalisis = std::max(anchoTipoAnalisis, (int)strlen(std::to_string(analisisProtocolos[i].getIdTipoAnalisis()).c_str()));
        anchoPrecioSoli = std::max(anchoPrecioSoli, (int)strlen(std::to_string(analisisProtocolos[i].getPrecioSolicitud()).c_str()));
        anchoResultados = std::max(anchoResultados, (int)strlen(analisisProtocolos[i].getResultado()));
    }

    std::string linea = mostrarCabecera(anchoID, anchoTipoAnalisis, anchoPrecioSoli, anchoResultados);

    for (int i=0; i<cantidad; i++) {
        if (analisisProtocolos[i].getEliminado()) {
            continue;
        }
        
        std::cout << "| " << std::setw(anchoID) << analisisProtocolos[i].getIdProtocolo() << " | " 
                  << std::setw(anchoTipoAnalisis) << analisisProtocolos[i].getIdTipoAnalisis() << " | " 
                  << std::setw(anchoPrecioSoli) << analisisProtocolos[i].getPrecioSolicitud() << " | " 
                  << std::setw(anchoResultados) << analisisProtocolos[i].getResultado() << " |\n";
    }
    std::cout << linea;
}

void ManagerAnalisisProtocolo::mostrarTodos(int idProtocolo){
    AnalisisProtocolo regAP;
    TipoAnalisis regTA;
    int resultadoDias = -1;
    int total = 0;
    int cantidad = 0;
    bool* indices = new bool[_repo.cantidadRegistros()] {false};

    for (int i=0; i<_repo.cantidadRegistros(); i++) {
        regAP = _repo.leer(i);

        if (idProtocolo!=regAP.getIdProtocolo()) {
            continue;
        }

        cantidad++;
        indices[i] = true;

        regTA = regAP.getTipoAnalisis();

        total += regTA.getPrecio();
        if (regTA.getTiempoResultado() > resultadoDias) {
            resultadoDias = regTA.getTiempoResultado();
        }
    }

    AnalisisProtocolo* analisisProtocolos = new AnalisisProtocolo[cantidad];
    int j = 0;
    for (int i=0; i<_repo.cantidadRegistros(); i++) {
        if (indices[i]) {
            regAP = _repo.leer(i);
            analisisProtocolos[j] = regAP;
            j++;
        }
    }

    mostrarVarios(analisisProtocolos, cantidad);

    std::cout << "PRECIO FINAL: $" << total << "\n";
    std::cout << "RESULTADOS en " << resultadoDias << " dia(s)\n\n" ;

    delete[] indices;
    delete[] analisisProtocolos;
}

ArchivoAnalisisProtocolo ManagerAnalisisProtocolo::getRepositorio(){
    return _repo;
}