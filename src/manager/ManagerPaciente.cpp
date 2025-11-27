#include "manager/ManagerPaciente.h"
#include "manager/ManagerPersona.h"
#include "manager/ManagerObraSocial.h"
#include "utils/ManagerFecha.h"
#include "utils/rlutil.h"
#include "utils/funcFrontend.h"
#include <algorithm>
#include <iomanip>
#include <cstring>


ManagerPaciente::ManagerPaciente(){};

bool ManagerPaciente::cargar(int dniPaciente){
    int codigoObraSocial = 1;
    bool opcValida = false;

    ManagerObraSocial mObraSocial;
    ManagerPersona mPersona;

    Persona persona = mPersona.cargar(dniPaciente);

    std::cout << "\nObras sociales disponibles:\n";
    mObraSocial.mostrarTodos();

    while (true) {
        std::cout << "Ingrese el codigo de la obra social del paciente (0 para cancelar): ";
        std::cin >> codigoObraSocial;

        if (codigoObraSocial == 0) {
            return false;
        }

        for (int i = 0; i < mObraSocial.getRepositorio().cantidadRegistros(); i++) {
            if (mObraSocial.getRepositorio().leer(i).getID() == codigoObraSocial) {
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
        std::cout << "El paciente se ha guardado correctamente. Presione ENTER para continuar\n";
        rlutil::anykey();
        return true;
    }

    std::cout << "Ocurrio un error al intentar guardar el paciente. Presione ENTER para continuar\n";
    rlutil::anykey();
    return false;
}

std::string ManagerPaciente::mostrarCabecera(
    const int anchoDNI, 
    const int anchoNombre, 
    const int anchoApellido, 
    const int anchoTelefono, 
    const int anchoEmail,
    const int anchoFechaNacimiento, 
    const int anchoObraSocial
){
    // -- Mostrar tabla --
    std::cout << std::left; // Alinear a la izquierda

    // Linea horizontal
    std::string linea = "+" + std::string(anchoDNI + 2, '-') + 
                        "+" + std::string(anchoNombre + 2, '-') + 
                        "+" + std::string(anchoApellido + 2, '-') + 
                        "+" + std::string(anchoTelefono + 2, '-') + 
                        "+" + std::string(anchoEmail + 2, '-') + 
                        "+" + std::string(anchoFechaNacimiento + 2, '-') + 
                        "+" + std::string(anchoObraSocial + 2, '-') + "+\n";
    // Cabeceras
    std::cout << linea;
    std::cout << "| " << std::setw(anchoDNI) << "DNI" << " | "
              << std::setw(anchoNombre) << "Nombre" << " | "
              << std::setw(anchoApellido) << "Apellido" << " | "
              << std::setw(anchoTelefono) << "Telefono" << " | "
              << std::setw(anchoEmail) << "Email" << " | "
              << std::setw(anchoFechaNacimiento) << "Fecha Nacimiento" << " | "
              << std::setw(anchoObraSocial) << "Obra Social" << " |\n";
    std::cout << linea;

    return linea;
}

void ManagerPaciente::mostrarUno(Paciente paciente){
    // -- Calcular ancho maximo --
    int anchoDNI = 9;               // Largo minimo "DNI"
    int anchoNombre = 6;            // Largo minimo "Nombre"
    int anchoApellido = 8;          // Largo minimo "Apellido"
    int anchoTelefono = 9;          // Largo minimo "Telefono"
    int anchoEmail = 5;             // Largo minimo "Email"
    int anchoFechaNacimiento = 17;  // Largo minimo "Fecha Nacimiento"
    int anchoObraSocial = 11;       // Largo minimo "Obra Social"

    anchoDNI = std::max(anchoDNI, (int)std::to_string(paciente.getDNI()).length());
    anchoNombre = std::max(anchoNombre, (int)strlen(paciente.getNombre()));
    anchoApellido = std::max(anchoApellido, (int)strlen(paciente.getApellido()));
    anchoTelefono = std::max(anchoTelefono, (int)std::to_string(paciente.getTelefono()).length());
    anchoEmail = std::max(anchoEmail, (int)strlen(paciente.getEmail()));
    anchoFechaNacimiento = std::max(anchoFechaNacimiento, (int)paciente.getFechaNacimiento().to_str().length());
    anchoObraSocial = std::max(anchoObraSocial, (int)strlen(paciente.getObraSocial().getNombre()));

    std::string linea = mostrarCabecera(
        anchoDNI, 
        anchoNombre, 
        anchoApellido, 
        anchoTelefono, 
        anchoEmail,
        anchoFechaNacimiento, 
        anchoObraSocial
    );

    std::cout << "| " << std::setw(anchoDNI) << paciente.getDNI() << " | "
              << std::setw(anchoNombre) << paciente.getNombre() << " | "
              << std::setw(anchoApellido) << paciente.getApellido() << " | "
              << std::setw(anchoTelefono) << paciente.getTelefono() << " | "
              << std::setw(anchoEmail) << paciente.getEmail() << " | "
              << std::setw(anchoFechaNacimiento) << paciente.getFechaNacimiento().to_str() << " | "
              << std::setw(anchoObraSocial) << paciente.getObraSocial().getNombre() << " |\n";

    std::cout << linea;
}

void ManagerPaciente::mostrarVarios(Paciente* pacientes, const int cantidad){
    if (cantidad == 0) {
        std::cout << "No hay pacientes para mostrar.\n";
        return;
    }

    // -- Calcular ancho maximo de columnas --
    int anchoDNI = 9;               // Largo minimo "DNI"
    int anchoNombre = 6;            // Largo minimo "Nombre"
    int anchoApellido = 8;          // Largo minimo "Apellido"
    int anchoTelefono = 9;          // Largo minimo "Telefono"
    int anchoEmail = 5;             // Largo minimo "Email"
    int anchoFechaNacimiento = 17;  // Largo minimo "Fecha Nacimiento"
    int anchoObraSocial = 11;       // Largo minimo "Obra Social"

    for(int i=0; i<cantidad; i++) {
        if (pacientes[i].getEliminado()) {
            continue;
        }

        anchoDNI = std::max(anchoDNI, (int)std::to_string(pacientes[i].getDNI()).length());
        anchoNombre = std::max(anchoNombre, (int)strlen(pacientes[i].getNombre()));
        anchoApellido = std::max(anchoApellido, (int)strlen(pacientes[i].getApellido()));
        anchoTelefono = std::max(anchoTelefono, (int)std::to_string(pacientes[i].getTelefono()).length());
        anchoEmail = std::max(anchoEmail, (int)strlen(pacientes[i].getEmail()));
        anchoFechaNacimiento = std::max(anchoFechaNacimiento, (int)pacientes[i].getFechaNacimiento().to_str().length());

        anchoObraSocial = std::max(anchoObraSocial, (int)strlen(pacientes[i].getObraSocial().getNombre()));
    }

    std::string linea = mostrarCabecera(
        anchoDNI, 
        anchoNombre, 
        anchoApellido, 
        anchoTelefono, 
        anchoEmail,
        anchoFechaNacimiento, 
        anchoObraSocial
    );

    // Datos
    for(int i=0; i<cantidad; i++){
        if (pacientes[i].getEliminado()) {
            continue;
        }

        std::cout << "| " << std::setw(anchoDNI) << pacientes[i].getDNI() << " | "
                  << std::setw(anchoNombre) << pacientes[i].getNombre() << " | "
                  << std::setw(anchoApellido) << pacientes[i].getApellido() << " | "
                  << std::setw(anchoTelefono) << pacientes[i].getTelefono() << " | "
                  << std::setw(anchoEmail) << pacientes[i].getEmail() << " | "
                  << std::setw(anchoFechaNacimiento) << pacientes[i].getFechaNacimiento().to_str() << " | "
                  << std::setw(anchoObraSocial) << pacientes[i].getObraSocial().getNombre() << " |\n";
    }

    std::cout << linea;
}

void ManagerPaciente::mostrarTodos(){
    const int CANTIDAD = _repo.cantidadRegistros();
    Paciente* todos = _repo.leerTodos();
    
    mostrarVarios(todos, CANTIDAD);
    delete[] todos;
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
    mostrarVarios(pacientes, CANTIDAD);

    // Finalizar
    delete[] pacientes;
    std::cout << "Presione ENTER para continuar";
    rlutil::anykey();
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
    mostrarVarios(pacientes, CANTIDAD);

    // Finalizar
    delete[] pacientes;
    std::cout << "Presione ENTER para continuar";
    rlutil::anykey();
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
    mostrarVarios(pacientes, CANTIDAD);

    // Finalizar
    delete[] pacientes;
    std::cout << "Presione ENTER para continuar";
    rlutil::anykey();
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
    mostrarVarios(pacientes, CANTIDAD);

    // Finalizar
    delete[] pacientes;
    std::cout << "Presione ENTER para continuar";
    rlutil::anykey();
}

void ManagerPaciente::busquedaDNI(){
    const int CANTIDAD = _repo.cantidadRegistros();
    Paciente *pacientes = _repo.leerTodos();
    bool* indices = new bool[CANTIDAD];

    // Busqueda personalizada por DNI o por nombre
    int opc = 0;

    std::cout << "Como desea buscar el paciente?\n";
    std::cout << "1. Por DNI\n";
    std::cout << "2. Por nombre completo\n";

    do{
        std::cout << "Opcion: ";
        std::cin >> opc;
    } while (opc != 1 && opc != 2);

    std::cin.ignore(100, '\n');

    int totalPacientes = 0, iAux = 0;
    // Busqueda por DNI
    if (opc == 1) {
        
        int dni = 0;

        std::cout << "Ingrese el DNI del paciente: ";
        std::cin >> dni;

        buscando();

        for (int i = 0; i < CANTIDAD; i ++) {
            if (pacientes[i].getEliminado()) {
                continue;
            }
            if (pacientes[i].getDNI() == dni) {
                indices[i] = true;
                totalPacientes ++;
            }
        }
    }
    // Busqueda por nombre completo
    if (opc == 2) {
        std::string nombreCompleto;
        std::string nombreIngresado;
        
        std::cout << "Ingrese el nombre y apellido del paciente, separados por espacio: ";
        std::getline(std::cin, nombreIngresado);

        buscando();
        
        for (int i = 0; i < CANTIDAD; i ++) {
            if (pacientes[i].getEliminado()) {
                continue;
            }

            nombreCompleto = "";
            nombreCompleto.append(pacientes[i].getNombre());
            nombreCompleto.append(" ");
            nombreCompleto.append(pacientes[i].getApellido());

            if (nombreCompleto.compare(nombreIngresado) == 0) {
                indices[i] = true;
                totalPacientes ++;
            }
        }
    }

    // Mostrar
    if (totalPacientes > 0) {
        std::cout << "-- Se encontraron los siguientes pacientes --\n";
        Paciente *pacientesEncontrados = new Paciente[totalPacientes];

        for (int i = 0; i < CANTIDAD; i ++) {
            if (indices[i]) {
                pacientesEncontrados[iAux] = pacientes[i];
                iAux ++;
            }
        }

        mostrarVarios(pacientesEncontrados, totalPacientes);
        std::cout << "\n\n";
        delete[] pacientesEncontrados;
    } else {
        std::cout << "No se han encontrado pacientes en la base de datos.\n";
    }

    std::cout << "Presione ENTER para continuar";
    rlutil::anykey();

    delete[] pacientes;
    delete[] indices;
}

void ManagerPaciente::busquedaObraSocial(){
    std::cin.ignore(100, '\n');

    const int CANTIDAD = _repo.cantidadRegistros();
    Paciente *pacientes = _repo.leerTodos();
    bool* indices = new bool[CANTIDAD];

    ManagerObraSocial mObraSocial;
    mObraSocial.mostrarTodos(true);

    int idObraSocial = 0;

    std::cout << "Ingrese el ID de la obra social a buscar: ";
    std::cin >> idObraSocial;

    int totalPacientes = 0, iAux = 0;

    buscando();

    for (int i = 0; i < CANTIDAD; i ++) {
        if (pacientes[i].getEliminado()) {
            continue;
        }
        if (pacientes[i].getCodigoObraSocial() == idObraSocial) {
            indices[i] = true;
            totalPacientes ++;
        }
    }

    // Mostrar
    if (totalPacientes > 0) {
        std::cout << "-- Se encontraron los siguientes pacientes --\n";
        Paciente *pacientesEncontrados = new Paciente[totalPacientes];

        for (int i = 0; i < CANTIDAD; i ++) {
            if (indices[i]) {
                pacientesEncontrados[iAux] = pacientes[i];
                iAux ++;
            }
        }

        mostrarVarios(pacientesEncontrados, totalPacientes);
        std::cout << "\n\n";
        delete[] pacientesEncontrados;
    } else {
        std::cout << "No se han encontrado pacientes de la obra social " << idObraSocial << " en la base de datos.\n";
    }

    std::cout << "Presione ENTER para continuar";
    rlutil::anykey();

    delete[] pacientes;
    delete[] indices;
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

        while (true) {
            std::cout << "Ingrese el numero de ID de la nueva obra social (0 para cancelar): ";
            mObraSocial.mostrarTodos(true);
            std::cin >> numOpc;

            if (numOpc == 0) {
                std::cout << "Se conserva la obra social anterior.\n";
                break;
            }

            if (mObraSocial.getRepositorio().getPos(numOpc) != -1) {
                paciente.setCodigoObraSocial(numOpc);
                break;
            } else {
                std::cout << "El ID ingresado no existe. Intente nuevamente.\n";
            }
        }
    }

    if (_repo.modificar(paciente, _repo.getPos(paciente.getDNI()))) {
        std::cout << "El paciente se ha modificado correctamente. Presione ENTER para continuar.\n";
        rlutil::anykey();
        return true;
    }

    std::cout << "Ocurrio un error al intentar modificar el paciente. Presione ENTER para continuar.\n";
    rlutil::anykey();
    return false;
}

bool ManagerPaciente::eliminar(Paciente& paciente){
    ManagerPersona mPersona;
    if (!mPersona.eliminar(paciente)) {
        return false;
    }

    if (_repo.modificar(paciente, _repo.getPos(paciente.getDNI()))) {
        std::cout << "El paciente se ha eliminado correctamente. Presione ENTER para continuar.\n";
        rlutil::anykey();
        return true;
    };

    std::cout << "Ocurrio un error al intentar eliminar el paciente. Presione ENTER para continuar.\n";
    rlutil::anykey();
    return false;
}

ArchivoPaciente ManagerPaciente::getRepositorio(){
    return _repo;
}