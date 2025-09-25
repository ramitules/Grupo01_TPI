#pragma once
#include "./Hora.h"
#include "./Persona.h"


class Enfermero: public Persona{
    private:
        bool _habilitado;
        Hora _horarioAtencion;
        int _horasDisponible;
        int _acumuladoHoras;
        float _sueldoHora;

    public:
        Enfermero();
        Enfermero(int dni, const char nombre[], const char apellido[], int telefono, const char email[], int codigoObraSocial, Fecha fechaNacimiento, bool eliminado);
};
