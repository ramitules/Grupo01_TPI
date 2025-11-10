#include "manager/ManagerPaciente.h"
#include "manager/ManagerPersona.h"
#include "manager/ManagerObraSocial.h"
#include "archivo/ArchivoObraSocial.h"
#include "utils/ManagerFecha.h"
#include "utils/rlutil.h"
#include "utils/funcFrontend.h"



ManagerPaciente::ManagerPaciente(){};

bool ManagerPaciente::cargar(){
    std::cin.ignore(100, '\n');

    int codigoObraSocial = 1;
    bool opcValida = false;

    ArchivoObraSocial repoObraSocial;

    ManagerObraSocial mObraSocial;
    ManagerPersona mPersona;

    Persona persona = mPersona.cargar();

    std::cin.ignore(100, '\n');

    std::cout << "Obras sociales disponibles:\n";
    mObraSocial.mostrarTodos();

    while (true) {
        std::cout << separadorParcial();
        std::cout << "Ingrese el codigo de la obra social del paciente (0 para cancelar): ";
        std::cin >> codigoObraSocial;

        if (codigoObraSocial == 0) {
            return false;
        }

        for (int i = 0; i < repoObraSocial.cantidadRegistros(); i++) {
            if (repoObraSocial.leer(i).getID() == codigoObraSocial) {
                opcValida = true;
                break;
            }
        }

        if (opcValida) {
            break;
        }

        std::cout << "Por favor ingrese un codigo de obra social valido\n";
    }
    
    Paciente paciente(persona, codigoObraSocial);

    if (_repo.guardar(paciente)) {
        std::cout << "El paciente se ha guardado correctamente.\n";
        return true;
    }

    std::cout << "No se pudo guardar el paciente.\n";
    return false;
}


void ManagerPaciente::mostrar(Paciente paciente){
    ManagerPersona mPersona;

    mPersona.mostrar(paciente);
    std::cout << "Obra Social: " << paciente.getObraSocial().getNombre() << "\n";
}

void ManagerPaciente::mostrarTodos(){
    Paciente aux;
    for (int i = 0; i < _repo.cantidadRegistros(); i++) {
        aux = _repo.leer(i);

        if (aux.getEliminado()) {
            continue;
        }

        mostrar(aux);
        std::cout << separadorParcial();
    }
}

void ManagerPaciente::ordenadosApellido() {
    const int CANTIDAD = _repo.cantidadRegistros();
    Paciente *pacientes = _repo.leerTodos();
    Paciente aux;

    // Ordenar
    for (int i=0; i<CANTIDAD; i++) {
        if (pacientes[i].getEliminado()) {
            continue;
        }

        for (int j=i+1; j<CANTIDAD; j++) {
            if (pacientes[j].getEliminado()) {
                continue;
            }

            if (strcmp(pacientes[i].getApellido(), pacientes[j].getApellido()) > 0) {
                aux = pacientes[i];
                pacientes[i] = pacientes[j];
                pacientes[j] = aux;
            }
        }
    }

    // Mostrar
    for (int i=0; i<CANTIDAD; i++) {
        if (pacientes[i].getEliminado()) {
            continue;
        }

        mostrar(pacientes[i]);
        std::cout << separadorParcial();
    }
}

void ManagerPaciente::ordenadosDNI() {
    const int CANTIDAD = _repo.cantidadRegistros();
    Paciente *pacientes = _repo.leerTodos();
    Paciente aux;

    // Ordenar
    for (int i=0; i<CANTIDAD; i++) {
        if (pacientes[i].getEliminado()) {
            continue;
        }

        for (int j=i+1; j<CANTIDAD; j++) {
            if (pacientes[j].getEliminado()) {
                continue;
            }

            if (pacientes[i].getDNI() > pacientes[j].getDNI()) {
                aux = pacientes[i];
                pacientes[i] = pacientes[j];
                pacientes[j] = aux;
            }
        }
    }

    // Mostrar
    for (int i=0; i<CANTIDAD; i++) {
        if (pacientes[i].getEliminado()) {
            continue;
        }

        mostrar(pacientes[i]);
        std::cout << separadorParcial();
    }
}

