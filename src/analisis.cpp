#include "Analisis.h"
#include <iostream>
using namespace std;


Analisis::Analisis(){};

Analisis::Analisis(int idTipoAnalisis, int sala, int dniPaciente){};

Analisis::Analisis(int id, int idTipoAnalisis, int sala, int dniPaciente){};


//GETTERS
int Analisis::getId(){
    return _id;
}
int Analisis::getIdTipoAnalisis(){
    return _idTipoAnalisis;
}
int Analisis::getSala(){
    return _sala;
}
int Analisis::getDniPaciente(){
    return _dniPaciente;
}

//SETTERS
void Analisis::setSala(int sala){
    _sala = sala;
}
void Analisis::setDniPaciente(int dniPaciente){
    _dniPaciente = dniPaciente;
}

void Analisis::mostrarAnalisis(){
    cout<<"ID Analisis: "<<_id<<endl;
    cout<<"ID Tipo Analisis: "<<_idTipoAnalisis<<endl;
    cout<<"Sala: "<<_sala<<endl;
    cout<<"DNI Paciente: "<<_dniPaciente<<endl;

}