#include "Analisis.h"
#include <iostream>
#include "archivo/ArchivoTipoAnalisis.h"
#include "archivo/ArchivoPaciente.h"


Analisis::Analisis(): _id(0), _idTipoAnalisis(0), _sala(0), _dniPaciente(0){};

Analisis::Analisis(int id, int idTipoAnalisis, int sala, int dniPaciente){
    setId(id);
    setIdTipoAnalisis(idTipoAnalisis);
    setSala(sala);
    setDniPaciente(dniPaciente);
};

//GETTERS
int Analisis::getId(){
    return _id;
}

int Analisis::getIdTipoAnalisis(){
    return _idTipoAnalisis;
}

int Analisis::getSala(){
    return _sala;
}

int Analisis::getDniPaciente(){
    return _dniPaciente;
}

TipoAnalisis Analisis::getTipoAnalisis(){
    ArchivoTipoAnalisis repoTipoAnalisis;

    int pos = repoTipoAnalisis.getPos(this->getDniPaciente());

    if (pos == -1) {
        return TipoAnalisis();
    }

    return repoTipoAnalisis.leer(pos);
}

Paciente Analisis::getPaciente() {
    ArchivoPaciente repoPaciente;

    int pos = repoPaciente.getPos(this->getDniPaciente());

    if (pos == -1) {
        return Paciente();
    }

    return repoPaciente.leer(pos);
}

//SETTERS
void Analisis::setSala(int sala){
    _sala = sala;
}
void Analisis::setDniPaciente(int dniPaciente){
    _dniPaciente = dniPaciente;
}

void Analisis::setId(int id) {
    _id = id;
}

void Analisis::setIdTipoAnalisis(int idTipoAnalisis) {
    _idTipoAnalisis = idTipoAnalisis;
}