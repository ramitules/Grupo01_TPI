#include "utils/Fecha.h"
#include <iostream>


Fecha::Fecha(): _dia(1), _mes(1), _anio(2000) {};

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
void Fecha::mostrarFecha(){
    std::cout<<_dia<<"/"<<_mes<<"/"<<_anio<<std::endl;
}