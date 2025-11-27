#include "manager/ManagerPersona.h"
#include "archivo/ArchivoPaciente.h"
#include "archivo/ArchivoEnfermero.h"
#include "utils/ManagerFecha.h"
#include "utils/rlutil.h"
#include <iostream>
#include <limits>

ManagerPersona::ManagerPersona(){};


Persona ManagerPersona::cargar(int dni){
    std::string nombre, apellido, email;
    int telefono;
    ManagerFecha fecha;

    ArchivoPaciente aPaciente;
    ArchivoEnfermero archivoEnfermero;

    if (dni == 0) {
        while (true) {
            std::cout << "Ingrese el DNI: ";
            std::cin >> dni;

            if (dni > 1000000 && dni < 100000000){
                break;
            }

            std::cout << "Intente nuevamente. Asegurese que sea un numero entre un millon y cien millones.\n";
        }
    }
    
    // Corroborar que el DNI no exista tanto en pacientes como en enfermeros
    for(int i=0; i<aPaciente.cantidadRegistros(); i++) {
        if (aPaciente.leer(i).getDNI() == dni) {
            std::cout << "ATENCION: El DNI ya existe. Sobreescribir? s/n: ";
            char opc;
            std::cin >> opc;

            if (opc == 's') {
                break;
            } else {
                return aPaciente.leer(i);
            }
        }
    }

    for(int i=0; i<archivoEnfermero.cantidadRegistros(); i++) {
        if (archivoEnfermero.leer(i).getDNI() == dni) {
            std::cout << "ATENCION: El DNI ya existe. Sobreescribir? s/n: ";
            char opc;
            std::cin >> opc;

            if (opc == 's') {
                break;
            } else {
                return archivoEnfermero.leer(i);
            }
        }
    }

    std::cin.ignore(100, '\n');

    std::cout << "Ingrese el nombre: ";
    std::getline(std::cin, nombre);

    if (nombre == "") {
        nombre = "Sin nombre";
    }

    std::cout << "Ingrese el apellido: ";
    std::getline(std::cin, apellido);

    if (apellido == "") {
        apellido = "Sin apellido";
    }

    std::cout << "Ingrese el email: ";
    std::getline(std::cin, email);

    if (email == "") {
        email = "Sin email";
    }

    while (true) {
        std::cout << "Ingrese el telefono: ";
        std::cin >> telefono;

        if (telefono >= 1100000000 && telefono <= 1599999999) {
            break;
        }

        std::cout << "Intente nuevamente. Asegurese que sea un numero celular de 10 digitos (11-15...).\n";
    }

    std::cout << "Ingrese la fecha de nacimiento:\n";
    Fecha fechaNacimiento = fecha.cargar();
    
    Persona persona(dni, nombre.c_str(), apellido.c_str(), telefono, email.c_str(), fechaNacimiento, false);

    // Dejar limpio el buffer por las dudas
    std::cin.ignore(100, '\n');

    return persona;
};

void ManagerPersona::actualizar(Persona& persona){
    std::string nombre = persona.getNombre();
    std::string apellido = persona.getApellido();
    std::string email = persona.getEmail();
    int telefono = persona.getTelefono();
    char opc = 'n';

    ManagerFecha fecha;
    
    std::cin.ignore(100, '\n');

    std::cout << "El nombre es el mismo? s/n: ";
    std::cin >> opc;

    if (opc != 's') {
        std::cout << "Ingrese el nombre: ";
        std::cin.ignore(2, '\n');
        std::getline(std::cin, nombre);

        if (nombre == "" || nombre == " ") {
            nombre = "Sin nombre";
        }

        persona.setNombre(nombre.c_str());
    }
    
    std::cout << "El apellido es el mismo? s/n: ";
    std::cin >> opc;

    if (opc != 's') {
        std::cout << "Ingrese el apellido: ";
        std::cin.ignore(2, '\n');
        std::getline(std::cin, apellido);
        
        if (apellido == "" || apellido == " ") {
            apellido = "Sin apellido";
        }

        persona.setApellido(apellido.c_str());
    }

    std::cout << "El email es el mismo? s/n: ";
    std::cin >> opc;

    if (opc != 's') {
        std::cout << "Ingrese el email: ";
        std::cin.ignore(2, '\n');
        std::getline(std::cin, email);
        
        if (email == "" || email == " ") {
            email = "Sin email";
        }

        persona.setEmail(email.c_str());
    }

    std::cout << "El telefono es el mismo? s/n: ";
    std::cin >> opc;

    if (opc != 's'){
        std::cin.ignore(2, '\n');
        std::cout << "Ingrese el telefono: ";
        std::cin >> telefono;

        if (telefono < 1100000000 || telefono > 1599999999) {
            std::cout << "Numero invalido (debe ser 11-15...). Se conserva el telefono anterior.\n";
        } else {
            persona.setTelefono(telefono);
        }
        std::cin.ignore(100, '\n');
    }

    std::cout << "La fecha de nacimiento es la misma? s/n: ";
    std::cin >> opc;

    if (opc != 's') {
        persona.setFechaNacimiento(fecha.cargar());
    }

    // Dejar limpio el buffer por las dudas
    std::cin.ignore(100, '\n');
};

bool ManagerPersona::eliminar(Persona& persona){
    char opc;

    std::cout << "Seguro que desea eliminar a esta persona? s/n: ";
    std::cin >> opc;

    if (opc == 's') {
        // ELIMINACION LOGICA
        // Como no tenemos repositorio, simplemente retornamos un booleano con
        // la respuesta del usuario y seteamos el objeto.
        persona.setEliminado(true);
        return true;
    }
    return false;
}

void ManagerPersona::mostrar(Persona persona){
    ManagerFecha mf;

    std::cout << "DNI: " << persona.getDNI() << "\n";
    std::cout << "Nombre completo: " << persona.getNombre() << " " << persona.getApellido() << "\n";
    std::cout << "Email: " << persona.getEmail() << "\n";
    std::cout << "Telefono: " << persona.getTelefono() << "\n";
    std::cout << "Fecha de nacimiento: ";
    std::cout << mf.mostrar(persona.getFechaNacimiento()) << "\n";
    std::cout << "Eliminado: " << (persona.getEliminado() ? "Si" : "No") << "\n";
};
