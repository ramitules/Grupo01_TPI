#include "utils/Hora.h"
using namespace std;
#include <iostream>

Hora::Hora(){};

Hora::Hora(int hora, int minuto, int segundo){};

//SETTERS

void Hora::set_hora(int hora){
    while (hora < 0 || hora > 23)
    {   cout<<" Formato de hora invalido ingrese uno correcto "<< endl;
        cin>>hora;
    }
     _hora = hora;
}
void Hora::set_minuto(int minuto){
    while (minuto < 0 || minuto > 59)
    {   cout<<" Formato de minuto invalido ingrese uno correcto "<< endl;
        cin>>minuto;
    }
     _minuto = minuto;
}

void Hora::set_segundo(int segundo){
    while (segundo < 0 || segundo > 59)
    {   cout<<" Formato de segundo invalido ingrese uno correcto "<< endl;
        cin>>segundo;
    }
     _segundo = segundo;
}

//GETTERS
    int Hora::get_hora(){
        return _hora;
    }
    int Hora::get_minuto(){
        return _minuto;
    }
    int Hora::get_segundo(){
        return _segundo;
    }
    void Hora::mostrarhora(){
        cout<<_hora<<":"<<_minuto<<":"<<_segundo<<endl;
        
    }