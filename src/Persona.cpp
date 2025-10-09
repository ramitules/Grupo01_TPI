#include "Persona.h"
#include <cstring>
#include <iostream>


Persona::Persona(): _dni(0), _nombre("sin nombre"), _apellido("sin apellido"), _email("sin email"), _fechaNacimiento(Fecha()), _eliminado(false) {};

Persona::Persona(int dni, const char nombre[], const char apellido[], int telefono, const char email[], Fecha fechaNacimiento, bool eliminado) {
    setDNI(dni);
    setNombre(nombre);
    setApellido(apellido);
    setTelefono(telefono);
    setEmail(email);
    setFechaNacimiento(fechaNacimiento);
    setEliminado(eliminado);
};


//SETTERS 
void Persona::setDNI(int dni){
    _dni = dni;
};

void Persona::setNombre(const char nombre[]){
    strcpy(_nombre, nombre);
};

void Persona::setApellido(const char apellido[]){
    strcpy(_apellido, apellido);
};

void Persona::setTelefono(int telefono){
    _telefono = telefono;
};

void Persona::setEmail(const char email[]){
    strcpy(_email, email);
};

void Persona::setFechaNacimiento(Fecha fechaNacimiento){
    _fechaNacimiento = fechaNacimiento;
}

void Persona::setEliminado(bool eliminado){
    _eliminado = eliminado;
};

//GETTERS
int Persona::getDNI(){
    return _dni;
};

const char* Persona::getNombre(){
    return _nombre;
};

const char* Persona::getApellido(){
    return _apellido;
};

int Persona::getTelefono(){
    return _telefono;
};

const char* Persona::getEmail(){
    return _email;
};

Fecha Persona::getFechaNacimiento(){
    return _fechaNacimiento;
};

bool Persona::getEliminado(){
    return _eliminado;
};

void Persona::mostrarDatosPersona(){
    std::cout << "DNI: " << _dni << std::endl;
    std::cout << "Nombre: " << _nombre << std::endl;
    std::cout << "Apellido: " << _apellido << std::endl;
    std::cout << "Telefono: " << _telefono << std::endl;
    std::cout << "Email: " << _email << std::endl;
    std::cout << "Fecha de Nacimiento: " << _fechaNacimiento.getDia() << "/" << _fechaNacimiento.getMes() << "/" << _fechaNacimiento.getAnio() << std::endl;
    std::cout << "Eliminado: " << (_eliminado ? "Si" : "No") << std::endl;
};

