#include "manager/ManagerProtocolo.h"
#include "manager/ManagerAnalisisProtocolo.h"
#include "manager/ManagerEnfermero.h"
#include "manager/ManagerTurno.h"
#include "Protocolo.h"
#include "utils/funcFrontend.h"
#include "archivo/ArchivoProtocolo.h"

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

    regProtocolo = _repo.leer(idProtocolo-1);

    if (idProtocolo==regProtocolo.getId() && regProtocolo.getEliminado()!=true) {
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
    Protocolo regProtocolo;

    regProtocolo = _repo.leer(idProtocolo-1);
    return regProtocolo;
}

void ManagerProtocolo::mostrar(Protocolo protocolo){

    std::cout << "\nID\tTurno\tEstado\tSala\tEnfermero\n" << std::endl;
    std::cout << protocolo.getId() << "\t" ;
    std::cout << protocolo.getIdTurno() << "\t";
    std::cout << protocolo.getEstado() << "\t";
    std::cout << protocolo.getSala() << "\t";
    std::cout << protocolo.getEnfermero().getNombre() << " " << protocolo.getEnfermero().getApellido() << "\n\n";
    std::cout << "Observaciones: " << protocolo.getObservaciones() << "\n";
}

bool ManagerProtocolo::mostrarTodos(){
    Protocolo regProtocolo;
    int cantidadProtocolo = _repo.cantidadRegistros();

    //ATENCION: Observaciones solo en el metodo mostrar

    std::cout << "ID\tTurno\tEstado\tSala\tEnfermero" << std::endl;

    for(int i=0; i<cantidadProtocolo; i++){
        regProtocolo = _repo.leer(i);

        if (regProtocolo.getEliminado()!=true) {

            std::cout << regProtocolo.getId() << "\t" ;
            std::cout << regProtocolo.getIdTurno() << "\t";
            std::cout << regProtocolo.getEstado() << "\t";
            std::cout << regProtocolo.getSala() << "\t";
            std::cout << regProtocolo.getEnfermero().getNombre() << "\n";

            //PENDIENTE CONDICION: Enfermero sin asignar
        }
    }
    std::cout << std::endl;
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

            this->mostrar(regProtocolo);

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

    ManagerProtocolo mProtocolo;
    ManagerAnalisisProtocolo mAnalisisProtocolo;

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
    ManagerProtocolo mProtocolo;
    ManagerEnfermero mEnfermero;
    ArchivoEnfermero archivoEnfermero;
    Enfermero enfermero;
    int dniEnfermero;
    int sala;
    char opc;
    int pos;

    mProtocolo.mostrar(protocolo);

    std::cout << "CLINICA - Enfermeros habilitados para asignar\n";

    mEnfermero.mostrarTodos();

    std::cout << "Seleccionar Enfermero (x DNI): ";
    std::cin >> dniEnfermero;

    enfermero = protocolo.getEnfermero();
    pos = archivoEnfermero.getPos(dniEnfermero);

    if (mEnfermero.comprobar(dniEnfermero)) {
        enfermero = mEnfermero.seleccionar(dniEnfermero);
        protocolo.setDniEnfermero(enfermero.getDNI());
    }

    std::cout << "\nAsignar sala de atencion: ";
    std::cin >> sala;
    protocolo.setSala(sala);

    std::cout << "CONFIRMAR: Modificar los datos s/n: ";
    std::cin >> opc;
    std::cout << "\n";

    if (opc != 's') {
        std::cout << "ATENCION: No se modificaron los datos\n\n";
        return false;
    }

    if (_repo.modificar(protocolo, protocolo.getId()-1)) {
        std::cout << "El protocolo se ha asignado correctamente\n\n";
        return true;
    }

    std::cout << "Ocurrio un error al intentar asignar EL protocolo.\n\n";
    return false;
}

bool ManagerProtocolo::cargarAnalisis(Protocolo protocolo) {
    ManagerAnalisisProtocolo mAnalisisProtocolo;

    mAnalisisProtocolo.cargar(protocolo.getId());
    return true;
}

bool ManagerProtocolo::finalizar(Protocolo protocolo){
    ManagerProtocolo mProtocolo;
    ManagerEnfermero mEnfermero;

    std::string observaciones;
    char opc;
    int pos;

    mProtocolo.mostrar(protocolo);


    std::cin.ignore(100, '\n');
    std::cout << "Agregar observacion: ";
    std::getline(std::cin, observaciones);
    std::cout << std::endl;

    std::cout << "CONFIRMAR: Finalizar Protocolo s/n: ";
    std::cin >> opc;
    std::cout << "\n";

    protocolo.setObservaciones(observaciones.c_str());
    protocolo.setEstado(true);

    if (opc != 's') {
        std::cout << "ATENCION: No se finalizo el Protocolo\n\n";
        return false;
    }

    if (_repo.modificar(protocolo, protocolo.getId()-1)) {
        std::cout << "El protocolo se ha finalizado correctamente\n\n";
        return true;
    }

    std::cout << "Ocurrio un error al finalizar asignar protocolo.\n\n";
    return false;
}


bool ManagerProtocolo::eliminar(Protocolo protocolo){
    char opc;
    ManagerProtocolo mProtocolo;

    std::cout << "\nSeguro que desea eliminar el protocolo? s/n: ";
    std::cin >> opc;

    if (opc == 's') {
        protocolo.setEliminado(true);
        if (_repo.modificar(protocolo,protocolo.getId()-1)){
            std::cout << "\nSe ha eliminado correctamente.\n\n";
            return true;
        } else {
            std::cout << "\nATENCION: Error al intentar eliminar el Protocolo.\n\n";
            return false;
        }
    }

    std::cout << "\nATENCION: No se eliminaron los datos.\n\n";
    return false;
}

ArchivoProtocolo ManagerProtocolo::getRepositorio() {
    return _repo;
}

