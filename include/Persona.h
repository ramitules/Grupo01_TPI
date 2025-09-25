#pragma once
#include "./Fecha.h"


class Persona{
    protected:
        int _dni;
        char _nombre[50];
        char _apellido[50];
        int _telefono;
        char _email[110];
        Fecha _fechaNacimiento;
        bool _eliminado;

    public:
        Persona();
        Persona(int dni, const char nombre[], const char apellido[], int telefono, const char email[], Fecha fechaNacimiento, bool eliminado);
};
