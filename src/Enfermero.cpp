#include "Enfermero.h"
#include <iostream>


Enfermero::Enfermero(): Persona::Persona(), _habilitado(false), _horarioAtencion(Hora()), _horasDisponible(0), _acumuladoHoras(0), _sueldoHora(0.0f){}

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

void Enfermero::mostrarDatosEnfermero(){
    Persona::mostrarDatosPersona();
    std::cout << "Habilitado: " << (_habilitado ? "Si" : "No") << std::endl;
    std::cout << "Horario de atencion: ";
    _horarioAtencion.mostrarhora();
    std::cout << std::endl;
    std::cout << "Horas disponibles: " << _horasDisponible << std::endl;
    std::cout << "Acumulado de horas trabajadas: " << _acumuladoHoras << std::endl;
    std::cout << "Sueldo por hora: $" << _sueldoHora << std::endl;
}
