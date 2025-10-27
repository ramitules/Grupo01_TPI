#include "AnalisisProtocolo.h"
#include <cstring>

AnalisisProtocolo::AnalisisProtocolo(): _idProtocolo(0), _idTipoAnalisis(0), _resultados("sin resultados"), _eliminado(0){};

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

bool AnalisisProtocolo::getEliminado() {
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

void AnalisisProtocolo::setEliminado(bool eliminado) {
    _eliminado = eliminado;
}