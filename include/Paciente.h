#pragma once
#include "utils/Fecha.h"
#include "Persona.h"
#include "ObraSocial.h"


class Paciente: public Persona{
    private:
        int _codigoObraSocial;

    public:
        Paciente();
        Paciente(Persona persona, int codigoObraSocial);

        //SETTERS
        void setCodigoObraSocial(int codigoObraSocial);

        //GETTERS
        int getCodigoObraSocial();
        ObraSocial getObraSocial();
};
