#pragma once
#include <iostream>


class Fecha{
    private:
        int _dia;
        int _mes;
        int _anio;

    public:
        Fecha();
        Fecha(int dia, int mes, int anio);
        // Construye una Fecha a partir de un string con formato "DD/MM/AAAA"
        Fecha(const std::string &fechaStr);

        //GETTERS
        int getDia();
        int getMes();
        int getAnio();

        // String con formato "DD/MM/AAAA"
        std::string to_str();

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
