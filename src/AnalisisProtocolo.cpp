#include "AnalisisProtocolo.h"
#include <cstring>

#include "archivo/ArchivoTipoAnalisis.h"
#include "archivo/ArchivoProtocolo.h"

AnalisisProtocolo::AnalisisProtocolo(): _idProtocolo(0), _idTipoAnalisis(0), _precioSolicitud(0), _resultados("sin resultados"), _eliminado(0){}; //Chequear Diagrama

AnalisisProtocolo::AnalisisProtocolo(int idProtocolo, int idTipoAnalisis, float precioSolicitud) {
    setIdProtocolo(idProtocolo);
    setIdTipoAnalisis(idTipoAnalisis);
    setPrecioSolicitud(precioSolicitud);
}

//GETTERS
int AnalisisProtocolo::getIdProtocolo(){
    return _idProtocolo;
}

int AnalisisProtocolo::getIdTipoAnalisis() {
    return _idTipoAnalisis;
}

float AnalisisProtocolo::getPrecioSolicitud() {
    return _precioSolicitud;
}

const char* AnalisisProtocolo::getResultado(){
    return _resultados;
}

Protocolo AnalisisProtocolo::getProtocolo() {
    ArchivoProtocolo repoProtocolo;

    int pos = repoProtocolo.getPos(this->getIdProtocolo());

    if (pos == -1) {
        return Protocolo();
    }

    return repoProtocolo.leer(pos);
}

TipoAnalisis AnalisisProtocolo::getTipoAnalisis() {
    ArchivoTipoAnalisis repoTipoAnalisis;

    int pos = repoTipoAnalisis.getPos(this->getIdTipoAnalisis());

    if (pos == -1) {
        return TipoAnalisis();
    }

    return repoTipoAnalisis.leer(pos);
}

bool AnalisisProtocolo::getEliminado() {  //Chequear Diagrama
    return _eliminado;
}

//SETTERS

void AnalisisProtocolo::setIdProtocolo(int idProtocolo) {
    _idProtocolo = idProtocolo;
}

void AnalisisProtocolo::setIdTipoAnalisis(int idTipoAnalisis) {
    _idTipoAnalisis = idTipoAnalisis;
}

void AnalisisProtocolo::setPrecioSolicitud(float precioSolicitud) {
    _precioSolicitud = precioSolicitud;
}

void AnalisisProtocolo::setResultados(const char resultados[]) {
    strcpy(_resultados, resultados);
}

void AnalisisProtocolo::setEliminado(bool eliminado) { //Chequear Diagrama
    _eliminado = eliminado;
}