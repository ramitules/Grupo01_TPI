#include "Enfermero.h"
using namespace std;
#include <iostream>

Enfermero::Enfermero(){}

void Enfermero::Cargar(){}

//SEETERS
void Enfermero::set_habilitado(bool habilitado){
    _habilitado = habilitado;

}
void Enfermero::set_horarioAtencion(Hora horarioAtencion){
    _horarioAtencion = horarioAtencion;
}
void Enfermero::set_horasDisponible(int horasDisponible){
    _horasDisponible = horasDisponible;
}
void Enfermero::set_acumuladoHoras(int acumuladoHoras){
    _acumuladoHoras += acumuladoHoras;
}
void Enfermero::set_sueldoHora(float sueldoHora){
    _sueldoHora = sueldoHora;
}
//GETTERS
bool Enfermero::get_habilitado(){
    return _habilitado;
}
Hora Enfermero::get_horarioAtencion(){
    return _horarioAtencion;
}
int Enfermero::get_horasDisponible(){
    return _horasDisponible;
}
int Enfermero::get_acumuladoHoras(){
    return _acumuladoHoras;
}
float Enfermero::get_sueldoHora(){
    return _sueldoHora;
}

