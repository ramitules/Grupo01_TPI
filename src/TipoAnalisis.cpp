#include "TipoAnalisis.h"
#include <cstring>

TipoAnalisis::TipoAnalisis(): _id(0), _nombreAnalisis(""), _tiempoResultado(0), _precio(0.0f) {};

TipoAnalisis::TipoAnalisis(int id, const char nombreAnalisis[], int tiempoResultado, float precio){
    setID(id);
    setNombreAnalisis(nombreAnalisis);
    setTiempoResultado(tiempoResultado);
    setPrecio(precio);
}

//SETERS 
void TipoAnalisis::setID(int id){
    _id = id;
};

void TipoAnalisis::setNombreAnalisis(const char nombreAnalisis[]){
    strcpy(_nombreAnalisis, nombreAnalisis);
};

void TipoAnalisis::setTiempoResultado(int tiempoResultado) {
    _tiempoResultado = tiempoResultado;
}

void TipoAnalisis::setPrecio(float precio){
    _precio = precio;
};

void TipoAnalisis::setEliminado(bool eliminado) {
    _eliminado = eliminado;
}


//GETERS
int TipoAnalisis::getID(){
    return _id;
};

const char* TipoAnalisis::getNombreAnalisis(){
    return _nombreAnalisis;
};

float TipoAnalisis::getPrecio(){
    return _precio;
};

int TipoAnalisis::getTiempoResultado() {
    return _tiempoResultado;
}


bool TipoAnalisis::getEliminado() {
    return _eliminado;
}