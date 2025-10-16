#include "utils/ManagerHora.h"
#include <iostream>

ManagerHora::ManagerHora(){};

Hora ManagerHora::cargar(){
    int hora, minuto, segundo;

    while (true) {
        std::cout << "Hora (0-23): ";
        std::cin >> hora;

        if (hora >= 0 && hora < 24){
            break;
        }

        std::cout << "Intente nuevamente. Asegurese que sea un numero entre 0 y 23.\n";
    }

    while (true) {
        std::cout << "Minuto (0-59): ";
        std::cin >> minuto;

        if (minuto >= 0 && minuto < 60){
            break;
        }

        std::cout << "Intente nuevamente. Asegurese que sea un numero entre 0 y 59.\n";
    }

    // Segundo es opcional
    std::cout << "Segundo (0-59, opcional): ";
    std::cin >> segundo;

    Hora h(hora, minuto, segundo);
    return h;
}

std::string ManagerHora::mostrar(Hora hora){
    std::string horario;

    horario.append((hora.getHora() < 10 ? "0" : "") + std::to_string(hora.getHora()) + ":");
    horario.append((hora.getMinuto() < 10 ? "0" : "") + std::to_string(hora.getMinuto()) + ":");
    horario.append((hora.getSegundo() < 10 ? "0" : "") + std::to_string(hora.getSegundo()));

    return horario;
}