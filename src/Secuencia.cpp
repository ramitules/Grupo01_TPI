#include "Secuencia.h"
#include <cstring>


Secuencia::Secuencia(): _id(1), _objeto("ejemplo"), _idActual(0){};

Secuencia::Secuencia(const char* objeto){
    setId(1);
    setObjeto(objeto);
    setIdActual(0);
};

Secuencia::Secuencia(int id, const char objeto[], int idActual){
    setId(id);
    setObjeto(objeto);
    setIdActual(idActual);
};

int Secuencia::getId(){
    return _id;
};

const char* Secuencia::getObjeto(){
    return _objeto;
};

int Secuencia::getIdActual(){
    return _idActual;
};

void Secuencia::setId(int id){
    _id = id;
};

void Secuencia::setObjeto(const char objeto[]){
    strcpy(_objeto, objeto);
};

void Secuencia::setIdActual(int idActual){
    _idActual = idActual;
};