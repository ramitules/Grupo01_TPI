#include "Enfermero.h"
#include <iostream>


Enfermero::Enfermero(): Persona::Persona(), _habilitado(false), _fechaIngreso(Fecha()){}

Enfermero::Enfermero(Persona persona, bool habilitado, Fecha fechaIngreso){
    setDNI(persona.getDNI());
    setNombre(persona.getNombre());
    setApellido(persona.getApellido());
    setTelefono(persona.getTelefono());
    setEmail(persona.getEmail());
    setFechaNacimiento(persona.getFechaNacimiento());
    setEliminado(persona.getEliminado());
    setHabilitado(habilitado);
    setFechaIngreso(fechaIngreso);
}

//SETTERS
void Enfermero::setHabilitado(bool habilitado){
    _habilitado = habilitado;
}

void Enfermero::setFechaIngreso(Fecha fechaIngreso){
    _fechaIngreso = fechaIngreso;
}


//GETTERS
bool Enfermero::getHabilitado(){
    return _habilitado;
}

Fecha Enfermero::getFechaIngreso(){
    return _fechaIngreso;
}
