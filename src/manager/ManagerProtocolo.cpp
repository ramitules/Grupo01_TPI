#include "manager/ManagerProtocolo.h"
#include "manager/ManagerAnalisisProtocolo.h"
#include "manager/ManagerEnfermero.h"
#include "manager/ManagerTurno.h"
#include "Protocolo.h"
#include "utils/funcFrontend.h"
#include "utils/rlutil.h"
#include "archivo/ArchivoProtocolo.h"

ManagerProtocolo::ManagerProtocolo(){};

bool ManagerProtocolo::comprobar(int idProtocolo) {
    Protocolo regProtocolo;
    int posProtocolo = _repo.getPos(idProtocolo);

    if (posProtocolo == -1) {
        std::cout << "\n\tATENCION: No existe el PROTOCOLO\n";
        return false;
    }

    regProtocolo = _repo.leer(posProtocolo);

    if (regProtocolo.getEliminado()) {
        std::cout << "\n\tATENCION: PROTOCOLO Eliminado\n";
        return false;
    }

    return true;
}

Protocolo ManagerProtocolo::seleccionar(int idProtocolo) {

    int posicion = _repo.getPos(idProtocolo);
    Protocolo protocolo = _repo.leer(idProtocolo-1);
    return protocolo;
}

Protocolo ManagerProtocolo::seleccionarxTurno(int idTurno) {
    int cantidadRegistros = _repo.cantidadRegistros();
    Protocolo* aProtocolo = new Protocolo[cantidadRegistros];
    Protocolo regProtocolo;

    aProtocolo = _repo.leerTodos();

    for (int i = 0; i < cantidadRegistros; i++) {
        if (aProtocolo[i].getEliminado()) {
            continue;
        }
        if (aProtocolo[i].getIdTurno() == idTurno) {
            regProtocolo = aProtocolo[i];
        }
    }

    delete []aProtocolo;
    return regProtocolo;
}

void ManagerProtocolo::mostrar(Protocolo protocolo) {
    ManagerAnalisisProtocolo mAnalisisProtocolo;

    std::cout << "\nID\tTurno\tEstado\t\tSala\tEnfermero\n" ;
    std::cout << protocolo.getId() << "\t" ;
    std::cout << protocolo.getIdTurno() << "\t";
    (protocolo.getEstado()) ? std::cout << "Finalizado\t" : std::cout << "Pendiente\t";

    if (protocolo.getSala() == 0) {
        std::cout << "-" << "\t";
        std::cout << "[Sin asignar]\t";
    } else {
        std::cout << protocolo.getSala() << "\t";
        std::cout << protocolo.getEnfermero().getNombre() << " " << protocolo.getEnfermero().getApellido() << "\n" ;
    }
    if (protocolo.getEstado()) {
        std::cout << "\nOBSERVACIONES: " << protocolo.getObservaciones() << "\n";
    }
    if (protocolo.getAnalisis()) {
        std::cout << "\nESTUDIOS CARGADOS EN EL PROTOCOLO\n";
        mAnalisisProtocolo.mostrarTodos(protocolo.getId());
    }else {
        std::cout << "\nPROTOCOLO SIN ESTUDIOS CARGADOS\n";
    }
}

void ManagerProtocolo::mostrarVarios(Protocolo *protocolo, int cantidad){

    std::cout << "\nID\tTurno\tEstado\t\tSala\tEnfermero\n\n" ;

    for(int i=0; i<cantidad; i++){

        if (protocolo[i].getEliminado()) {
            continue;
        }

        std::cout << protocolo[i].getId() << "\t" ;
        std::cout << protocolo[i].getIdTurno() << "\t";
        (protocolo[i].getEstado()) ? std::cout << "Finalizado\t" : std::cout << "Pendiente\t";
        if (protocolo[i].getSala() == 0) {
            std::cout << protocolo[i].getSala() << "\t";
            std::cout << "[Sin asignar]\n";
        } else {
            std::cout << protocolo[i].getSala() << "\t";
            std::cout << protocolo[i].getEnfermero().getNombre() << " " << protocolo[i].getEnfermero().getApellido() << "\n" ;
        };
    }
    std::cout << std::endl;
}

bool ManagerProtocolo::mostrarTodos(){
    Protocolo regProtocolo;
    int cantidadProtocolo = _repo.cantidadRegistros();

    //ATENCION: Observaciones solo en el metodo mostrar

    std::cout << "\nID\tTurno\tEstado\t\tSala\tEnfermero\n\n" ;

    for(int i=0; i<cantidadProtocolo; i++){
        regProtocolo = _repo.leer(i);

        if (regProtocolo.getEliminado() == true) {
            continue;
        }

        std::cout << regProtocolo.getId() << "\t" ;
        std::cout << regProtocolo.getIdTurno() << "\t";
        (regProtocolo.getEstado()) ? std::cout << "Finalizado\t" : std::cout << "Pendiente\t";
        if (regProtocolo.getSala() == 0) {
            std::cout << regProtocolo.getSala() << "\t";
            std::cout << "[Sin asignar]\n";
        } else {
            std::cout << regProtocolo.getSala() << "\t";
            std::cout << regProtocolo.getEnfermero().getNombre() << " " << regProtocolo.getEnfermero().getApellido() << "\n" ;
        }
    }
    std::cout << std::endl;
    ManagerTurno mTurno;

    return true;
}

