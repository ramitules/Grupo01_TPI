#include "manager/ManagerProtocolo.h"
#include "manager/ManagerAnalisisProtocolo.h"
#include "manager/ManagerEnfermero.h"
#include "manager/ManagerTurno.h"
#include "Protocolo.h"
#include "utils/funcFrontend.h"
#include "archivo/ArchivoProtocolo.h"
#include <algorithm>
#include <iomanip>

ManagerProtocolo::ManagerProtocolo(){};

//VALIDACION: Comprueba que exista el ID

bool ManagerProtocolo::comprobar(int idProtocolo) {
    Protocolo regProtocolo;
    int cantidadProtocolo = _repo.cantidadRegistros();

    if (cantidadProtocolo <= 0) {
        std::cout << "\nRegistro vacio.\n" << std::endl;
        return false;
    }

    if (idProtocolo == -1) { // valor por defecto: no se ingresó parametro
        return true;
    }

    regProtocolo = _repo.leer(_repo.getPos(idProtocolo));

    if (idProtocolo==regProtocolo.getId() && !regProtocolo.getEliminado()) {
        //std::cout << "Protocolo encontrado";
        return true;
    }
    else {
        std::cout << "\nATENCION: ID no existente.\n" << std::endl;
        return false;
    }
}

//RETORNA EL OBJETO CON EL ID SELECCIONADO

Protocolo ManagerProtocolo::seleccionar(int idProtocolo) {
    return _repo.leer(_repo.getPos(idProtocolo));
}

std::string ManagerProtocolo::mostrarCabecera(const int observaciones){
    // -- Mostrar tabla --
    std::cout << std::left; // Alinear a la izquierda

    // Linea horizontal
    std::string linea = "+" + std::string(5, '-') +                 // ID
                        "+" + std::string(10, '-') +                // ID Turno
                        "+" + std::string(15, '-') +                // DNI enfermero
                        "+" + std::string(6, '-') +                 // Sala
                        "+" + std::string(observaciones + 2, '-') + 
                        "+" + std::string(15, '-') + "+\n";
    // Cabeceras
    std::cout << linea;
    std::cout << "| " << std::setw(3) << "ID" << " | "
              << std::setw(10) << "ID Turno" << " | "
              << std::setw(15) << "DNI enfermero" << " | "
              << std::setw(6) << "Sala" << " | "
              << std::setw(observaciones) << "Observaciones" << " | "
              << std::setw(15) << "Estado" << " |\n";
    std::cout << linea;

    return linea;
}

void ManagerProtocolo::mostrarUno(Protocolo protocolo){
    int anchoObservaciones = std::max((int)std::string("Observaciones").length(), (int)strlen(protocolo.getObservaciones()));

    std::string linea = mostrarCabecera(anchoObservaciones);

    std::cout << "| " << std::setw(3) << protocolo.getId() << " | "
              << std::setw(10) << protocolo.getIdTurno() << " | "
              << std::setw(15) << protocolo.getDniEnfermero() << " | "
              << std::setw(6) << protocolo.getSala() << " | "
              << std::setw(anchoObservaciones) << protocolo.getObservaciones() << " | "
              << std::setw(15) << (protocolo.getEstado() ? "Completado" : "No completado") << " | "
              << std::setw(11) << protocolo.getEliminado() << " |\n";
    std::cout << linea;
}

void ManagerProtocolo::mostrarVarios(Protocolo* protocolos, const int cantidad){
    if (cantidad == 0) {
        std::cout << "No hay protocolos para mostrar.\n";
        return;
    }

    int anchoObservaciones = (int)std::string("Observaciones").length();

    for(int i=0; i<cantidad; i++){
        if (protocolos[i].getEliminado()) {
            continue;
        }

        anchoObservaciones = std::max(anchoObservaciones, (int)strlen(protocolos[i].getObservaciones()));
    }
    
    std::string linea = mostrarCabecera(anchoObservaciones);

    // Datos
    for (int i=0; i<cantidad; i++) {
        if (protocolos[i].getEliminado()) {
            continue;
        }

        std::cout << "| " << std::setw(3) << protocolos[i].getId() << " | "
                  << std::setw(10) << protocolos[i].getIdTurno() << " | "
                  << std::setw(15) << protocolos[i].getDniEnfermero() << " | "
                  << std::setw(6) << protocolos[i].getSala() << " | "
                  << std::setw(anchoObservaciones) << protocolos[i].getObservaciones() << " | "
                  << std::setw(13) << (protocolos[i].getEstado() ? "Completado" : "No completado") << " | "
                  << std::setw(11) << protocolos[i].getEliminado() << " |\n";
    }
    std::cout << linea;
}

bool ManagerProtocolo::mostrarTodos(){
    Protocolo* protocolos = _repo.leerTodos();
    int cantidadProtocolos = _repo.cantidadRegistros();

    mostrarVarios(protocolos, cantidadProtocolos);

    delete[] protocolos;
    return true;
}

