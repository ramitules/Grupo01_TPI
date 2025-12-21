#include "manager/ManagerObraSocial.h"
#include "manager/ManagerPaciente.h"
#include "Paciente.h"
#include "utils/rlutil.h"
#include "utils/funcFrontend.h"
#include <algorithm>
#include <iomanip>


ManagerObraSocial::ManagerObraSocial(){};

bool ManagerObraSocial::cargar(){
    std::cin.ignore(100, '\n');

    int proximoID = _repo.cantidadRegistros() + 1;
    int telefono, cobertura;
    std::string nombre;
    std::string nombreContacto;
    std::string email;

    std::cout << "Ingrese el nombre de la obra social: ";
    std::getline(std::cin, nombre);
    
    if (nombre == "") {
        nombre = "Sin nombre";
    }

    std::cout << "Ingrese un nombre de contacto: ";
    std::getline(std::cin, nombreContacto);
    
    if (nombreContacto == "") {
        nombreContacto = "Sin contacto";
    }

    std::cout << "Ingrese el email de la obra social: ";
    std::getline(std::cin, email);
    
    if (email == "") {
        email = "Sin email";
    }

    while (true) {
        std::cout << "Ingrese el telefono de la obra social: ";
        std::cin >> telefono;

        if (telefono > 1000000000 && telefono < 1600000000) {
            break;
        }

        std::cout << "Intente nuevamente. Asegurese que sea un numero de 10 digitos.\n";
    }

    while (true) {
        std::cout << "Ingrese el porcentaje de cobertura de la obra social: ";
        std::cin >> cobertura;

        if (cobertura >= 0 && cobertura <=100) {
            break;
        }

        std::cout << "Intente nuevamente. Asegurese que sea un valor entre 0 y 100.\n";
    }

    std::cin.ignore(100, '\n');

    ObraSocial obraSocial(proximoID, nombre.c_str(), nombreContacto.c_str(), telefono, email.c_str(), cobertura);

    if (_repo.guardar(obraSocial)) {
        std::cout << "\nLa obra social se ha guardado correctamente. Presione ENTER para continuar\n";
        rlutil::anykey();
        return true;
    }

    std::cout << "Ocurrio un error al intentar guardar la obra social. Presione ENTER para continuar\n";
    rlutil::anykey();
    return false;
}

std::string ManagerObraSocial::mostrarCabecera(const int anchoNombre, const int anchoContacto, const int anchoTelefono, const int anchoEmail, const int anchoCobertura){
    // -- Mostrar tabla --
    std::cout << std::left; // Alinear a la izquierda

    // Linea horizontal
    std::string linea = "+" + std::string(5, '-') + 
                        "+" + std::string(anchoNombre + 2, '-') + 
                        "+" + std::string(anchoContacto + 2, '-') + 
                        "+" + std::string(anchoTelefono + 2, '-') +
                        "+" + std::string(anchoEmail + 2, '-') +
                        "+" + std::string(anchoCobertura + 2, '-') + "+\n";
    // Cabeceras
    std::cout << linea;
    std::cout << "| " << std::setw(3) << "ID" << " | " 
              << std::setw(anchoNombre) << "Nombre" << " | "
              << std::setw(anchoContacto) << "Contacto" << " | "
              << std::setw(anchoTelefono) << "Telefono" << " | "
              << std::setw(anchoEmail) << "Email" << " | "
              << std::setw(anchoCobertura) << "Cobertura (%)" << " |\n";
    std::cout << linea;

    return linea;
}

void ManagerObraSocial::mostrarUno(ObraSocial obraSocial){
    // -- Calcular ancho maximo
    int anchoNombre = 6;            // Minimo 6 (Nombre)
    int anchoContacto = 9;          // Minimo 9 (Contacto)
    const int anchoTelefono = 10;   // Constante
    int anchoEmail = 5;             // Minimo 5 (Email)
    const int anchoCobertura = 13;

    anchoNombre = std::max(anchoNombre, (int)strlen(obraSocial.getNombre()));
    anchoContacto = std::max(anchoContacto, (int)strlen(obraSocial.getNombreContacto()));
    anchoEmail = std::max(anchoEmail, (int)strlen(obraSocial.getEmail()));

    std::string linea = mostrarCabecera(anchoNombre, anchoContacto, anchoTelefono, anchoEmail, anchoCobertura);

    // Datos
    std::cout << "| " << std::setw(3) << obraSocial.getID() << " | "
              << std::setw(anchoNombre) << obraSocial.getNombre() << " | "
              << std::setw(anchoContacto) << obraSocial.getNombreContacto() << " | "
              << std::setw(anchoTelefono) << obraSocial.getTelefono() << " | "
              << std::setw(anchoEmail) << obraSocial.getEmail() << " | "
              << std::setw(anchoCobertura) << obraSocial.getCobertura() << " |\n";
    std::cout << linea;
}

