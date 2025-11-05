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

int Fecha::diasEnElMes() {
    switch (_mes) {
        case 4: // Abril
        case 6: // Junio
        case 9: // Septiembre
        case 11: // Noviembre
            // Todos estos tienen 30 dias
            return 30; 
        case 2: // Febrero
            // Depende del anio bisiesto
            return esBisiesto() ? 29 : 28;
        default:
            // Los demas meses tienen 31 dias
            return 31;
    }
}

bool Fecha::esBisiesto() {
    return (_anio % 4 == 0 && _anio % 100 != 0) || (_anio % 400 == 0);
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

Fecha& Fecha::operator++(){
    const int LIMITDIAS = diasEnElMes();

    // 1. Comprobar si es el ultimo dia del mes
    if (getDia() < LIMITDIAS) {
        setDia(getDia() + 1);
    } else {
        // Es el ultimo dia del mes
        setDia(1);

        // 2. Comprobar si es el ultimo mes del anio (Diciembre)
        if (getMes() == 12) {
            // Ultimo mes, avanzamos al 1 de Enero del anio siguiente
            setMes(1);
            setAnio(getAnio() + 1);
        } else {
            setMes(getMes() + 1);
        }
    }

    return *this;  // Referencia a la fecha ya modificada
};