int ManagerProtocolo::buscarTurno(int idTurno) {
    Protocolo regProtocolo;
    int cantidadRegistros = _repo.cantidadRegistros();
    int idProtocolo;
    bool turnoEncontrado = false;

    for(int i=0; i<cantidadRegistros; i++) {
        regProtocolo = _repo.leer(i);

        if (regProtocolo.getIdTurno()==idTurno) {
            idProtocolo = regProtocolo.getId();
            turnoEncontrado = true;

            std::cout  << "El turno ya tiene un protocolo iniciado.\n\n";

            this->mostrarUno(regProtocolo);

            return idProtocolo;
        }
    }

    if (turnoEncontrado == false) {
        return -1;
    }
}

//INICIA UN PROTOCOLO RECIBIENDO EL ID DEL TURNO

int ManagerProtocolo::iniciar(int idTurno) {
    Protocolo protocolo;
    int auxTurno;

    auxTurno = this->buscarTurno(idTurno);

    if (auxTurno != -1) {
        return auxTurno;
    }

    int idProtocolo = _repo.cantidadRegistros()+1;

    char opc;

    std::cout << "\nSe iniciara el protocolo del turno " << idTurno << "\n\n";

    std::cout << "CONFIRMAR: Iniciar el protocolo (s/n): ";
    std::cin >> opc;
    std::cout << std::endl;

    if (opc != 's') {
        std::cout << "ATENCION: No se inicio el protocolo\n\n";
        return -1;
    }

    protocolo.setId(idProtocolo);
    protocolo.setIdTurno(idTurno);

    if (_repo.guardar(protocolo)) {
        std::cout << "El protocolo se ha iniciado correctamente.\n\n";
        return idProtocolo;
    }

    std::cout << "ATENCION: Ocurrio un error al intentar guardar el protocolo.\n";
    return -1;
}

bool ManagerProtocolo::asignar(Protocolo protocolo){
    ManagerEnfermero mEnfermero;
    int dniEnfermero;
    int sala;
    char opc;

    this->mostrarUno(protocolo);

    if (protocolo.getEstado()) {
        std::cout << "\n\nProtocolo ya cerrado\n";
        return false;
    }

    std::cout << "CLINICA - Enfermeros habilitados para asignar\n";

    mEnfermero.mostrarTodos();

    while (true) {
        std::cout << "Seleccionar enfermero (por DNI): ";
        std::cin >> dniEnfermero;

        if (mEnfermero.getRepositorio().getPos(dniEnfermero) != -1) {
            protocolo.setDniEnfermero(dniEnfermero);
            break;
        }
        else {
            std::cout << "DNI no valido";
        }
    }

    while (true) {
        std::cout << "\nAsignar sala de atencion: ";
        std::cin >> sala;

        if (sala > 0 && sala < 20) {
            protocolo.setSala(sala);
            break;
        }
        else {
            std::cout << "Numero de sala invalido. Intente nuevamente.\n";
        }
    }

    std::cout << "CONFIRMAR: Modificar los datos? s/n: ";
    std::cin >> opc;
    std::cout << "\n";

    if (opc != 's') {
        std::cout << "ATENCION: No se modificaron los datos\n\n";
        return false;
    }

    if (_repo.modificar(protocolo, _repo.getPos(protocolo.getId()))) {
        std::cout << "El protocolo se ha asignado correctamente\n\n";
        return true;
    }

    std::cout << "Ocurrio un error al intentar asignar el protocolo.\n\n";
    return false;
}

bool ManagerProtocolo::cargarAnalisis(Protocolo protocolo) {
    ManagerAnalisisProtocolo mAnalisisProtocolo;

    mAnalisisProtocolo.cargar(protocolo.getId());
    return true;
}

bool ManagerProtocolo::finalizar(Protocolo protocolo){
    ManagerEnfermero mEnfermero;

    std::string observaciones;
    char opc;

    this->mostrarUno(protocolo);


    std::cin.ignore(100, '\n');
    std::cout << "Agregar observacion: ";
    std::getline(std::cin, observaciones);
    std::cout << std::endl;

    std::cout << "CONFIRMAR: Finalizar protocolo? s/n: ";
    std::cin >> opc;
    std::cout << "\n";

    protocolo.setObservaciones(observaciones.c_str());
    protocolo.setEstado(true);

    if (opc != 's') {
        std::cout << "ATENCION: No se finalizo el protocolo\n\n";
        return false;
    }

    if (_repo.modificar(protocolo, _repo.getPos(protocolo.getId()))) {
        std::cout << "El protocolo se ha finalizado correctamente\n\n";
        return true;
    }

    std::cout << "Ocurrio un error al finalizar el protocolo.\n\n";
    return false;
}


bool ManagerProtocolo::eliminar(Protocolo protocolo){
    char opc;
    ManagerProtocolo mProtocolo;

    std::cout << "\nSeguro que desea eliminar el protocolo? s/n: ";
    std::cin >> opc;

    if (opc == 's') {
        protocolo.setEliminado(true);
        if (_repo.modificar(protocolo, _repo.getPos(protocolo.getId()))) {
            std::cout << "\nSe ha eliminado correctamente.\n\n";
            return true;
        } else {
            std::cout << "\nATENCION: Error al intentar eliminar el protocolo.\n\n";
            return false;
        }
    }

    std::cout << "\nATENCION: No se eliminaron los datos.\n\n";
    return false;
}

ArchivoProtocolo ManagerProtocolo::getRepositorio() {
    return _repo;
}