void ManagerObraSocial::mostrarVarios(ObraSocial* obrasSociales, const int cantidad){
    if (cantidad == 0) {
        std::cout << "No hay obras sociales para mostrar.\n";
        return;
    }

    // -- Calcular ancho maximo de columnas --
    int anchoNombre = 6;            // Minimo 6 (Nombre)
    int anchoContacto = 9;          // Minimo 9 (Contacto)
    const int anchoTelefono = 10;   // Constante
    int anchoEmail = 5;             // Minimo 5 (Email)
    const int anchoCobertura = 13;

    for(int i=0; i<cantidad; i++) {
        if (obrasSociales[i].getEliminado()) {
            continue;
        }

        anchoNombre = std::max(anchoNombre, (int)strlen(obrasSociales[i].getNombre()));
        anchoContacto = std::max(anchoContacto, (int)strlen(obrasSociales[i].getNombreContacto()));
        anchoEmail = std::max(anchoEmail, (int)strlen(obrasSociales[i].getEmail()));
    }

    std::string linea = mostrarCabecera(anchoNombre, anchoContacto, anchoTelefono, anchoEmail, anchoCobertura);

    // Datos
    for(int i=0; i<cantidad; i++){
        if (obrasSociales[i].getEliminado()) {
            continue;
        }

        std::cout << "| " << std::setw(3) << obrasSociales[i].getID() << " | "
                        << std::setw(anchoNombre) << obrasSociales[i].getNombre() << " | "
                        << std::setw(anchoContacto) << obrasSociales[i].getNombreContacto() << " | "
                        << std::setw(anchoTelefono) << obrasSociales[i].getTelefono() << " | "
                        << std::setw(anchoEmail) << obrasSociales[i].getEmail() << " | "
                        << std::setw(anchoCobertura) << obrasSociales[i].getCobertura() << " |\n";
    }

    std::cout << linea;
}

void ManagerObraSocial::mostrarTodos(bool claveValor){
    const int CANTIDAD = _repo.cantidadRegistros();
    ObraSocial* todos = _repo.leerTodos();

    if (claveValor) {
        separadorParcial();
        for (int i = 0; i < CANTIDAD; i ++ ){
            if (todos[i].getEliminado()) {
                continue;
            }

            std::cout << todos[i].getID() << ". " << todos[i].getNombre() << '\n';
        }
        separadorParcial();
    } else {
        mostrarVarios(todos, CANTIDAD);
    }

    delete[] todos;
}

void ManagerObraSocial::ordenadosNombre(){
    const int CANTIDAD = _repo.cantidadRegistros();
    ObraSocial *obrasSociales = _repo.leerTodos();
    ObraSocial aux;

    // Ordenar
    for (int i=0; i<CANTIDAD; i++) {
        if (obrasSociales[i].getEliminado()) {
            continue;
        }

        for (int j=i+1; j<CANTIDAD; j++) {
            if (obrasSociales[j].getEliminado()) {
                continue;
            }

            if (strcmp(obrasSociales[i].getNombre(), obrasSociales[j].getNombre()) > 0) {
                aux = obrasSociales[i];
                obrasSociales[i] = obrasSociales[j];
                obrasSociales[j] = aux;
            }
        }
    }

    // Mostrar
    mostrarVarios(obrasSociales, CANTIDAD);

    // Finalizar
    delete[] obrasSociales;
    std::cout << "Presione ENTER para continuar";
    rlutil::anykey();
}

void ManagerObraSocial::agrupadosPacientes(){
    const int CANTIDAD = _repo.cantidadRegistros();
    ObraSocial *obrasSociales = _repo.leerTodos();
    bool* indicesVisitados = new bool[CANTIDAD] {false};

    ManagerPaciente mPaciente;
    const int CANTIDADPACIENTES = mPaciente.getRepositorio().cantidadRegistros();
    Paciente* pacientes = mPaciente.getRepositorio().leerTodos();
    bool* indicesPacientes = new bool[CANTIDADPACIENTES] {false};
    
    int totalPacientes = 0;
    int iAux = 0;
    for (int i=0; i<CANTIDAD; i++) {
        if (indicesVisitados[i]) {             // Saltear obras sociales ya mostradas
            continue;
        }

        if (obrasSociales[i].getEliminado()) { // y eliminadas
            indicesVisitados[i] = true;
            continue;
        }

        std::cout << "-- Pacientes con la obra social " << obrasSociales[i].getNombre() << " --\n";
       
        for (int j = 0; j < CANTIDADPACIENTES; j++) {
            if (pacientes[j].getEliminado()) {
                continue;
            }

            if (pacientes[j].getCodigoObraSocial() == obrasSociales[i].getID()) {
                totalPacientes ++;
                indicesPacientes[j] = true;
            }
        }

        Paciente *pacientesObraSocial = new Paciente[totalPacientes];

        for (int j = 0; j < CANTIDADPACIENTES; j ++) {
            if (indicesPacientes[j]) {
                pacientesObraSocial[iAux] = pacientes[j];
                iAux ++;
            }
        }
        mPaciente.mostrarVarios(pacientesObraSocial, totalPacientes);
        std::cout << "\n\n";

        // Reiniciar variables
        totalPacientes = 0;
        iAux = 0;
        for (int j = 0; j < CANTIDADPACIENTES; j ++) { indicesPacientes[j] = false; }
        delete[] pacientesObraSocial;
    }

    delete[] pacientes;
    delete[] indicesVisitados;
    delete[] indicesPacientes;

    std::cout << "Presione ENTER para continuar";
    rlutil::anykey();
}


