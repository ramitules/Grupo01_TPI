#include "Paciente.h"
#include "archivo/ArchivoObraSocial.h"
#include <iostream>


Paciente::Paciente(): Persona::Persona(), _codigoObraSocial(1){};

Paciente::Paciente(Persona persona, int codigoObraSocial){
    setDNI(persona.getDNI());
    setNombre(persona.getNombre());
    setApellido(persona.getApellido());
    setTelefono(persona.getTelefono());
    setEmail(persona.getEmail());
    setFechaNacimiento(persona.getFechaNacimiento());
    setEliminado(persona.getEliminado());
    setCodigoObraSocial(codigoObraSocial);
};


//SETTERS
void Paciente::setCodigoObraSocial(int codigoObraSocial){
    _codigoObraSocial = codigoObraSocial;
}

//GETTERS
int Paciente::getCodigoObraSocial(){
    return _codigoObraSocial;
}

ObraSocial Paciente::getObraSocial(){
    ArchivoObraSocial repoObraSocial;

    int pos = repoObraSocial.getPos(this->getCodigoObraSocial());

    if (pos == -1) {
        return ObraSocial();
    }

    return repoObraSocial.leer(pos);
}
