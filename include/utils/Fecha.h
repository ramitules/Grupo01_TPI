#pragma once


class Fecha{
    private:
        int _dia;
        int _mes;
        int _anio;

    public:
        Fecha();
        Fecha(int dia, int mes, int anio);

        //GETTERS
        int getDia();
        int getMes();
        int getAnio();

        //SETTERS
        void setDia(int dia);
        void setMes(int mes);
        void setAnio(int anio);

        // Sobrecarga de operadores
        bool operator==(const Fecha &otro);
        bool operator!=(const Fecha &otro);
        bool operator<(const Fecha &otro);
        bool operator>(const Fecha &otro);
        Fecha& operator++();

        // Otros
        int diasEnElMes();
        bool esBisiesto();
};
