#include "utils/Hora.h"
#include <iostream>


Hora::Hora(){
    time_t timestamp = time(nullptr);
    struct tm datetime = *localtime(&timestamp);

    setHora(datetime.tm_hour);
    setMinuto(datetime.tm_min);
    setSegundo(0);
};

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

bool Hora::operator==(const Hora &otro){
    return (_hora == otro._hora && _minuto == otro._minuto && _hora == otro._hora);
}

bool Hora::operator<(const Hora &otro){
    if (_hora < otro._hora) { return true; }

    if (_hora == otro._hora && _minuto < otro._minuto) { return true; }

    if (_hora == otro._hora && _minuto == otro._minuto && _segundo < otro._segundo) { return true; }

    return false;
}

bool Hora::operator>(const Hora &otro){
    if (_hora > otro._hora) { return true; }

    if (_hora == otro._hora && _minuto > otro._minuto) { return true; }

    if (_hora == otro._hora && _minuto == otro._minuto && _segundo > otro._segundo) { return true; }

    return false;
}
