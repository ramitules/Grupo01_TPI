#include "AnalisisProtocolo.h"
#include <cstring>

#include "archivo/ArchivoTipoAnalisis.h"

AnalisisProtocolo::AnalisisProtocolo(): _idProtocolo(0), _idTipoAnalisis(0), _resultados("sin resultados"), _eliminado(0){}; //Chequear Diagrama

AnalisisProtocolo::AnalisisProtocolo(int idProtocolo, int idTipoAnalisis, const char resultados[]) {
    setIdProtocolo(idProtocolo);
    setIdTipoAnalisis(idTipoAnalisis);
    setResultados(resultados);
}

//GETTERS
int AnalisisProtocolo::getIdProtocolo(){
    return _idProtocolo;
}

int AnalisisProtocolo::getIdTipoAnalisis() {
    return _idTipoAnalisis;
}

const char* AnalisisProtocolo::getResultados(){
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

void AnalisisProtocolo::setResultados(const char resultados[]) {
    strcpy(_resultados, resultados);
}

void AnalisisProtocolo::setEliminado(bool eliminado) { //Chequear Diagrama
    _eliminado = eliminado;
}