bool ManagerObraSocial::actualizar(ObraSocial obraSocial){
    std::cin.ignore(100, '\n');

    std::string aux;
    char opc = 'n';

    std::cout << "\nEl nombre de la obra social sera la misma? s/n: ";
    std::cin >> opc;

    if (opc != 's') {
        std::cout << "Ingrese el nombre de la obra social: ";
        std::cin.ignore(2, '\n');
        std::getline(std::cin, aux);
        
        if (aux == "") {
            aux = "Sin nombre";
        }

        obraSocial.setNombre(aux.c_str());
    }

    std::cout << "El nombre del contacto sera el mismo? s/n: ";
    std::cin >> opc;

    if (opc != 's') {
        std::cout << "Ingrese el nombre del contacto: ";
        std::cin.ignore(2, '\n');
        std::getline(std::cin, aux);
        
        if (aux == "") {
            aux = "Sin contacto";
        }

        obraSocial.setNombreContacto(aux.c_str());
    }

    std::cout << "El email sera el mismo? s/n: ";
    std::cin >> opc;

    if (opc != 's') {
        std::cout << "Ingrese el email: ";
        std::cin.ignore(2, '\n');
        std::getline(std::cin, aux);
        
        if (aux == "") {
            aux = "Sin email";
        }

        obraSocial.setEmail(aux.c_str());
    }

    std::cout << "El telefono de la obra social sera el mismo? s/n: ";
    std::cin >> opc;

    if (opc != 's') {
        std::cin.ignore(100, '\n');
        int tel = 0;
        while (true) {
            std::cout << "Ingrese el telefono de la obra social: ";
            std::cin >> tel;

            if (tel > 1000000000 && tel < 1600000000) {
                break;
            }

            std::cout << "Intente nuevamente. Asegurese que sea un numero de 10 digitos.\n";
        }

        obraSocial.setTelefono(tel);
    }

    std::cout << "El porcentaje de cobertura de la obra social sera el mismo? s/n: ";
    std::cin >> opc;

    if (opc != 's') {
        std::cin.ignore(100, '\n');
        int cobertura = 0;
        while (true) {
            std::cout << "Ingrese el porcentaje de cobertura de la obra social: ";
            std::cin >> cobertura;

            if (cobertura >= 0 && cobertura <= 100) {
                break;
            }

            std::cout << "Intente nuevamente. Asegurese que sea un valor entre 0 y 100.\n";
        }

        obraSocial.setCobertura(cobertura);
    }

    std::cin.ignore(100, '\n');

    if (_repo.modificar(obraSocial, _repo.getPos(obraSocial.getID()))) {
        std::cout << "La obra social se ha modificado correctamente. Presione ENTER para continuar.\n";
        rlutil::anykey();
        return true;
    }

    std::cout << "Ocurrio un error al intentar modificar la obra social. Presione ENTER para continuar.\n";
    rlutil::anykey();
    return false;
}

bool ManagerObraSocial::eliminar(ObraSocial obraSocial){
    char opc;

    std::cout << "Seguro que desea eliminar la obra social? s/n: ";
    std::cin >> opc;

    if (opc == 's') {
        obraSocial.setEliminado(true);
        if (_repo.modificar(obraSocial, _repo.getPos(obraSocial.getID()))) {
            std::cout << "La obra social se ha eliminado correctamente. Presione ENTER para continuar.\n";
            rlutil::anykey();
            return true;
        }
        std::cout << "Ocurrio un error al intentar eliminar la obra social. Presione ENTER para continuar.\n";
        rlutil::anykey();
        return false;
    }

    std::cout << "Operacion cancelada.\n";
    return false;
}

ArchivoObraSocial ManagerObraSocial::getRepositorio(){
    return _repo;
}
