#pragma once


class Hora{
    private:
        int _hora;
        int _minuto;
        int _segundo;

    public:
        Hora();
        Hora(int hora, int minuto, int segundo);

        //SETTERS
        void setHora(int hora);
        void setMinuto(int minuto);
        void setSegundo(int segundo);
        
        //GETTERS
        int getHora();
        int getMinuto();
        int getSegundo();

        // Sobrecarga de operadores
        bool operator==(const Hora &otro);
        bool operator!=(const Hora &otro);
        bool operator<(const Hora &otro);
        bool operator>(const Hora &otro);
};
