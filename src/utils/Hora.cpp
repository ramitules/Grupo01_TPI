#include "utils/Hora.h"
#include <iostream>


Hora::Hora(){};

Hora::Hora(int hora, int minuto, int segundo){};


//SETTERS
void Hora::setHora(int hora){
    while (hora < 0 || hora > 23)
    {   
        std::cout<<" Formato de hora invalido ingrese uno correcto "<< std::endl;
        std::cin>>hora;
    }
     _hora = hora;
}

void Hora::setMinuto(int minuto){
    while (minuto < 0 || minuto > 59)
    {   
        std::cout<<" Formato de minuto invalido ingrese uno correcto "<< std::endl;
        std::cin>>minuto;
    }
     _minuto = minuto;
}

void Hora::setSegundo(int segundo){
    while (segundo < 0 || segundo > 59)
    {   
        std::cout<<" Formato de segundo invalido ingrese uno correcto "<< std::endl;
        std::cin>>segundo;
    }
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
