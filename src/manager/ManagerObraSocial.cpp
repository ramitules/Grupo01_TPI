#include "manager/ManagerObraSocial.h"
#include "utils/rlutil.h"
#include "utils/funcFrontend.h"


ManagerObraSocial::ManagerObraSocial(){};

bool ManagerObraSocial::cargar(){
    std::cin.ignore(100, '\n');

    int proximoID = _repo.cantidadRegistros() + 1;
    int telefono;
    std::string nombre;
    std::string nombreContacto;
    std::string email;

    std::cout << "Ingrese el nombre de la obra social: ";
    std::getline(std::cin, nombre);
    
    if (nombre == "") {
        nombre = "Sin nombre";
    }

    std::cout << "Ingrese un nombre de contacto: ";
    std::getline(std::cin, nombreContacto); // <-- corregido: antes usaba 'nombre' por error
    
    if (nombreContacto == "") {               // <-- corregido: verificar nombreContacto
        nombreContacto = "Sin contacto";
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
        } else {
            mostrar(aux);
        }

        separadorParcial();
    }
}

bool ManagerObraSocial::actualizar(ObraSocial obraSocial){
    std::cin.ignore(100, '\n');

    std::string aux;
    char opc = 'n';

    std::cout << "El nombre de la obra social sera la misma? s/n: ";
    std::cin >> opc;

    if (opc != 's') {
        std::cout << "Ingrese el nombre de la obra social: ";
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

    std::cin.ignore(100, '\n');

    if (_repo.modificar(obraSocial, _repo.getPos(obraSocial.getID()))) {
        std::cout << "La obra social se ha modificado correctamente. Presione ENTER para continuar.\n";
        rlutil::getkey();
        return true;
    }

    std::cout << "Ocurrio un error al intentar modificar la obra social. Presione ENTER para continuar.\n";
    rlutil::getkey();
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
            rlutil::getkey();
            return true;
        }
        std::cout << "Ocurrio un error al intentar eliminar la obra social. Presione ENTER para continuar.\n";
        rlutil::getkey();
        return false;
    }

    std::cout << "Operacion cancelada.\n";
    return false;
}

ArchivoObraSocial ManagerObraSocial::getRepositorio(){
    return _repo;
}
