#include "utils/Hora.h"
#include <iostream>


Hora::Hora(): _hora(0), _minuto(0), _segundo(0) {};

Hora::Hora(int hora, int minuto, int segundo) {
    setHora(hora);
    setMinuto(minuto);
    setSegundo(segundo);
};


//SETTERS
void Hora::setHora(int hora){
    _hora = hora;
}

void Hora::setMinuto(int minuto){
    _minuto = minuto;
}

void Hora::setSegundo(int segundo){
    _segundo = segundo;
}

//GETTERS
int Hora::getHora(){
    return _hora;
}

int Hora::getMinuto(){
    return _minuto;
}

int Hora::getSegundo(){
    return _segundo;
}

void Hora::mostrarhora(){
    std::cout<<_hora<<":"<<_minuto<<":"<<_segundo<<std::endl;   
}
