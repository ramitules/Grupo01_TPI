#include "Turno.h"
#include "archivo/ArchivoPaciente.h"
#include <iostream>


Turno::Turno(): _id(0), _dniPaciente(0), _fechaAtencion(), _horaAtencion(), _importe(0.0f) {};

Turno::Turno(int id, int dniPaciente, Fecha fechaAtencion, Hora horaAtencion, float importe){
    setID(id);
    setDniPaciente(dniPaciente);
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

void Turno::setFechaAtencion(Fecha fechaAtencion){
    _fechaAtencion = fechaAtencion;
};

void Turno::setHoraAtencion(Hora horaAtencion){
    _horaAtencion = horaAtencion;
};

void Turno::setImporte(float importe){
    _importe = importe;
};

void Turno::setEliminado(bool eliminado) {
    _eliminado = eliminado;
}


// GETTERS
int Turno::getID(){
    return _id;
};

int Turno::getDniPaciente(){
    return _dniPaciente;
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

bool Turno::getEliminado() {
    return _eliminado;
};
