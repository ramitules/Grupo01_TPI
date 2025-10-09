#include "TipoAnalisis.h"
#include <cstring>

TipoAnalisis::TipoAnalisis(): _id(0), _nombreAnalisis(""), _precio(0.0f) {};

TipoAnalisis::TipoAnalisis(int id, const char nombreAnalisis[], float precio){
    setID(id);
    setNombreAnalisis(nombreAnalisis);
    setPrecio(precio);
}


//SETERS 
void TipoAnalisis::setID(int id){
    _id = id;
};

void TipoAnalisis::setNombreAnalisis(const char nombreAnalisis[]){
    strcpy(_nombreAnalisis, nombreAnalisis);
};

void TipoAnalisis::setPrecio(float precio){
    _precio = precio;
};


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