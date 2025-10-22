#include "ObraSocial.h"
#include <iostream>
#include <cstring>

ObraSocial::ObraSocial(): _id(0), _nombre(""), _nombreContacto(""), _telefono(0), _email("") {};

ObraSocial::ObraSocial(int id, const char nombre[], const char nombreContacto[], int telefono, const char email[]){
    setID(id);
    setNombre(nombre);
    setNombreContacto(nombreContacto);
    setTelefono(telefono);
    setEmail(email);
}

//SETTERS
void ObraSocial::setID(int id){
    _id = id;
}

void ObraSocial::setNombre(const char nombre[]){
    strncpy(_nombre, nombre, sizeof(_nombre) - 1);
    _nombre[sizeof(_nombre) - 1] = '\0'; // Asegura la terminación nula
}

void ObraSocial::setNombreContacto(const char nombreContacto[]){
    strncpy(_nombreContacto, nombreContacto, sizeof(_nombreContacto) - 1);
    _nombreContacto[sizeof(_nombreContacto) - 1] = '\0'; // Asegura la terminación nula
}

void ObraSocial::setTelefono(int telefono){
    _telefono = telefono;
}

void ObraSocial::setEmail(const char email[]){
    strncpy(_email, email, sizeof(_email) - 1);
    _email[sizeof(_email) - 1] = '\0'; // Asegura la terminación nula
}

void ObraSocial::setEliminado(bool eliminado) {
    _eliminado = eliminado;
}

//GETTERS
int ObraSocial::getID(){
    return _id;
}

const char* ObraSocial::getNombre(){
    return _nombre;
}

const char* ObraSocial::getNombreContacto(){
    return _nombreContacto;
}

int ObraSocial::getTelefono(){
    return _telefono;
}

const char* ObraSocial::getEmail(){
    return _email;
}

bool ObraSocial::getEliminado() {
    return _eliminado;
}