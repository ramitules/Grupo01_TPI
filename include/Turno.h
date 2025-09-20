#pragma once
#include "./Fecha.h"
#include "./Hora.h"


class Turno{
    private:
        int _id;
        int _dniPaciente;
        int _idAnalisis;
        Fecha _fechaAtencion;
        Hora _horaAtencion;
        float _importe;

    public:
        Turno();
        Turno(int dniPaciente, int idAnalisis, Fecha fechaAtencion, Hora horaAtencion, float importe);
        Turno(int id, int dniPaciente, int idAnalisis, Fecha fechaAtencion, Hora horaAtencion, float importe);
};