#include "Protocolo.h"
#include <cstring>

Protocolo::Protocolo(): _id(0), _idTurno(0), _dniEnfermero(0), _sala(0), _analisis(false), _observaciones("sin observaciones"), _estado(false), _eliminado(false){};

Protocolo::Protocolo(int id, int idTurno, int dniEnfermero, int sala, bool estado, bool analisis, const char observaciones[]) {
    setId(id);
    setIdTurno(idTurno);
    setDniEnfermero(dniEnfermero);
    setSala(sala);
    setEstado(estado);
    setAnalisis(analisis);
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

bool Protocolo::getEstado() {
    return _estado;
}

bool Protocolo::getAnalisis() {
    return _analisis;
}


Enfermero Protocolo::getEnfermero() {
    ArchivoEnfermero repoEnfermero;

    int pos = repoEnfermero.getPos(this->getDniEnfermero());

    if (pos == -1) {
        return Enfermero();
    }

    return repoEnfermero.leer(pos);
}

Turno Protocolo::getTurno() {
    ArchivoTurno repoTurno;

    int pos = repoTurno.getPos(this->getIdTurno());

    if (pos == -1) {
        return Turno();
    }

    return repoTurno.leer(pos);
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

void Protocolo::setEstado(bool estado) {
    _estado = estado;
}

void Protocolo::setAnalisis(bool analisis) {
    _analisis = analisis;
}

void Protocolo::setEliminado(bool eliminado) {
    _eliminado = eliminado;
}