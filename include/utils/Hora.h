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
    void set_hora(int hora);
    void set_minuto(int minuto);
    void set_segundo(int segundo);
    
    //GETTERS
    int get_hora();
    int get_minuto();
    int get_segundo();

    

    void mostrarhora();

};
