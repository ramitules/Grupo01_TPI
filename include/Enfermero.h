#pragma once
#include "utils/Hora.h"
#include "Persona.h"


class Enfermero: public Persona{
    private:
        bool _habilitado;
        Fecha _fechaIngreso;

    public:
        Enfermero();
        Enfermero(Persona persona, bool habilitado, Fecha fechaIngreso);

        //SETTERS
        void setHabilitado(bool habilitado);
        void setFechaIngreso(Fecha fechaIngreso);

        //GETTERS
        bool getHabilitado();
        Fecha getFechaIngreso();
    };
