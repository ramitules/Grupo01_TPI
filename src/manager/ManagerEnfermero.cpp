#include "manager/ManagerEnfermero.h"
#include "manager/ManagerPersona.h"
#include "utils/ManagerFecha.h"


ManagerEnfermero::ManagerEnfermero(){};

//VALIDACION: Comprueba que exista el dni

bool ManagerEnfermero::comprobar(int dniEnfermero) {
    Enfermero regEnfermero;
    Persona regPersona;
    int cantidadEnfermero = _repo.cantidadRegistros();

    if (cantidadEnfermero <= 0) {
        std::cout << "\nRegistro vacio.\n\n" << std::endl;
        return false;
    }

    if (dniEnfermero == -1) { // valor por defecto: no se ingresó parametro
        return true;
    }

    int posicion = _repo.getPos(dniEnfermero);
    regEnfermero = _repo.leer(posicion);

    if (dniEnfermero==regEnfermero.getDNI() && regEnfermero.getEliminado()!=true) {
        //std::cout << "Enfermero";
        return true;
    }
    else {
        std::cout << "\nATENCION: No existe el DNI ingresado.\n" << std::endl;
        return false;
    }
}

//RETORNA EL OBJETO CON EL DNI INGRESADO

Enfermero ManagerEnfermero::seleccionar(int dniEnfermero) {
    Enfermero regEnfermero;

    int posicion = _repo.getPos(dniEnfermero);
    regEnfermero = _repo.leer(posicion);
    return regEnfermero;
}

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
    ManagerPersona mPersona;
    Enfermero regEnfermero;
    int cantidadEnfermeros = _repo.cantidadRegistros();

    std::cout << "\nOpc\tNombre\t\tDNI\t\tHabilitado\n";

    for(int i=0; i<_repo.cantidadRegistros(); i++){
        regEnfermero = _repo.leer(i);

        if (regEnfermero.getEliminado()!=true) {
            std::cout << i+1<< "\t";
            std::cout << regEnfermero.getNombre() << " " << regEnfermero.getApellido() << "\t";
            std::cout << regEnfermero.getDNI() << "\t";
            std::cout << regEnfermero.getHabilitado() << "\n";
        }
    }
    std::cout << std::endl;
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