#include "manager/ManagerPaciente.h"
#include "manager/ManagerPersona.h"
#include "manager/ManagerObraSocial.h"
#include "archivo/ArchivoObraSocial.h"
#include "utils/ManagerFecha.h"


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
        std::cout << "------------------------------\n";
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
    Paciente *pacientes = _repo.leerTodos();
    
    if (pacientes == nullptr){
        std::cout << "No se pudo asignar memoria." << std::endl;
        return;
    }
    
    for(int i=0; i<_repo.cantidadRegistros(); i++){
        this->mostrar(pacientes[i]);
        std::cout << "------------------------\n";
    }

    delete[] pacientes;
}

bool ManagerPaciente::actualizar(Paciente paciente){
    // PENDIENTE
}

bool ManagerPaciente::eliminar(Paciente paciente){
    char opc;

    std::cout << "Seguro que desea eliminar el analisis? s/n: ";
    std::cin >> opc;

    if (opc == 's') {
        _repo.eliminar(_repo.getPos(paciente.getDNI()));
    }
}

ArchivoPaciente ManagerPaciente::getRepositorio(){
    return _repo;
}