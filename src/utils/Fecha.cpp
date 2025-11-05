#include "utils/Fecha.h"
#include <iostream>
#include <ctime>


Fecha::Fecha(){
    time_t timestamp = time(nullptr);
    struct tm datetime = *localtime(&timestamp);

    setAnio(datetime.tm_year + 1900);  // tm_year devuelve los años que pasaron desde "epoch", o sea desde el 1900
    setMes(datetime.tm_mon + 1);
    setDia(datetime.tm_mday);
};

Fecha::Fecha(int dia, int mes, int anio){
    setDia(dia);
    setMes(mes);
    setAnio(anio);
};

//GETTERS
int Fecha::getDia(){
    return _dia;
}

int Fecha::getMes(){
    return _mes;
}

int Fecha::getAnio(){
    return _anio;
}

//SETTERS
void Fecha::setDia(int dia){
    _dia = dia;
}

void Fecha::setMes(int mes){
    _mes = mes;
}

void Fecha::setAnio(int anio){
    _anio = anio;
}

bool Fecha::operator==(const Fecha &otro){
    return (_dia == otro._dia && _mes == otro._mes && _anio == otro._anio);
}

bool Fecha::operator!=(const Fecha &otro){
    return (_dia != otro._dia || _mes != otro._mes || _anio != otro._anio);
}

bool Fecha::operator<(const Fecha &otro){
    if (_anio < otro._anio) { return true; }

    if (_anio == otro._anio && _mes < otro._mes) { return true; }

    if (_anio == otro._anio && _mes == otro._mes && _dia < otro._dia) { return true; }

    return false;
}

bool Fecha::operator>(const Fecha &otro){
    if (_anio > otro._anio) { return true; }

    if (_anio == otro._anio && _mes > otro._mes) { return true; }

    if (_anio == otro._anio && _mes == otro._mes && _dia > otro._dia) { return true; }

    return false;
}
