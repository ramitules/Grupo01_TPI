#include "Paciente.h"
#include <iostream>


Paciente::Paciente(){};

Paciente::Paciente(int dni, const char nombre[], const char apellido[], int telefono, const char email[], int codigoObraSocial, Fecha fechaNacimiento, bool eliminado){};


//SETTERS
void Paciente::setCodigoObraSocial(int codigoObraSocial){
    _codigoObraSocial = codigoObraSocial;
}

//GETTERS
int Paciente::getCodigoObraSocial(){
    return _codigoObraSocial;
}

void Paciente::mostrarDatosPaciente(){
    mostrarDatosPersona();
    std::cout<<"codigo Obra Social:  "<<_codigoObraSocial<<std::endl;
}