#include "Turno.h"
#include <iostream>


Turno::Turno(): _id(0), _dniPaciente(0), _idAnalisis(0), _fechaAtencion(), _horaAtencion(), _importe(0.0f) {};

Turno::Turno(int id, int dniPaciente, int idAnalisis, Fecha fechaAtencion, Hora horaAtencion, float importe){
    setID(id);
    setDniPaciente(dniPaciente);
    setIdAnalisis(idAnalisis);
    setFechaAtencion(fechaAtencion);
    setHoraAtencion(horaAtencion);
    setImporte(importe);
};

// SETTERS
void Turno::setID(int id){
    _id = id;
};

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
    std::cout << "Fecha de Atencion: ";
    _fechaAtencion.mostrarFecha();
    std::cout << "Hora de Atencion: ";
    _horaAtencion.mostrarhora();
}
