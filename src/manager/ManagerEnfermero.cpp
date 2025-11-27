#include "manager/ManagerEnfermero.h"
#include "manager/ManagerPersona.h"
#include "utils/ManagerFecha.h"
#include "utils/rlutil.h"
#include "utils/funcFrontend.h"
#include <algorithm>
#include <iomanip>
#include <cstring>


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

    if (dniEnfermero==regEnfermero.getDNI() && !regEnfermero.getEliminado()) {
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

bool ManagerEnfermero::cargar(int dniEnfermero){
    ManagerPersona mPersona;

    Persona persona = mPersona.cargar(dniEnfermero);

    char opc = 'n';
    std::cout << "El enfermero esta habilitado? (s/n): ";
    std::cin >> opc;

    bool habilitado = (opc == 's');

    ManagerFecha mFecha;
    std::cout << "Ingrese la fecha de ingreso del enfermero:\n";
    Fecha fechaIngreso = mFecha.cargar();

    Enfermero enfermero(persona, habilitado, fechaIngreso);

    if (_repo.guardar(enfermero)) {
        std::cout << "El enfermero se ha guardado correctamente. Presione ENTER para continuar\n";
        rlutil::anykey();
        return true;
    }

    std::cout << "Ocurrio un error al intentar guardar el enfermero. Presione ENTER para continuar\n";
    rlutil::anykey();
    return false;
}

std::string ManagerEnfermero::mostrarCabecera(
    const int anchoDNI, 
    const int anchoNombre, 
    const int anchoApellido, 
    const int anchoTelefono, 
    const int anchoEmail,
    const int anchoFecha
){
    // -- Mostrar tabla --
    std::cout << std::left; // Alinear a la izquierda

    // Linea horizontal
    std::string linea = "+" + std::string(anchoDNI + 2, '-') + 
                        "+" + std::string(anchoNombre + 2, '-') + 
                        "+" + std::string(anchoApellido + 2, '-') + 
                        "+" + std::string(anchoTelefono + 2, '-') + 
                        "+" + std::string(anchoEmail + 2, '-') +
                        "+" + std::string(anchoFecha + 2, '-') +
                        "+" + std::string(13, '-') +
                        "+" + std::string(anchoFecha + 2, '-') + "+\n";
    // Cabeceras
    std::cout << linea;
    std::cout << "| " << std::setw(anchoDNI) << "DNI" << " | " 
              << std::setw(anchoNombre) << "Nombre" << " | "
              << std::setw(anchoApellido) << "Apellido" << " | "
              << std::setw(anchoTelefono) << "Telefono" << " | "
              << std::setw(anchoEmail) << "Email" << " | "
              << std::setw(anchoFecha) << "Fecha Nacimiento" << " | "
              << std::setw(11) << "Habilitado" << " | "
              << std::setw(anchoFecha) << "Fecha Ingreso" << " |\n";
    std::cout << linea;

    return linea;
}

void ManagerEnfermero::mostarUno(Enfermero enfermero){
    // -- Calcular ancho maximo --
    int anchoDNI = 9;               // Largo minimo "DNI"
    int anchoNombre = 6;            // Largo minimo "Nombre"
    int anchoApellido = 8;          // Largo minimo "Apellido"
    const int anchoTelefono = 10;   // Constante
    int anchoEmail = 5;             // Largo minimo "Email"
    const int anchoFecha = 17;      // Constante

    anchoDNI = std::max(anchoDNI, (int)std::to_string(enfermero.getDNI()).length());
    anchoNombre = std::max(anchoNombre, (int)strlen(enfermero.getNombre()));
    anchoApellido = std::max(anchoApellido, (int)strlen(enfermero.getApellido()));
    anchoEmail = std::max(anchoEmail, (int)strlen(enfermero.getEmail()));
    
    std::string linea = mostrarCabecera(
        anchoDNI, 
        anchoNombre, 
        anchoApellido, 
        anchoTelefono, 
        anchoEmail,
        anchoFecha
    );

    std::cout << "| " << std::setw(anchoDNI) << enfermero.getDNI() << " | "
              << std::setw(anchoNombre) << enfermero.getNombre() << " | "
              << std::setw(anchoApellido) << enfermero.getApellido() << " | "
              << std::setw(anchoTelefono) << enfermero.getTelefono() << " | "
              << std::setw(anchoEmail) << enfermero.getEmail() << " | "
              << std::setw(anchoFecha) << enfermero.getFechaNacimiento().to_str() << " | "
              << std::setw(11) << (enfermero.getHabilitado() ? "Si" : "No") << " | "
              << std::setw(anchoFecha) << enfermero.getFechaIngreso().to_str() << " |\n";

    std::cout << linea;
}

void ManagerEnfermero::mostrarVarios(Enfermero* enfermeros, const int cantidad){
    if (cantidad == 0) {
        std::cout << "No hay enfermeros para mostrar.\n";
        return;
    }

    // -- Calcular ancho maximo de columnas --
    int anchoDNI = 9;               // Largo minimo "DNI"
    int anchoNombre = 6;            // Largo minimo "Nombre"
    int anchoApellido = 8;          // Largo minimo "Apellido"
    const int anchoTelefono = 10;   // Constante
    int anchoEmail = 5;             // Largo minimo "Email"
    const int anchoFecha = 17;      // Constante

    for(int i=0; i<cantidad; i++) {
        if (enfermeros[i].getEliminado()) {
            continue;
        }

        anchoDNI = std::max(anchoDNI, (int)std::to_string(enfermeros[i].getDNI()).length());
        anchoNombre = std::max(anchoNombre, (int)strlen(enfermeros[i].getNombre()));
        anchoApellido = std::max(anchoApellido, (int)strlen(enfermeros[i].getApellido()));
        anchoEmail = std::max(anchoEmail, (int)strlen(enfermeros[i].getEmail()));
    }

    std::string linea = mostrarCabecera(
        anchoDNI, 
        anchoNombre, 
        anchoApellido, 
        anchoTelefono, 
        anchoEmail,
        anchoFecha
    );

    // Datos
    for(int i=0; i<cantidad; i++){
        if (enfermeros[i].getEliminado()) {
            continue;
        }

        std::cout << "| " << std::setw(anchoDNI) << enfermeros[i].getDNI() << " | "
                  << std::setw(anchoNombre) << enfermeros[i].getNombre() << " | "
                  << std::setw(anchoApellido) << enfermeros[i].getApellido() << " | "
                  << std::setw(anchoTelefono) << enfermeros[i].getTelefono() << " | "
                  << std::setw(anchoEmail) << enfermeros[i].getEmail() << " | "
                  << std::setw(anchoFecha) << enfermeros[i].getFechaNacimiento().to_str() << " | "
                  << std::setw(11) << (enfermeros[i].getHabilitado() ? "Si" : "No") << " | "
                  << std::setw(anchoFecha) << enfermeros[i].getFechaIngreso().to_str() << " |\n";
    }

    std::cout << linea;
}

void ManagerEnfermero::mostrarTodos(){
    const int CANTIDAD = _repo.cantidadRegistros();
    Enfermero* todos = _repo.leerTodos();
    
    mostrarVarios(todos, CANTIDAD);
    delete[] todos;
}

void ManagerEnfermero::ordenadosApellido() {
    const int CANTIDAD = _repo.cantidadRegistros();
    Enfermero *enfermeros = _repo.leerTodos();
    Enfermero aux;

    // Ordenar
    for (int i=0; i<CANTIDAD; i++) {
        if (enfermeros[i].getEliminado()) {
            continue;
        }

        for (int j=i+1; j<CANTIDAD; j++) {
            if (enfermeros[j].getEliminado()) {
                continue;
            }

            if (strcmp(enfermeros[i].getApellido(), enfermeros[j].getApellido()) > 0) {
                aux = enfermeros[i];
                enfermeros[i] = enfermeros[j];
                enfermeros[j] = aux;
            }
        }
    }

    // Mostrar
    mostrarVarios(enfermeros, CANTIDAD);

    // Finalizar
    delete[] enfermeros;
    std::cout << "Presione ENTER para continuar";
    rlutil::anykey();
}

void ManagerEnfermero::ordenadosDNI() {
    const int CANTIDAD = _repo.cantidadRegistros();
    Enfermero *enfermeros = _repo.leerTodos();
    Enfermero aux;

    // Ordenar
    for (int i=0; i<CANTIDAD; i++) {
        if (enfermeros[i].getEliminado()) {
            continue;
        }

        for (int j=i+1; j<CANTIDAD; j++) {
            if (enfermeros[j].getEliminado()) {
                continue;
            }

            if (enfermeros[i].getDNI() > enfermeros[j].getDNI()) {
                aux = enfermeros[i];
                enfermeros[i] = enfermeros[j];
                enfermeros[j] = aux;
            }
        }
    }

    // Mostrar
    mostrarVarios(enfermeros, CANTIDAD);

    // Finalizar
    delete[] enfermeros;
    std::cout << "Presione ENTER para continuar";
    rlutil::anykey();
}

void ManagerEnfermero::ordenadosAntiguedad() {
    const int CANTIDAD = _repo.cantidadRegistros();
    Enfermero *enfermeros = _repo.leerTodos();
    Enfermero aux;

    // Ordenar
    for (int i=0; i<CANTIDAD; i++) {
        if (enfermeros[i].getEliminado()) {
            continue;
        }

        for (int j=i+1; j<CANTIDAD; j++) {
            if (enfermeros[j].getEliminado()) {
                continue;
            }

            if (enfermeros[i].getFechaIngreso() > enfermeros[j].getFechaIngreso()) {
                aux = enfermeros[i];
                enfermeros[i] = enfermeros[j];
                enfermeros[j] = aux;
            }
        }
    }

    // Mostrar
    mostrarVarios(enfermeros, CANTIDAD);

    // Finalizar
    delete[] enfermeros;
    std::cout << "Presione ENTER para continuar";
    rlutil::anykey();
}

bool ManagerEnfermero::actualizar(Enfermero& enfermero){
    ManagerPersona mPersona;
    ManagerFecha mFecha;

    mPersona.actualizar(enfermero);

    char opc = 'n';

    std::cin.ignore(100, '\n');

    if (enfermero.getHabilitado()) {
        std::cout << "El enfermero sigue habilitado? (s/n): ";
        std::cin >> opc;

        enfermero.setHabilitado(opc == 's');
    } else {
        std::cout << "El enfermero sigue deshabilitado? (s/n): ";
        std::cin >> opc;

        enfermero.setHabilitado(opc == 'n');
    }

    std::cout << "Su fecha de ingreso sigue siendo la misma? (s/n): ";
    std::cin >> opc;

    if (opc != 's') {
        enfermero.setFechaIngreso(mFecha.cargar());
    }
    
    if (_repo.modificar(enfermero, _repo.getPos(enfermero.getDNI()))) {
        std::cout << "El enfermero se ha modificado correctamente. Presione ENTER para continuar.\n";
        rlutil::anykey();
        return true;
    }

    std::cout << "Ocurrio un error al intentar modificar el enfermero. Presione ENTER para continuar.\n";
    rlutil::anykey();
    return false;
}

bool ManagerEnfermero::eliminar(Enfermero& enfermero){
    char opc;

    std::cout << "Seguro que desea eliminar el enfermero? (s/n): ";
    std::cin >> opc;

    if (opc == 's') {
        enfermero.setEliminado(true);
        if (_repo.modificar(enfermero, _repo.getPos(enfermero.getDNI()))) {
            std::cout << "El enfermero se ha eliminado correctamente. Presione ENTER para continuar.\n";
            rlutil::anykey();
            return true;
        }
    }

    std::cout << "Operacion cancelada.\n";
    return false;
}

ArchivoEnfermero ManagerEnfermero::getRepositorio(){
    return _repo;
}
