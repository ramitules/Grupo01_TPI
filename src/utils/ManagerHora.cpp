#include "utils/ManagerHora.h"
#include <ctime>
#include <string>

ManagerHora::ManagerHora(){};

Hora ManagerHora::cargar(){
    // Para valores por defecto
    time_t timestamp = time(nullptr);
    struct tm datetime = *localtime(&timestamp);

    int hora, minuto, segundo;
    
    while (true) {
        std::cout << "Hora (0-23 | -1 para hora actual): ";
        std::cin >> hora;

        if (hora == -1) {
            hora = datetime.tm_hour;
            break;
        }

        if (hora >= 0 && hora < 24){
            break;
        }

        std::cout << "Intente nuevamente. Asegurese que sea un numero entre 0 y 23.\n";
    }

    while (true) {
        std::cout << "Minuto (0-59 | -1 para minutos actuales): ";
        std::cin >> minuto;

        if (minuto == -1) {
            minuto = datetime.tm_min;
        }

        if (minuto >= 0 && minuto < 60){
            break;
        }

        std::cout << "Intente nuevamente. Asegurese que sea un numero entre 0 y 59.\n";
    }

    // Segundo es opcional
    std::cout << "Segundo (0-59 | -1 para segundos actuales): ";
    std::cin >> segundo;

    if (segundo == -1) {
        segundo = datetime.tm_sec;
    } else if (segundo < -1) {
        segundo = 0;
    } else if (segundo > 59) {
        segundo = 59;
    }
    
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