#include "Enfermero.h"
#include <iostream>


Enfermero::Enfermero(){}

void Enfermero::Cargar(){}

//SETTERS
void Enfermero::setHabilitado(bool habilitado){
    _habilitado = habilitado;
}

void Enfermero::setHorarioAtencion(Hora horarioAtencion){
    _horarioAtencion = horarioAtencion;
}

void Enfermero::setHorasDisponibles(int horasDisponible){
    _horasDisponible = horasDisponible;
}

void Enfermero::setAcumuladoHoras(int acumuladoHoras){
    _acumuladoHoras += acumuladoHoras;
}

void Enfermero::setSueldoHora(float sueldoHora){
    _sueldoHora = sueldoHora;
}


//GETTERS
bool Enfermero::getHabilitado(){
    return _habilitado;
}

Hora Enfermero::getHorarioAtencion(){
    return _horarioAtencion;
}

int Enfermero::getHorasDisponibles(){
    return _horasDisponible;
}

int Enfermero::getAcumuladoHoras(){
    return _acumuladoHoras;
}

float Enfermero::getSueldoHora(){
    return _sueldoHora;
}
