#include "Turno.h"
#include <iostream>


Turno::Turno(){};

Turno::Turno(int dniPaciente, int idAnalisis, Fecha fechaAtencion, Hora horaAtencion, float importe){};

Turno::Turno(int id, int dniPaciente, int idAnalisis, Fecha fechaAtencion, Hora horaAtencion, float importe){};

// SETTERS
void Turno::setDniPaciente(int dniPaciente){
    _dniPaciente = dniPaciente;
};

void Turno::setIdAnalisis(int idAnalisis){
    _idAnalisis = idAnalisis;
};

void Turno::setFechaAtencion(Fecha fechaAtencion){
    _fechaAtencion = fechaAtencion;
};

void Turno::setHoraAtencion(Hora horaAtencion){
    _horaAtencion = horaAtencion;
};

void Turno::setImporte(float importe){
    _importe = importe;
};


// GETTERS
int Turno::getID(){
    return _id;
};

int Turno::getDniPaciente(){
    return _dniPaciente;
};

int Turno::getIdAnalisis(){
    return _idAnalisis;
};

Fecha Turno::getFechaAtencion(){
    return _fechaAtencion;
};

Hora Turno::getHoraAtencion(){
    return _horaAtencion;
};

float Turno::getImporte(){
    return _importe;
};


void Turno::mostrarTurno(){
    std::cout << "DNI Paciente: " << _dniPaciente << std::endl;
    std::cout << "ID Analisis: " << _idAnalisis << std::endl;
    std::cout << "Fecha de Atencion: " << _fechaAtencion << std::endl;
    std::cout << "Hora de Atencion: " << _horaAtencion << std::endl;
}