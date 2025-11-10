#include "manager/ManagerObraSocial.h"
#include "manager/ManagerSecuencia.h"
#include "utils/funcFrontend.h"

ManagerObraSocial::ManagerObraSocial(){};

bool ManagerObraSocial::cargar(){
    std::cin.ignore(100, '\n');

    ManagerSecuencia mSecuencia;
    Secuencia sec = mSecuencia.cargar("ObraSocial");

    int proximoID = sec.getIdActual() + 1;
    int telefono;
    std::string nombre;
    std::string nombreContacto;
    std::string email;

    std::cout << "Ingrese el nombre de la obra social: ";
    std::getline(std::cin, nombre);
    
    if (nombre == "") {
        nombre = "Sin nombre";
    }

    std::cout << "Ingrese el un nombre de contacto: ";
    std::getline(std::cin, nombre);
    
    if (nombre == "") {
        nombre = "Sin contacto";
    }

    while (true) {
        std::cout << "Ingrese el telefono de la obra social: ";
        std::cin >> telefono;

        if (telefono > 1000000000 && telefono < 1600000000) {
            break;
        }

        std::cout << "Intente nuevamente. Asegurese que sea un numero de 10 digitos.\n";
    }

    std::cin.ignore(100, '\n');

    std::cout << "Ingrese el email de la obra social: ";
    std::getline(std::cin, email);
    
    if (email == "") {
        email = "Sin email";
    }

    ObraSocial obraSocial(proximoID, nombre.c_str(), nombreContacto.c_str(), telefono, email.c_str());

    if (_repo.guardar(obraSocial)) {
        std::cout << "La obra social se ha guardado correctamente.\n";
        return true;
    }

    std::cout << "Ocurrio un error al intentar guardar la obra social.\n";
    return false;
}

void ManagerObraSocial::mostrar(ObraSocial obraSocial){
    std::cout << "ID: " << obraSocial.getID() << "\n";
    std::cout << "Nombre: " << obraSocial.getNombre() << "\n";
    std::cout << "Nombre de contacto: " << obraSocial.getNombreContacto() << "\n";
    std::cout << "Telefono: " << obraSocial.getTelefono() << "\n";
    std::cout << "Email: " << obraSocial.getEmail() << "\n";
}

void ManagerObraSocial::mostrarTodos(bool claveValor){
    ObraSocial aux;

    for(int i=0; i<_repo.cantidadRegistros(); i++){
        aux = _repo.leer(i);

        if (aux.getEliminado()) {
            continue;
        }

        if (claveValor) {
            std::cout << aux.getID() << ". " << aux.getNombre() << '\n';
        }
        
        mostrar(aux);

        std::cout << separadorParcial();
    }
}

bool ManagerObraSocial::actualizar(ObraSocial obraSocial){
    // PENDIENTE
}

bool ManagerObraSocial::eliminar(ObraSocial obraSocial){
    char opc;

    std::cout << "Seguro que desea eliminar la obra social? s/n: ";
    std::cin >> opc;

    if (opc == 's') {
        if (_repo.eliminar(_repo.getPos(obraSocial.getID()))){
            std::cout << "La obra social se ha eliminado correctamente.\n";
            return true;
        } else {
            std::cout << "Ocurrio un error al intentar eliminar la obra social.\n";
            return false;
        }
    }

    std::cout << "Operacion cancelada.\n";
    return false;
}

ArchivoObraSocial ManagerObraSocial::getRepositorio(){
    return _repo;
}
