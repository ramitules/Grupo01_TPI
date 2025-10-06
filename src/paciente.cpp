#include "Paciente.h"
using namespace std;
#include <iostream>

Paciente::Paciente(){};

Paciente::Paciente(int dni, const char nombre[], const char apellido[], int telefono, const char email[], int codigoObraSocial, Fecha fechaNacimiento, bool eliminado){};


//SETTERS
void Paciente::set_codigObraSocial(int codigoObraSocial){
    _codigoObraSocial = codigoObraSocial;
}

//GETTERS
int Paciente::get_codigoObraSocial(){
    return _codigoObraSocial;
}

void Paciente::mostrarDatosPaciente(){
    mostrarDatosPersona();
    cout<<"codigo Obra Social:  "<<_codigoObraSocial<<endl;
    
}