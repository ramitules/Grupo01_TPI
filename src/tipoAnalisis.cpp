#include "TipoAnalisis.h"
#include <cstring>

TipoAnalisis::TipoAnalisis(){};

TipoAnalisis::TipoAnalisis(const char nombreAnalisis[], float precio){};

TipoAnalisis::TipoAnalisis(int id, const char nombreAnalisis[], float precio){};



//SETERS 
void TipoAnalisis::set_nombreAnalisis(const char nombreAnalisis[]){
        strcpy(_nombreAnalisis, nombreAnalisis);

};


void TipoAnalisis::set_precio(float precio){
    _precio = precio;
    
};


//GETERS

int TipoAnalisis::get_id(){
    return _id;
};

const char* TipoAnalisis::get_nombreAnalisis(){
    return _nombreAnalisis;
};

float TipoAnalisis::get_precio(){
    return _precio;
};