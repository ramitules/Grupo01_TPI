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

Hora::Hora(const std::string &horaStr) {
    // Asumir que el formato es siempre "HH:MM:SS"
    int hora = std::stoi(horaStr.substr(0, 2));
    int minuto = std::stoi(horaStr.substr(3, 2));
    int segundo = std::stoi(horaStr.substr(6, 2));

    setHora(hora);
    setMinuto(minuto);
    setSegundo(segundo);
}

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

std::string Hora::to_str(){
    std::string hh = (_hora < 10 ? "0" : "") + std::to_string(_hora);
    std::string mm = (_minuto < 10 ? "0" : "") + std::to_string(_minuto);
    std::string ss = (_segundo < 10 ? "0" : "") + std::to_string(_segundo);
    return hh + ":" + mm + ":" + ss;
}

bool Hora::operator==(const Hora &otro){
    return (_hora == otro._hora && _minuto == otro._minuto && _hora == otro._hora);
}

bool Hora::operator!=(const Hora &otro){
    return (_hora != otro._hora || _minuto != otro._minuto || _hora != otro._hora);
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
