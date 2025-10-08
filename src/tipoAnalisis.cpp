#include "TipoAnalisis.h"
#include <cstring>

TipoAnalisis::TipoAnalisis(){};

TipoAnalisis::TipoAnalisis(const char nombreAnalisis[], float precio){};

TipoAnalisis::TipoAnalisis(int id, const char nombreAnalisis[], float precio){};



//SETERS 
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