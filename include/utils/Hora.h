#pragma once
#include <string>


class Hora{
    private:
        int _hora;
        int _minuto;
        int _segundo;

    public:
        Hora();
        Hora(int hora, int minuto, int segundo);
        // Construye una Hora a partir de un string con formato "HH:MM:SS"
        Hora(const std::string &horaStr);

        //SETTERS
        void setHora(int hora);
        void setMinuto(int minuto);
        void setSegundo(int segundo);
        
        //GETTERS
        int getHora();
        int getMinuto();
        int getSegundo();

        // String con formato "HH:MM:SS"
        std::string to_str();

        // Sobrecarga de operadores
        bool operator==(const Hora &otro);
        bool operator!=(const Hora &otro);
        bool operator<(const Hora &otro);
        bool operator>(const Hora &otro);
};