bool ManagerProtocolo::chequearTurno(Protocolo protocolo) {
    int cantidadRegistros = _repo.cantidadRegistros();
    int idProtocolo;
    bool turnoEncontrado = false;

    Protocolo regProtocolo;

    for(int i=0; i<cantidadRegistros; i++) {
        regProtocolo = _repo.leer(i);

        if (regProtocolo.getIdTurno()==protocolo.getIdTurno() && regProtocolo.getEliminado()==false) {
            return true;
        }
    }
    return false;
}

//

//INICIA UN PROTOCOLO RECIBIENDO EL ID DEL TURNO

bool ManagerProtocolo::iniciar(Protocolo &protocolo) {
    ManagerProtocolo mProtocolo;
    Protocolo auxProtocolo = protocolo;

    if (mProtocolo.chequearTurno(protocolo)) {
        std::cout << "\n\tATENCION: El turno ingresado ya tiene un Protocolo iniciado\n";
        menuVolver();
        return false;
    }

    int idProtocoloNuevo = _repo.cantidadRegistros()+1;

    auxProtocolo.setId(idProtocoloNuevo);

    if (_repo.guardar(auxProtocolo)) {
        protocolo.setId(idProtocoloNuevo);
        return true;
    } else {
        std::cout << "\n\tATENCION: Ocurrio un error al intentar iniciar el protocolo.\n";
        return false;
    }
}

bool ManagerProtocolo::cargarAnalisis(Protocolo protocolo) {
    ManagerAnalisisProtocolo mAnalisisProtocolo;

    if (!mAnalisisProtocolo.cargar(protocolo.getId())) {
        pausa;
        return false;
    } else {
        protocolo.setAnalisis(true);
        _repo.modificar(protocolo, protocolo.getId()-1);
        return true;
    }

}

bool ManagerProtocolo::asignar(Protocolo protocolo){
    ManagerProtocolo mProtocolo;
    ManagerEnfermero mEnfermero;
    Enfermero enfermero;
    int dniEnfermero;
    int sala;
    char opc;
    int pos;

    if (protocolo.getEstado()!=false) {
        std::cout << "\nATENCION: Protocolo ya finalizado\n";
        return false;
    }

    if (protocolo.getSala()!=0) {
        std::cout << "\nATENCION: Protocolo ya asignado\n";
        return false;
    }

    if (!protocolo.getAnalisis()) {
        std::cout << "\nATENCION: El protocolo no tiene estudios cargados. No se puede asignar.\n";
        return false;
    }

    rlutil::cls();

    std::cout << "\nCLINICA - Enfermeros habilitados para asignar\n\n";

    mEnfermero.mostrarTodos();

    while (true) {
        std::cout << "\nSeleccionar Enfermero (x DNI): ";
        std::cin >> dniEnfermero;

        if (dniEnfermero == 0) {
            return false;
        }

        if (mEnfermero.comprobar(dniEnfermero) == false) {
            continue;
        }

        enfermero = mEnfermero.seleccionar(dniEnfermero);

        if (enfermero.getHabilitado() == false){
            std::cout << "\n\tEnfermero no habilitado\n";
            continue;
        }
        break;
    }

    std::cout << "Asignar sala de atencion: ";
    std::cin >> sala;

    if (sala == 0) {
        return false;
    }

    protocolo.setSala(sala);

    std::cout << "\t\nCONFIRMAR: Asignar el protocolo s/n: ";
    std::cin >> opc;

    if (opc != 's') {
        std::cout << "\nATENCION: No se asigno el protocolo\n";
        return false;
    } else {
        protocolo.setDniEnfermero(enfermero.getDNI());
    }

    if (_repo.modificar(protocolo, protocolo.getId()-1)) {
        return true;
    }else {
        std::cout << "Ocurrio un error al intentar asignar el protocolo.\n\n";
    }
    return false;
}

bool ManagerProtocolo::finalizar(Protocolo protocolo){
    ManagerProtocolo mProtocolo;
    ManagerEnfermero mEnfermero;

    std::string observaciones;
    char opc;
    int pos;

    if (protocolo.getEliminado()==true) {
        std::cout << "\nATENCION: El protocolo no existe\n" ;
        return false;
    }

    if (protocolo.getEstado()!=false) {
        std::cout << "\nATENCION: El protocolo ya esta finalizado\n";
        return false;
    }

    if (protocolo.getSala()==0) {
        std::cout << "\nATENCION: El protocolo no se ha asignado.\n";
        return false;
    }

    mProtocolo.mostrar(protocolo);

    std::cin.ignore(100, '\n');
    std::cout << "\nFINALIZANDO PROTOCOLO - Agregar observacion: ";
    std::getline(std::cin, observaciones);

    std::cout << "\nCONFIRMAR: Finalizar Protocolo s/n: ";
    std::cin >> opc;

    protocolo.setObservaciones(observaciones.c_str());
    protocolo.setEstado(true);

    if (opc != 's') {
        std::cout << "\nATENCION: No se finalizo el Protocolo\n";
        return false;
    }

    if (_repo.modificar(protocolo, protocolo.getId()-1)) {
        std::cout << "\nEl protocolo se ha finalizado correctamente\n";
        return true;
    }

    std::cout << "Ocurrio un error al finalizar asignar protocolo.\n\n";
    return false;
}

bool resultados(Protocolo protocolo) {


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

