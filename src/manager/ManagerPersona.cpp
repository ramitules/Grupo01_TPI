#include "manager/ManagerPersona.h"
#include "utils/ManagerFecha.h"
#include <iostream>
#include <limits>

ManagerPersona::ManagerPersona(){};


Persona ManagerPersona::cargar(){
    std::string nombre, apellido, email;
    int dni, telefono;
    ManagerFecha fecha;

    std::cin.ignore(100, '\n');

    while (true) {
        std::cout << "Ingrese el DNI: ";
        std::cin >> dni;

        if (dni > 1000000 && dni < 100000000){
            break;
        }

        std::cout << "Intente nuevamente. Asegurese que sea un numero entre un millon y cien millones.\n";
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

        if (telefono > 1000000000 && telefono < 1600000000) {
            break;
        }

        std::cout << "Intente nuevamente. Asegurese que sea un numero celular de 10 digitos.\n";
    }

    std::cout << "Ingrese la fecha de nacimiento:\n";
    Fecha fechaNacimiento = fecha.cargar();
    
    Persona persona(dni, nombre.c_str(), apellido.c_str(), telefono, email.c_str(), fechaNacimiento, false);

    // Dejar limpio el buffer por las dudas
    std::cin.ignore(100, '\n');

    return persona;
};

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
