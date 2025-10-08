#pragma once
#include "utils/Fecha.h"
#include "utils/Hora.h"


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

        // SETTERS
        void setDniPaciente(int dniPaciente);
        void setIdAnalisis(int idAnalisis);
        void setFechaAtencion(Fecha fechaAtencion);
        void setHoraAtencion(Hora horaAtencion);
        void setImporte(float importe);

        // GETTERS
        int getID();
        int getDniPaciente();
        int getIdAnalisis();
        Fecha getFechaAtencion();
        Hora getHoraAtencion();
        float getImporte();

        void mostrarTurno();
    };
