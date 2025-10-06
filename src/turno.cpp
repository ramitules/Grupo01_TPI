#include "Turno.h"
#include <iostream>
using namespace std;


Turno::Turno(){};

Turno::Turno(int dniPaciente, int idAnalisis, Fecha fechaAtencion, Hora horaAtencion, float importe){};

Turno::Turno(int id, int dniPaciente, int idAnalisis, Fecha fechaAtencion, Hora horaAtencion, float importe){};

// SETTERS
void Turno::set_dniPaciente(int dniPaciente){
    _dniPaciente = dniPaciente;
};
void Turno::set_idAnalisis(int idAnalisis){
    _idAnalisis = idAnalisis;
};
void Turno::set_fechaAtencion(Fecha fechaAtencion){
    _fechaAtencion = fechaAtencion;
};
void Turno::set_horaAtencion(Hora horaAtencion){
    _horaAtencion = horaAtencion;
};
void Turno::set_importe(float importe){
    _importe = importe;
};
// GETTERS
int Turno::get_id(){
    return _id;
};
int Turno::get_dniPaciente(){
    return _dniPaciente;
};
int Turno::get_idAnalisis(){
    return _idAnalisis;
};
Fecha Turno::get_fechaAtencion(){
    return _fechaAtencion;
};
Hora Turno::get_horaAtencion(){
    return _horaAtencion;
};
float Turno::get_importe(){
    return _importe;
};
//mostrar turno
void Turno::mostrarTurno(){
    cout << "DNI Paciente: " << _dniPaciente << endl;
    cout << "ID Analisis: " << _idAnalisis << endl;
    cout << "Fecha de Atencion: " << _fechaAtencion << endl;
    cout << "Hora de Atencion: " << _horaAtencion << endl;
}