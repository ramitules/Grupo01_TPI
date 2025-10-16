#include "utils/ManagerFecha.h"
#include <iostream>

ManagerFecha::ManagerFecha(){};

Fecha ManagerFecha::cargar(){
    int dia, mes, anio;

    while (true) {
        std::cout << "Dia: ";
        std::cin >> dia;

        if (dia > 0 && dia < 32){
            break;
        }

        std::cout << "Intente nuevamente. Asegurese que sea un numero entre 1 y 31.\n";
    }

    while (true) {
        std::cout << "Mes: ";
        std::cin >> mes;

        if (mes > 0 && mes < 13){
            break;
        }

        std::cout << "Intente nuevamente. Asegurese que sea un numero entre 1 y 12.\n";
    }

    while (true) {
        std::cout << "Anio: ";
        std::cin >> anio;

        if (anio > 1900 && anio < 2024){
            break;
        }

        std::cout << "Intente nuevamente. Asegurese que sea un numero entre 1900 y 2024.\n";
    }

    Fecha fecha(dia, mes, anio);
    return fecha;
}

std::string ManagerFecha::mostrar(Fecha fecha){
    return std::to_string(fecha.getDia()) + "/" + std::to_string(fecha.getMes()) + "/" + std::to_string(fecha.getAnio());
}
