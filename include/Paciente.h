#pragma once
#include "./Fecha.h"


class Paciente{
    private:
        int _dni;
        char _nombre[50];
        char _apellido[50];
        int _telefono;
        char _email[110];
        int _codigoObraSocial;
        Fecha _fechaNacimiento;
        bool _eliminado;

    public:
        Paciente();
        Paciente(int dni, const char nombre[], const char apellido[], int telefono, const char email[], int codigoObraSocial, Fecha fechaNacimiento, bool eliminado);
};
