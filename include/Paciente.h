#pragma once
#include "utils/Fecha.h"
#include "Persona.h"


class Paciente: public Persona{
    private:
        int _codigoObraSocial;

    public:
        Paciente();
        Paciente(int dni, const char nombre[], const char apellido[], int telefono, const char email[], int codigoObraSocial, Fecha fechaNacimiento, bool eliminado);

        //SETTERS
        void setCodigoObraSocial(int codigoObraSocial);

        //GETTERS
        int getCodigoObraSocial();

        void mostrarDatosPaciente();
};
