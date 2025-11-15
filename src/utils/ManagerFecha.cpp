#include "utils/ManagerFecha.h"
#include <ctime>
#include <string>

ManagerFecha::ManagerFecha(){};

Fecha ManagerFecha::cargar(){
    // Para valores por defecto
    time_t timestamp = time(nullptr);
    struct tm datetime = *localtime(&timestamp);

    int dia, mes, anio;

    while (true) {
        std::cout << "Dia (0 = dia actual): ";
        std::cin >> dia;

        if (dia >= 0 && dia < 32){
            if (dia == 0) {
                dia = datetime.tm_mday;
            }

            break;
        }

        std::cout << "Intente nuevamente. Asegurese que sea un numero entre 1 y 31.\n";
    }

    while (true) {
        std::cout << "Mes (0 = mes actual): ";
        std::cin >> mes;

        if (mes >= 0 && mes < 13){
            if (mes == 0) {
                mes = datetime.tm_mon + 1;
            }

            break;
        }

        std::cout << "Intente nuevamente. Asegurese que sea un numero entre 1 y 12.\n";
    }

    while (true) {
        std::cout << "Anio (0 = anio actual): ";
        std::cin >> anio;

        if (anio == 0) {
            anio = datetime.tm_year + 1900;
            break;
        }

        if (anio > 1900 && anio < 2026){
            break;
        }

        std::cout << "Intente nuevamente. Asegurese que sea un numero entre 1900 y 2025.\n";
    }

    Fecha fecha(dia, mes, anio);
    return fecha;
}

std::string ManagerFecha::mostrar(Fecha fecha){
    return std::to_string(fecha.getDia()) + "/" + std::to_string(fecha.getMes()) + "/" + std::to_string(fecha.getAnio());
}

// Devuelve un vector con todas las fechas incluyendo "desde".
// El vector se crea con memoria dinamica. Recordar eliminarlo!
Fecha* ManagerFecha::rangoFechas(Fecha desde, const int DIAS){
    // Crear un vector dinámico para almacenar las fechas en el rango.
    Fecha* fechas = new Fecha[DIAS];
    Fecha fechaAux = desde;

    // Crear vector de fechas basandose en la fecha anterior y sumandole un dia
    for (int i=0; i<DIAS; i++) {
        fechas[i] = fechaAux;
        ++fechaAux;
    }

    return fechas;
}
