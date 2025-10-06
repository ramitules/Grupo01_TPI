#include "Persona.h"
#include <cstring>
#include <iostream>
using namespace std;

Persona::Persona(){};

Persona::Persona(int dni, const char nombre[], const char apellido[], int telefono, const char email[], Fecha fechaNacimiento, bool eliminado){};


//SETTERS 
void Persona::set_dni(int dni){
    _dni = dni;
};
void Persona::set_nombre(const char nombre[]){
    strcpy(_nombre, nombre);
};
void Persona::set_apellido(const char apellido[]){
    strcpy(_apellido, apellido);
};
void Persona::set_telefono(int telefono){
    _telefono = telefono;
};
void Persona::set_email(const char email[]){
    strcpy(_email, email);
};
void Persona::set_fechaNacimiento(Fecha fechaNacimiento){
    _fechaNacimiento = fechaNacimiento;
}
void Persona::set_eliminado(bool eliminado){
    _eliminado = eliminado;
};

//GETTERS
int Persona::get_dni(){
    return _dni;
};
const char* Persona::get_nombre(){
    return _nombre;
};
const char* Persona::get_apellido(){
    return _apellido;
};
int Persona::get_telefono(){
    return _telefono;
};
const char* Persona::get_email(){
    return _email;
};
Fecha Persona::get_fechaNacimiento(){
    return _fechaNacimiento;
};
bool Persona::get_eliminado(){
    return _eliminado;
};
void Persona::mostrarDatosPersona(){
    cout << "DNI: " << _dni << endl;
    cout << "Nombre: " << _nombre << endl;
    cout << "Apellido: " << _apellido << endl;
    cout << "Telefono: " << _telefono << endl;
    cout << "Email: " << _email << endl;
    cout << "Fecha de Nacimiento: " << _fechaNacimiento.get_dia() << "/" << _fechaNacimiento.get_mes() << "/" << _fechaNacimiento.get_anio() << endl;
    cout << "Eliminado: " << (_eliminado ? "Si" : "No") << endl;
};

