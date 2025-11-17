#include "manager/ManagerProtocolo.h"
#include "manager/ManagerAnalisisProtocolo.h"
#include "manager/ManagerTipoAnalisis.h"
#include "manager/ManagerEnfermero.h"
#include "manager/ManagerTurno.h"
#include "manager/ManagerSecuencia.h"
#include "Protocolo.h"


ManagerProtocolo::ManagerProtocolo(){};

bool ManagerProtocolo::comprobarProtocolo(int idProtocolo) {
    Protocolo regProtocolo;
    int cantidadProtocolo = _repo.cantidadRegistros();

    if (cantidadProtocolo <= 0) {
        std::cout << "\nRegistro vacio: No se pudo encontrar el Protocolo\n" << std::endl;
        return false;
    }

    for(int i=0; i<cantidadProtocolo; i++) {
        regProtocolo = _repo.leer(i);

        if (regProtocolo.getId()==idProtocolo) {
            return true;
        }
    }

    std::cout << "No existe el protocolo ingresado\n" << std::endl;
    return false;
}

Protocolo ManagerProtocolo::seleccionarProtocolo(int idProtocolo) {
    Protocolo regProtocolo;
    int cantidadProtocolo = _repo.cantidadRegistros();

    for(int i=0; i<cantidadProtocolo; i++) {
        regProtocolo = _repo.leer(i);

        if (regProtocolo.getEstado()!=true && regProtocolo.getId()==idProtocolo) {
            return regProtocolo;
        }
    }
}

bool ManagerProtocolo::iniciar(int idTurno) {
    Protocolo protocolo;
    ArchivoProtocolo repoProtocolo;

    ManagerProtocolo mProtocolo;
    ManagerAnalisisProtocolo mAnalisisProtocolo;

    //Cargo el ID
    ManagerSecuencia mSecuencia;
    Secuencia secuencia = mSecuencia.cargar("Protocolo");
    int idProtocolo = secuencia.getIdActual();

    char opc;

    std::cout << "Se inicia el protocolo del turno " << idTurno << std::endl;

    protocolo.setId(idProtocolo);
    protocolo.setIdTurno(idTurno);

    std::cout << "Confirmar s/n: ";
    std::cin >> opc;

    std::cout << "Protocolo\n";
    std::cout << "Protocolo ID " << protocolo.getId();
    std::cout << "Protocolo ID Turno" << protocolo.getIdTurno();

    if (opc != 's') {
        std::cout << "No se inicio el protocolo.\n";
        return false;
    }

    if (_repo.guardar(protocolo)) {
        std::cout << "\nEl protocolo se ha cargado correctamente.\n" << std::endl;
        secuencia.setIdActual(idProtocolo); //En tipo de Analisis es setIdActal Revisar
        mSecuencia.actualizar(secuencia);
        return true;
    }

    std::cout << "Ocurrio un error al intentar guardar el protocolo.\n";
    return false;
}

bool ManagerProtocolo::cargarAnalisis(Protocolo protocolo) {
    ManagerAnalisisProtocolo mAnalisisProtocolo;
    ManagerTipoAnalisis mTipoAnalisis;

    mAnalisisProtocolo.cargar(protocolo.getId());
    return true;
}

bool ManagerProtocolo::asignar(Protocolo protocolo){
    ManagerProtocolo mProtocolo;
    int dniEnfermero;
    int sala;
    char opc;

    mProtocolo.mostrar(protocolo);

    std::cout << "Mostrar Enfermeros habilitados\n" ;
    std::cout << "Ingresar DNI del enfermero elegido: 30123123\n";
    std::cout << "Asignar enfermero con DNI 30123123 al protocolo\n"; //corregir
    protocolo.setDniEnfermero(30123123);

    std::cout << "Asignar sala de atencion: ";
    std::cin >> sala;
    protocolo.setSala(sala);

    std::cout << "Modificar los datos s/n: ";
    std::cin >> opc;

    if (opc != 's') {
        std::cout << "No se modificaron los datos\n";
        return false;
    }

    if (_repo.modificar(protocolo, protocolo.getId()-1)) {
        std::cout << "El protocolo se ha asignado correctamente\n";
        return true;
    }

    std::cout << "Ocurrio un error al intentar asignar protocolo.\n";
    return false;
}

void ManagerProtocolo::mostrar(Protocolo protocolo){

    std::cout << "ID\tTurno\tEstado\tSala\tEnfermero\n" << std::endl;
    std::cout << protocolo.getId() << "\t" ;
    std::cout << protocolo.getIdTurno() << "\t";
    std::cout << protocolo.getEstado() << "\t";
    std::cout << protocolo.getSala() << "\t";
    std::cout << protocolo.getEnfermero().getNombre() << "\n" <<std::endl;
    std::cout << "Observaciones: " << protocolo.getObservaciones() << "\n" << std::endl;
}

bool ManagerProtocolo::mostrarTodos(){
    Protocolo regProtocolo;

    int cantidadProtocolo = _repo.cantidadRegistros();

    if (cantidadProtocolo >= 1) {
        std::cout << "ID\tTurno\tEstado\tSala\tEnfermero" << std::endl; //Observaciones en muestra especifica
    }
    else {
        std::cout << "\nRegistro vacio\n" << std::endl;
        return false;
    }

    for(int i=0; i<cantidadProtocolo; i++){
        regProtocolo = _repo.leer(i);

        if (regProtocolo.getEstado()!=true) {

            std::cout << regProtocolo.getId() << "\t" ;
            std::cout << regProtocolo.getIdTurno() << "\t";
            std::cout << regProtocolo.getEstado() << "\t";
            std::cout << regProtocolo.getSala() << "\t";
            std::cout << regProtocolo.getEnfermero().getNombre() << "\n";
        }
    }

    std::cout << std::endl;
    return true;
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
