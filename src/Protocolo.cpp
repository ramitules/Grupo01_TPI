#include "Protocolo.h"
#include <cstring>

Protocolo::Protocolo(): _id(0), _idTurno(0), _dniEnfermero(0), _sala(0), _observaciones("sin observaciones"), _eliminado(0){};

Protocolo::Protocolo(int id, int idTurno, int dniEnfermero, int sala, const char observaciones[]) {
    setId(id);
    setIdTurno(idTurno);
    setDniEnfermero(dniEnfermero);
    setSala(sala);
    setObservaciones(observaciones);
};

//GETTERS
int Protocolo::getId(){
    return _id;
}

int Protocolo::getIdTurno() {
    return _idTurno;
}

int Protocolo::getDniEnfermero() {
    return _dniEnfermero;
}

int Protocolo::getSala(){
    return _sala;
}

const char* Protocolo::getObservaciones(){
    return _observaciones;
}

bool Protocolo::getEliminado() {
    return _eliminado;
}

//SETTERS

void Protocolo::setId(int id) {
    _id = id;
}

void Protocolo::setIdTurno(int idTurno) {
    _idTurno = idTurno;
}

void Protocolo::setDniEnfermero(int dniEnfermero){
    _dniEnfermero = dniEnfermero;
}

void Protocolo::setSala(int sala){
    _sala = sala;
}

void Protocolo::setObservaciones(const char observaciones[]) {
    strcpy(_observaciones, observaciones);
}

void Protocolo::setEliminado(bool eliminado) {
    _eliminado = eliminado;
}