#include "Turno.h"
#include "archivo/ArchivoAnalisis.h"
#include "archivo/ArchivoPaciente.h"
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

Paciente Turno::getPaciente(){
    ArchivoPaciente repoPaciente;

    int pos = repoPaciente.getPos(this->getDniPaciente());

    if (pos == -1) {
        return Paciente();
    }

    return repoPaciente.leer(pos);
};

Analisis Turno::getAnalisis(){
    ArchivoAnalisis repoAnalisis;

    int pos = repoAnalisis.getPos(this->getIdAnalisis());

    if (pos == -1) {
        return Analisis();
    }

    return repoAnalisis.leer(pos);
};