void ManagerPaciente::ordenadosEdad() {
    const int CANTIDAD = _repo.cantidadRegistros();
    Paciente *pacientes = _repo.leerTodos();
    Paciente aux;

    // Ordenar
    for (int i=0; i<CANTIDAD; i++) {
        if (pacientes[i].getEliminado()) {
            continue;
        }

        for (int j=i+1; j<CANTIDAD; j++) {
            if (pacientes[j].getEliminado()) {
                continue;
            }

            if (pacientes[i].getFechaNacimiento() > pacientes[j].getFechaNacimiento()) {
                aux = pacientes[i];
                pacientes[i] = pacientes[j];
                pacientes[j] = aux;
            }
        }
    }

    // Mostrar
    for (int i=0; i<CANTIDAD; i++) {
        if (pacientes[i].getEliminado()) {
            continue;
        }

        mostrar(pacientes[i]);
        std::cout << separadorParcial();
    }
}

void ManagerPaciente::ordenadosObraSocial() {
    const int CANTIDAD = _repo.cantidadRegistros();
    Paciente *pacientes = _repo.leerTodos();
    Paciente aux;

    // Ordenar
    for (int i=0; i<CANTIDAD; i++) {
        if (pacientes[i].getEliminado()) {
            continue;
        }

        for (int j=i+1; j<CANTIDAD; j++) {
            if (pacientes[j].getEliminado()) {
                continue;
            }

            if (pacientes[i].getCodigoObraSocial() > pacientes[j].getCodigoObraSocial()) {
                aux = pacientes[i];
                pacientes[i] = pacientes[j];
                pacientes[j] = aux;
            }
        }
    }

    // Mostrar
    for (int i=0; i<CANTIDAD; i++) {
        if (pacientes[i].getEliminado()) {
            continue;
        }

        mostrar(pacientes[i]);
        std::cout << separadorParcial();
    }
}

bool ManagerPaciente::actualizar(Paciente& paciente){
    ManagerObraSocial mObraSocial;
    ManagerPersona mPersona;
    mPersona.actualizar(paciente);

    char opc = 'n';

    std::cin.ignore(100, '\n');

    std::cout << "La obra social es la misma? s/n: ";
    std::cin >> opc;

    if (opc != 's') {
        int numOpc;

        std::cout << "Ingrese el numero de ID de la nueva obra social: ";
        mObraSocial.mostrarTodos(true);
        std::cin >> numOpc;

        if (mObraSocial.getRepositorio().getPos(numOpc) == -1) {
            std::cout << "El ID ingresado no existe. Se conserva la obra social anterior.\n";
        } else {
            paciente.setCodigoObraSocial(numOpc);
        }
    }

    if (_repo.modificar(paciente, _repo.getPos(paciente.getDNI()))) {
        std::cout << "El paciente se ha modificado correctamente. Presione ENTER para continuar.\n";
        rlutil::getkey();
        return true;
    }

    std::cout << "Ocurrio un error al intentar modificar el paciente. Presione ENTER para continuar.\n";
    rlutil::getkey();
    return false;
}

bool ManagerPaciente::eliminar(Paciente& paciente){
    ManagerPersona mPersona;
    if (!mPersona.eliminar(paciente)) {
        return false;
    }

    if (_repo.modificar(paciente, _repo.getPos(paciente.getDNI()))) {
        std::cout << "El paciente se ha eliminado correctamente. Presione ENTER para continuar.\n";
        rlutil::getkey();
        return true;
    };

    std::cout << "Ocurrio un error al intentar eliminar el paciente. Presione ENTER para continuar.\n";
    rlutil::getkey();
    return false;
}

ArchivoPaciente ManagerPaciente::getRepositorio(){
    return _repo;
}