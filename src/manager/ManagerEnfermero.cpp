#include "manager/ManagerEnfermero.h"
#include "manager/ManagerPersona.h"
#include "utils/ManagerFecha.h"


ManagerEnfermero::ManagerEnfermero(){};

bool ManagerEnfermero::cargar(){
    int habilitado = 1;

    ManagerPersona mPersona;
    ManagerFecha mFecha;

    Persona persona = mPersona.cargar();

    std::cout << "Ingrese la fecha de ingreso del enfermero:\n";
    Fecha fechaIngreso = mFecha.cargar();

    std::cout << "El enfermero esta habilitado? (1 = si, 0 = no): ";
    std::cin >> habilitado;

    Enfermero enfermero(persona, habilitado, fechaIngreso);

    std::cin.ignore(100, '\n');

    if (_repo.guardar(enfermero)) {
        std::cout << "El enfermero se ha guardado correctamente.\n";
        return true;
    }

    std::cout << "No se pudo guardar el enfermero.\n";
    return false;
}


void ManagerEnfermero::mostrar(Enfermero enfermero){
    ManagerFecha mFecha;
    ManagerPersona mPersona;

    mPersona.mostrar(enfermero);
    std::cout << "Habilitado: " << (enfermero.getHabilitado() ? "Si" : "No") << "\n";
    std::cout << "Fecha de ingreso: " << mFecha.mostrar(enfermero.getFechaIngreso()) << "\n";
}

void ManagerEnfermero::mostrarTodos(){
    for(int i=0; i<_repo.cantidadRegistros(); i++){
        this->mostrar(_repo.leer(i));
    }
}

bool ManagerEnfermero::eliminar(Enfermero enfermero){
    int pos = _repo.getPos(enfermero.getDNI());

    if (pos == -1) {
        std::cout << "No se encontro el enfermero.\n";
        return false;
    }

    if (_repo.eliminar(pos)) {
        std::cout << "El enfermero se ha eliminado correctamente.\n";
        return true;
    }

    std::cout << "No se pudo eliminar el enfermero.\n";
    return false;
}

bool ManagerEnfermero::actualizar(Enfermero enfermero){
    // PENDIENTE
}