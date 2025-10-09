#include "Paciente.h"
#include <iostream>


Paciente::Paciente(): Persona::Persona(), _codigoObraSocial(1){};

Paciente::Paciente(int dni, const char nombre[], const char apellido[], int telefono, const char email[], int codigoObraSocial, Fecha fechaNacimiento, bool eliminado){
    setDNI(dni);
    setNombre(nombre);
    setApellido(apellido);
    setTelefono(telefono);
    setEmail(email);
    setCodigoObraSocial(codigoObraSocial);
    setFechaNacimiento(fechaNacimiento);
    setEliminado(eliminado);
};


//SETTERS
void Paciente::setCodigoObraSocial(int codigoObraSocial){
    _codigoObraSocial = codigoObraSocial;
}

//GETTERS
int Paciente::getCodigoObraSocial(){
    return _codigoObraSocial;
}

void Paciente::mostrarDatosPaciente(){
    Persona::mostrarDatosPersona();
    std::cout<<"codigo Obra Social:  "<<_codigoObraSocial<<std::endl;
}